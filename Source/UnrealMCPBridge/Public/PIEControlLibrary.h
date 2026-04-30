// Copyright Omar Abdelwahed 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PIEControlLibrary.generated.h"

/**
 * Editor-only library for controlling Play-In-Editor (PIE) sessions from
 * Python / MCP. Wraps ULevelEditorPlaySettings and ULevelEditorSubsystem
 * so callers can configure multiplayer PIE and start/stop it without
 * the user clicking the Play toolbar.
 */
UCLASS()
class UPIEControlLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Start a Play-In-Editor session, optionally configured for multiplayer.
	 * @param NetMode "standalone", "listen_server", or "client" (case-insensitive)
	 * @param NumClients Number of player windows to spawn (clamped >= 1)
	 * @return true if the start request was accepted
	 */
	UFUNCTION(BlueprintCallable, Category = "MCP|PIE")
	static bool StartPIE(const FString& NetMode = TEXT("standalone"), int32 NumClients = 1);

	/** Stop the active PIE session. */
	UFUNCTION(BlueprintCallable, Category = "MCP|PIE")
	static bool StopPIE();

	/** True if a PIE session is currently running. */
	UFUNCTION(BlueprintCallable, Category = "MCP|PIE")
	static bool IsPIERunning();
};
