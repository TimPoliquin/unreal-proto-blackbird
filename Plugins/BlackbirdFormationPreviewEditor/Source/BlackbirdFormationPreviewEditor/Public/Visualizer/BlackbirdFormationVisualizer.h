#pragma once

#include "ComponentVisualizer.h"

class FBlackbirdFormationVisualizer : public FComponentVisualizer
{
	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;
};
