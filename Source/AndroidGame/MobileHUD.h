// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AndroidPhotoLibrary.h"

#include "MobileHUD.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDGAME_API AMobileHUD : public AHUD
{
	GENERATED_BODY()

private:
	TUniquePtr<AndroidPhotoLibrary> PhotoLibrary;

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnPhotoSelected(UTexture2D* SelectedPhoto);
	
	void InitMobileLibrary();
	void OpenMobileGallery();
	void OnPhotoSelected(TArray<uint8>& ImageBytes);
	UTexture2D* LoadImageFromBytes(const TArray<uint8>& ImageBytes) const;
};
