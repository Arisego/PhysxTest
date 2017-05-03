// Fill out your copyright notice in the Description page of Project Settings.

#include "TC_Blank.h"
#include "NewStaticMeshComponent.h"

#include "PhysXIncludes.h"
#include "PhysicsPublic.h"
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"
#include "PhysXPublic.h"

UNewStaticMeshComponent::UNewStaticMeshComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;

    OnCalculateCustomPhysics.BindUObject(this, &UNewStaticMeshComponent::SubstepTick);
}

void UNewStaticMeshComponent::BeginPlay()
{
    Super::BeginPlay();

    PRigidBody = GetBodyInstance()->GetPxRigidBody_AssumesLocked();
    
}

void UNewStaticMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    GetBodyInstance()->AddCustomPhysics(OnCalculateCustomPhysics);
}

void UNewStaticMeshComponent::SubstepTick(float DeltaTime, FBodyInstance* BodyInstance)
{
    // Here get your custom forces
    FVector f = FVector(1000.0f, 1000.0f, 1000.0f);//GetForce();
    FVector t = FVector(1000.0f, 1000.0f, 1000.0f);//GetTorque();

   // And apply them to the rigid body
    PRigidBody->addForce(PxVec3(f.X, f.Y, f.Z), physx::PxForceMode::eFORCE, true);
    PRigidBody->addTorque(PxVec3(t.X, t.Y, t.Z), PxForceMode::eFORCE, true);
}

FVector UNewStaticMeshComponent::GetCurrentLocation() {
    PxTransform PTransform = PRigidBody->getGlobalPose();
    return FVector(PTransform.p.x, PTransform.p.y, PTransform.p.z);
}

FRotator UNewStaticMeshComponent::GetCurrentRotation() {
    PxTransform PTransform = PRigidBody->getGlobalPose();
    return FRotator(FQuat(PTransform.q.x, PTransform.q.y, PTransform.q.z, PTransform.q.w));
}

FVector UNewStaticMeshComponent::GetCurrentAngularVelocity() {
    PxVec3 PAngVelocity = PRigidBody->getAngularVelocity();
    return FMath::RadiansToDegrees(FVector(PAngVelocity.x, PAngVelocity.y, PAngVelocity.z));
}

FVector UNewStaticMeshComponent::GetCurrentVelocity() {
    PxVec3 PVelocity = PRigidBody->getLinearVelocity();
    return FVector(PVelocity.x, PVelocity.y, PVelocity.z);
}


void UNewStaticMeshComponent::SetBallVelocity(FVector fvVelocity, bool bAdd /*= false*/)
{
    if (bAdd && fvVelocity.Size() == 0.0f) return;

    UE_LOG(LogTemp, Log, TEXT("[UNewStaticMeshComponent] SetBallVelocity: speed %s and %s add"), *fvVelocity.ToString(), bAdd?TEXT("is"):TEXT("not"));
    PxVec3 PNewVel = U2PVector(fvVelocity);
    if (bAdd)
    {
        PRigidBody->addForce(PNewVel, physx::PxForceMode::eVELOCITY_CHANGE);
    }
    else 
    {
        PRigidBody->setLinearVelocity(PNewVel);
    }
}
