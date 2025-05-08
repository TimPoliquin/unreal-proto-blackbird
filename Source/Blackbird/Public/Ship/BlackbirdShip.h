// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipInterface.h"
#include "GameFramework/Pawn.h"
#include "BlackbirdShip.generated.h"

class UFloatingPawnMovement;
class UBoxComponent;

UCLASS()
class BLACKBIRD_API ABlackbirdShip : public APawn, public IShipInterface
{
	GENERATED_BODY()

public:
	ABlackbirdShip();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Start ShipInterface **/
	virtual void SetRollAmount(const float InRollDirection) override;
	virtual void SetFacingDirection(const FVector& Direction) override;
	/** End ShipInterface **/

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
	UPROPERTY(EditAnywhere, Category="Movement")
	float RollTime = .5f;
	UPROPERTY(EditAnywhere, Category="Movement")
	float RollAmount = 25.f;

private:
	float InitialRollAmount = 0.f;
	float IntendedRollAmount = 0.f;
	float CurrentRollTime = 0.f;
	FVector FacingDirection = FVector::ZeroVector;
};
