// Fill out your copyright notice in the Description page of Project Settings.

#include "TC_Blank.h"
#include "MyStaticMeshComponent.h"

#include "PhysXIncludes.h"
#include "PhysicsPublic.h"
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"

UMyStaticMeshComponent::UMyStaticMeshComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;

    OnCalculateCustomPhysics.BindUObject(this, &UMyStaticMeshComponent::SubstepTick);
}

void UMyStaticMeshComponent::BeginPlay()
{
    Super::BeginPlay();

    PRigidBody = GetBodyInstance()->GetPxRigidBody_AssumesLocked();
}

void UMyStaticMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    GetBodyInstance()->AddCustomPhysics(OnCalculateCustomPhysics);
}

void UMyStaticMeshComponent::SubstepTick(float DeltaTime, FBodyInstance* BodyInstance)
{
    // Here get your custom forces
    FVector f = FVector(100.0f, 100.0f, 100.0f);//GetForce();
    FVector t = FVector(100.0f, 100.0f, 100.0f);//GetTorque();

    // And apply them to the rigid body
    PRigidBody->addForce(PxVec3(f.X, f.Y, f.Z), physx::PxForceMode::eFORCE, true);
    PRigidBody->addTorque(PxVec3(t.X, t.Y, t.Z), PxForceMode::eFORCE, true);
}

FVector UMyStaticMeshComponent::GetCurrentLocation() {
    PxTransform PTransform = PRigidBody->getGlobalPose();
    return FVector(PTransform.p.x, PTransform.p.y, PTransform.p.z);
}

FRotator UMyStaticMeshComponent::GetCurrentRotation() {
    PxTransform PTransform = PRigidBody->getGlobalPose();
    return FRotator(FQuat(PTransform.q.x, PTransform.q.y, PTransform.q.z, PTransform.q.w));
}

FVector UMyStaticMeshComponent::GetCurrentAngularVelocity() {
    PxVec3 PAngVelocity = PRigidBody->getAngularVelocity();
    return FMath::RadiansToDegrees(FVector(PAngVelocity.x, PAngVelocity.y, PAngVelocity.z));
}

FVector UMyStaticMeshComponent::GetCurrentVelocity() {
    PxVec3 PVelocity = PRigidBody->getLinearVelocity();
    return FVector(PVelocity.x, PVelocity.y, PVelocity.z);
}



