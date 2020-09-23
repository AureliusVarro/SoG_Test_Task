// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "SpawnPool.generated.h"

UCLASS()
class TESTPROJECT_API ASpawnPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPool();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DelayTime;

	
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> SpawnActor;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 PoolMaxCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName TemplateName;
	UPROPERTY(BlueprintReadOnly)
		int32 CurrentWaveMaxEnemiesCount;
	UPROPERTY(BlueprintReadOnly)
		int32 CurrentWaveLiveEnemiesCount;
	UPROPERTY(BlueprintReadOnly)
		bool bEndSpawn;
	
	UPROPERTY(BlueprintReadOnly)
		int32 Wave;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bPooling;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bClamping;
	

	UFUNCTION(BlueprintCallable)
		void Spawn(FVector const& StartLocation, FRotator const &StartRotation, int32 Index);
	UFUNCTION(BlueprintCallable)
		void StupidSpawn(FVector const& StartLocation, FRotator const &StartRotation);
	UFUNCTION(BlueprintCallable)
		void DeathEnemy();
	UFUNCTION(BlueprintCallable)
		void SpawnEnemy(int32 EnemiesCount, TArray<AActor*> SpawnPoints);

	UFUNCTION(BlueprintCallable)
		void StartWave();
	UFUNCTION(BlueprintCallable)
		void Start(TArray<AActor* > S_P);
	UFUNCTION(BlueprintCallable)
		void DeadAll();
	UFUNCTION(BlueprintCallable)
		int32 GetPoolSize();

	//int32 SpawnedEnemies;

private:
	TArray<AActor*> SimplePool;
	TArray<AActor*> SP;
	
};
