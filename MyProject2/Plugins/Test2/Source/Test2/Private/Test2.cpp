// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Test2.h"
#include "Test2Style.h"
#include "Test2Commands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName Test2TabName("New Actors");

#define LOCTEXT_NAMESPACE "FTest2Module"

void FTest2Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTest2Style::Initialize();
	FTest2Style::ReloadTextures();

	FTest2Commands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTest2Commands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTest2Module::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FTest2Module::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FTest2Module::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(Test2TabName, FOnSpawnTab::CreateRaw(this, &FTest2Module::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTest2TabTitle", "New Actors"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTest2Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FTest2Style::Shutdown();

	FTest2Commands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(Test2TabName);
}

TSharedRef<SDockTab> FTest2Module::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//FText WidgetText = FText::Format(
	//	LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
	//	/*FText::FromString(TEXT("FTest2Module::OnSpawnPluginTab")),
	//	FText::FromString(TEXT("Test2.cpp"))*/
	//	FText::FromString(TEXT("Rub")),
	//	FText::FromString(TEXT("Dub"))
	//	);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[

			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SComboButton)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.ButtonContent()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("BlickBlook", "Abble gobble gook"))
					
				]
				
			]
		];
	
}

void FTest2Module::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(Test2TabName);
}

void FTest2Module::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FTest2Commands::Get().OpenPluginWindow);
}

void FTest2Module::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FTest2Commands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTest2Module, Test2)