// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"




UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
     if (Mover == nullptr)
    {
        return;
    }


    AActor* Actor = GetAcceptableActor();

    if (Actor != nullptr)
    {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if(Component != nullptr)
        {
            Component->SetSimulatePhysics(false);
        }
        Actor->AttachToComponent(this , FAttachmentTransformRules::KeepWorldTransform);
         Mover->SetShouldMove(true);
    }
    else   
    {
      Mover->SetShouldMove(false);
    }
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}



AActor* UTriggerComponent::GetAcceptableActor() 
{

    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    if (Actors.Num() > 0 )
    {
        for (int i = 0; i < Actors.Num(); i++)
        {
            bool HasAcceptableTag = Actors[i]->ActorHasTag(TagName);
            bool IsGrabbed = Actors[i] ->ActorHasTag("Grabbed");

            if (HasAcceptableTag && !(IsGrabbed))
            {
                return Actors[i];
            }
        }
        
    }
    return nullptr;
}