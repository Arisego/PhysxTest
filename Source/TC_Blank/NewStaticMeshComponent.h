// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "NewStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class TC_BLANK_API UNewStaticMeshComponent : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    UNewStaticMeshComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    FCalculateCustomPhysics OnCalculateCustomPhysics;

    void SubstepTick(float DeltaTime, FBodyInstance* BodyInstance);

    physx::PxRigidBody* PRigidBody;

    FORCEINLINE FVector  GetCurrentLocation();
    FORCEINLINE FRotator GetCurrentRotation();
    FORCEINLINE FVector  GetCurrentVelocity();
	void SetBallVelocity(FVector fvVelocity, bool bAdd /*= false*/);
	FORCEINLINE FVector  GetCurrentAngularVelocity();
};
