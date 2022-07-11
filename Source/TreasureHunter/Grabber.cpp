// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicsHandle = 	GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		return;
	}
	
	if (PhysicsHandle->GetGrabbedComponent()!= nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDist;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation , GetComponentRotation());
	}
	
	


}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		/* code */return;
	}
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");

		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
		

	}
	
	
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = 	GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		return;
	}
	
	FHitResult  HitResult;

	if (GetGrabbaleInReach(HitResult))
	{	
		UPrimitiveComponent *  HitComponent = HitResult.GetComponent();
		HitComponent ->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		
		
		AActor * HitActor = HitResult.GetActor();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
 
}


bool UGrabber::GetGrabbaleInReach(FHitResult & OutHitResult)const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDist;


	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(GrabRaduis);
	FHitResult HitResult;
	return GetWorld()->SweepSingleByChannel(
	OutHitResult
	,Start , End,
	 FQuat::Identity,
	 ECC_GameTraceChannel2
	, CollisionShape);
}
