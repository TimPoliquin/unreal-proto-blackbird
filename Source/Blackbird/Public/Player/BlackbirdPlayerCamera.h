// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackbirdPlayerCamera.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ITrackFollowingActorInterface;

UCLASS()
class BLACKBIRD_API ABlackbirdPlayerCamera : public AActor
{
	GENERATED_BODY()

public:
	ABlackbirdPlayerCamera();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void SetFollowActor(AActor* InFollowActor);
	UCameraComponent* GetCameraComponent() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	TScriptInterface<ITrackFollowingActorInterface> FollowActor;
};
