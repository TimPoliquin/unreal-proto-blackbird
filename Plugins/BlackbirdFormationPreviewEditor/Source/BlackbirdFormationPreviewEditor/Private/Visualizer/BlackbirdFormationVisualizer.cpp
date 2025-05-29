#include "Visualizer/BlackbirdFormationVisualizer.h"

#include "Ship/Formation/BlackbirdFormationComponent.h"

void FBlackbirdFormationVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	FComponentVisualizer::DrawVisualization(Component, View, PDI);

	if (const UBlackbirdFormationComponent* FormationComponent = Cast<UBlackbirdFormationComponent>(Component))
	{
		TArray<FTransform> SpawnTransforms;
		FormationComponent->GetSpawnTransforms(SpawnTransforms);
		for (FTransform SpawnTransform : SpawnTransforms)
		{
			PDI->DrawPoint(SpawnTransform.GetLocation(), FLinearColor::Red, 20.f, 0);
			PDI->DrawLine(
				SpawnTransform.GetLocation(),
				SpawnTransform.GetLocation() + SpawnTransform.GetRotation().GetForwardVector() * 50.f,
				FLinearColor::Gray,
				0,
				5
			);
		}
	}
}
