// Copyright Omar Abdelwahed 2026. All Rights Reserved.

#include "PIEControlLibrary.h"

#include "Editor.h"
#include "LevelEditorSubsystem.h"
#include "Settings/LevelEditorPlaySettings.h"

bool UPIEControlLibrary::StartPIE(const FString& NetMode, int32 NumClients)
{
	if (IsPIERunning())
	{
		UE_LOG(LogTemp, Warning, TEXT("[PIEControl] StartPIE: PIE already running"));
		return false;
	}

	ULevelEditorPlaySettings* Settings = GetMutableDefault<ULevelEditorPlaySettings>();
	if (!Settings)
	{
		UE_LOG(LogTemp, Error, TEXT("[PIEControl] StartPIE: LevelEditorPlaySettings unavailable"));
		return false;
	}

	EPlayNetMode UENetMode = EPlayNetMode::PIE_Standalone;
	if (NetMode.Equals(TEXT("listen_server"), ESearchCase::IgnoreCase) ||
	    NetMode.Equals(TEXT("listen"), ESearchCase::IgnoreCase) ||
	    NetMode.Equals(TEXT("server"), ESearchCase::IgnoreCase))
	{
		UENetMode = EPlayNetMode::PIE_ListenServer;
	}
	else if (NetMode.Equals(TEXT("client"), ESearchCase::IgnoreCase))
	{
		UENetMode = EPlayNetMode::PIE_Client;
	}

	Settings->SetPlayNetMode(UENetMode);
	Settings->SetPlayNumberOfClients(FMath::Max(1, NumClients));
	Settings->SaveConfig();

	if (!GEditor)
	{
		UE_LOG(LogTemp, Error, TEXT("[PIEControl] StartPIE: GEditor is null"));
		return false;
	}

	ULevelEditorSubsystem* LES = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>();
	if (!LES)
	{
		UE_LOG(LogTemp, Error, TEXT("[PIEControl] StartPIE: LevelEditorSubsystem unavailable"));
		return false;
	}

	int32 OutClients = 1;
	Settings->GetPlayNumberOfClients(OutClients);
	LES->EditorRequestBeginPlay();
	UE_LOG(LogTemp, Display, TEXT("[PIEControl] StartPIE requested (NetMode=%s, NumClients=%d)"),
		*NetMode, OutClients);
	return true;
}

bool UPIEControlLibrary::StopPIE()
{
	if (!GEditor)
	{
		return false;
	}
	ULevelEditorSubsystem* LES = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>();
	if (!LES)
	{
		return false;
	}
	LES->EditorRequestEndPlay();
	return true;
}

bool UPIEControlLibrary::IsPIERunning()
{
	return GEditor != nullptr && GEditor->PlayWorld != nullptr;
}
