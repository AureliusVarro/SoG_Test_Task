// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPool.h"

// Sets default values
ASpawnPool::ASpawnPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bEndSpawn = true;

}

void ASpawnPool::Spawn(FVector const& StartLocation, FRotator const &StartRotation, int32 Index)
{
	int32 Size = GetPoolSize();
	
	//if (bDynamicPooling) {
		if (Size < CurrentWaveMaxEnemiesCount) {
			StupidSpawn(StartLocation, StartRotation);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("%d,%d"), Index, GetPoolSize());
			SimplePool[Index]->SetActorLocation(StartLocation);
			SimplePool[Index]->SetActorRotation(StartRotation);
		}
	
/*
	else {
		if (CurrentWaveLiveEnemiesCount <= PoolMaxCount) {
			if (Size < CurrentWaveMaxEnemiesCount) {
				StupidSpawn(StartLocation, StartRotation);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("%d,%d"), Index, GetPoolSize());
				
					SimplePool[Index]->SetActorLocation(StartLocation);
					SimplePool[Index]->SetActorRotation(StartRotation);
				
			}
		}
	}
	*/

	/*
	if (Size > PoolMaxCount) {
		for (int i = 0; i < PoolMaxCount - Size; i++) {
			SimplePool.RemoveAt(0);
		}
		SimplePool[0]->SetActorLocation(StartLocation);
		SimplePool[0]->SetActorRotation(StartRotation);
	}else if (Size < PoolMaxCount) {
		FActorSpawnParameters SpawnParams;
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnActor,StartLocation, StartRotation, SpawnParams);

		SimplePool.Add(SpawnedActor);	
	} */
}
void ASpawnPool::StupidSpawn(FVector const & StartLocation, FRotator const & StartRotation)
{
	FActorSpawnParameters SpawnParams;
	//SpawnParams.Name = TemplateName;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnActor, StartLocation, StartRotation, SpawnParams);
	SimplePool.Add(SpawnedActor);
}
void ASpawnPool::DeathEnemy()//call when some enemy dieing ;	
{
	CurrentWaveLiveEnemiesCount--;
	if (CurrentWaveLiveEnemiesCount <= 0&& bEndSpawn) {
		
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawnPool::StartWave, DelayTime, false);
		
	}
}


void ASpawnPool::SpawnEnemy(int32 EnemiesCount, TArray<AActor*> SpawnPoints)
{
	bEndSpawn = false;
	
	CurrentWaveMaxEnemiesCount = EnemiesCount;
	
	for (int i = 0; i < CurrentWaveMaxEnemiesCount; i++) {
		AActor* RandomSpwnIndexActor = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)];
		FVector SpawnLoc = RandomSpwnIndexActor->GetActorLocation();
		FRotator SpawnRot = RandomSpwnIndexActor->GetActorRotation();
		CurrentWaveLiveEnemiesCount++;
		SpawnedEnemies++;
		if (bPooling)
			Spawn(SpawnLoc, SpawnRot,i);
		else
			StupidSpawn(SpawnLoc, SpawnRot);
		
	}
	bEndSpawn = true;
	//spawn all enemies
	
}
int32 ASpawnPool::GetPoolSize() {
	return SimplePool.Num();
}
void ASpawnPool::DeadAll() {
	while(CurrentWaveLiveEnemiesCount>0) {
		DeathEnemy();
	}
}
void ASpawnPool::Start(TArray<AActor* > S_P) {
	SP = S_P;
	Wave = 0;
	StartWave();
}
void ASpawnPool::StartWave()
{
	if (!bPooling) {
		while (SimplePool.Num() > 0)
		{
			SimplePool.RemoveAt(0);
		}
	}
	CurrentWaveLiveEnemiesCount = 0;
	//SpawnedEnemies = 0;
	Wave++;
	int32 EnemiesCount = 0;
	if (Wave <=3) {
		EnemiesCount = Wave;
	}
	else {
		EnemiesCount = FMath::RandRange(Wave - 3, Wave + 5);
	}
	if (bClamping&&EnemiesCount > PoolMaxCount)
		EnemiesCount = PoolMaxCount;
		
	 //calculate enemies count;
	SpawnEnemy(EnemiesCount,SP);

}

// Called when the game starts or when spawned


