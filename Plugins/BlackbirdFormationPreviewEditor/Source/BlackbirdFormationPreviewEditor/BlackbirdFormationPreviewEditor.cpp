// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlackbirdFormationPreviewEditor.h"

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "UnrealEd.h"
#include "Ship/Formation/BlackbirdFormationComponent.h"
#include "Visualizer/BlackbirdFormationVisualizer.h"

#define LOCTEXT_NAMESPACE "FBlackbirdFormationPreviewEditorModule"

void FBlackbirdFormationPreviewEditorModule::StartupModule()
{
	if (GUnrealEd != nullptr)
	{
		TSharedPtr<FComponentVisualizer> FormationVisualizer = MakeShareable(new FBlackbirdFormationVisualizer);
		GUnrealEd->RegisterComponentVisualizer(UBlackbirdFormationComponent::StaticClass()->GetFName(), FormationVisualizer);
	}
}

void FBlackbirdFormationPreviewEditorModule::ShutdownModule()
{
	if (GUnrealEd != nullptr)
	{
		GUnrealEd->UnregisterComponentVisualizer(UBlackbirdFormationComponent::StaticClass()->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBlackbirdFormationPreviewEditorModule, BlackbirdFormationPreviewEditor)
