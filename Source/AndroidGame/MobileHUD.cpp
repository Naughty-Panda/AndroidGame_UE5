// Fill out your copyright notice in the Description page of Project Settings.

#include "MobileHUD.h"

#include "IImageWrapper.h"
#include "IImageWrapperModule.h"

void AMobileHUD::BeginPlay()
{
	Super::BeginPlay();

	InitMobileLibrary();
}

void AMobileHUD::InitMobileLibrary()
{
#if PLATFORM_ANDROID
PhotoLibrary = MakeUnique<AndroidPhotoLibrary>();
#endif
}

void AMobileHUD::OpenMobileGallery()
{
	if (PhotoLibrary)
	{
		PhotoLibrary->OnImageSelected.BindUObject(this, &AMobileHUD::OnPhotoSelected);
		PhotoLibrary->OpenGallery();
	}
}

void AMobileHUD::OnPhotoSelected(TArray<uint8>& ImageBytes)
{
	auto Length = ImageBytes.Num();

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UTexture2D* ImportedTexture = LoadImageFromBytes(ImageBytes);
		BP_OnPhotoSelected(ImportedTexture);
	});
}

UTexture2D* AMobileHUD::LoadImageFromBytes(const TArray<uint8>& ImageBytes) const
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	const EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(ImageBytes.GetData(), ImageBytes.Num());
	const TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageBytes.GetData(), ImageBytes.Num()))
	{
		TArray<uint8> UncompressedBGRA;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			const FName UniqueName = MakeUniqueObjectName(nullptr, UTexture2D::StaticClass());
			const int32 ImageWidth = ImageWrapper->GetWidth();
			const int32 ImageHeight = ImageWrapper->GetHeight();
			UTexture2D* NewTexture = UTexture2D::CreateTransient(ImageWidth, ImageHeight, EPixelFormat::PF_B8G8R8A8, UniqueName);

			if (!NewTexture)
			{
				return nullptr;
			}

			if (UTexture2D* ImageTexture = Cast<UTexture2D>(NewTexture))
			{
				// Lock data
				void* TextureData = ImageTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				// Move data and clear memory
				FMemory::Memmove(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
				FMemory::Memzero((void*)UncompressedBGRA.GetData(), UncompressedBGRA.Num() * sizeof(uint8));

				ImageTexture->GetPlatformData()->Mips[0].BulkData.Unlock();
				ImageTexture->UpdateResource();
			}

			return NewTexture;
		}
	}

	return nullptr;
}
