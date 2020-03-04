// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Test2Style.h"

class FTest2Commands : public TCommands<FTest2Commands>
{
public:

	FTest2Commands()
		: TCommands<FTest2Commands>(TEXT("New Actors"), NSLOCTEXT("Contexts", "New Actors", "Test2 Plugin"), NAME_None, FTest2Style::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};