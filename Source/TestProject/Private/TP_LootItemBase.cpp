// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_LootItemBase.h"

// Sets default values
ATP_LootItemBase::ATP_LootItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATP_LootItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATP_LootItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

