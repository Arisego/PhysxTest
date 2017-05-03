// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "MyStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TC_BLANK_API UMyStaticMeshComponent : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    UMyStaticMeshComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    FCalculateCustomPhysics OnCalculateCustomPhysics;

    void SubstepTick(float DeltaTime, FBodyInstance* BodyInstance);

    physx::PxRigidBody* PRigidBody;

    FORCEINLINE FVector  GetCurrentLocation();
    FORCEINLINE FRotator GetCurrentRotation();
    FORCEINLINE FVector  GetCurrentVelocity();
    FORCEINLINE FVector  GetCurrentAngularVelocity();
};