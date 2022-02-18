#include "AndroidPhotoLibrary.h"

#if PLATFORM_ANDROID
// Android environment includes
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

#if PLATFORM_ANDROID
extern "C"
{
	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_onImageSelected(JNIEnv* jni, jclass clazz, jbyteArray imageBytes)
	{
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
			{
				jbyte* dataPtr = Env->GetByteArrayElements(imageBytes, NULL);
				jsize len = Env->GetArrayLength(imageBytes);
				TArray<uint8> result((uint8*)dataPtr, (int32)len);
				AndroidPhotoLibrary::ImageSelectedFromGalleryProxy.ExecuteIfBound(result);
			}
		}
		);
	}
}
#endif

AndroidPhotoLibrary::AndroidPhotoLibrary()
{
#if PLATFORM_ANDROID
	ImageSelectedFromGalleryProxy = OnImageSelected;
	INIT_JAVA_METHOD(AndroidThunkJava_OpenGallery, "()V");
#endif
}

void AndroidPhotoLibrary::OpenGallery()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_OpenGallery);
	}
#endif
}
