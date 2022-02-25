#pragma once

#include "CoreMinimal.h"
#include "Interface/PhotoLibrary.h"
#include "PhotoLibrary.h"
#include "Delegates/Delegate.h"

DECLARE_DELEGATE_OneParam(FOnImageSelectedFromGallery, TArray<uint8>& ImageBytes);

class PHOTOLIBRARY_API AndroidPhotoLibrary : public IPhotoLibrary
{
#if PLATFORM_ANDROID
public:
	// Android environment class
	static struct _JNIEnv* ENV;
	
#define DECLARE_JAVA_METHOD(name) \
	static jmethodID (name);
	
#define INIT_JAVA_METHOD(name, signature) \
		if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true)) { \
			name = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, #name, signature, false); \
			check(name != NULL); \
		} else { \
			check(0); \
		}

	// Name of Java-side method in PhotoLibrary_APL.xml
	DECLARE_JAVA_METHOD(AndroidThunkJava_OpenGallery);
#endif
	
public:
	// OnImageSelected callback
	static FOnImageSelectedFromGallery ImageSelectedFromGalleryProxy;

	FOnImageSelectedFromGallery OnImageSelected;

	AndroidPhotoLibrary();

	virtual void OpenGallery() override;
};
