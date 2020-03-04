// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Test2Commands.h"

#define LOCTEXT_NAMESPACE "FTest2Module"

void FTest2Commands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "New Actors", "Bring up Test2 window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
