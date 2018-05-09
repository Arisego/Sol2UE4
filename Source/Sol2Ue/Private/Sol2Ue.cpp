// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Sol2Ue.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"

#define LOCTEXT_NAMESPACE "FSol2UeModule"

void FSol2UeModule::StartupModule()
{
	FString LibPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() + "Plugins/Sol2Ue/Source/ThirdParty/LuaJIT/lib/");

	// If we're on Windows we need to load DLLs from our custom path
#if PLATFORM_WINDOWS && PLATFORM_64BITS 
	LibPath += "Win64";
	FPlatformProcess::PushDllDirectory(*LibPath);
	//DLLHandle = FPlatformProcess::GetDllHandle(LibPath/TEXT("lua51.dll"));

	UE_LOG(LogTemp, Log, TEXT("patched dll directory paths: %s"), *LibPath);
#endif
}

void FSol2UeModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSol2UeModule, Sol2Ue)