// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponEssentials.h"
#include "RocketLauncher.h"


ARocketLauncher::ARocketLauncher(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void ARocketLauncher::ProjectileFire()
{
	Super::ProjectileFire();

	if (ProjectileClass != NULL)
	{
		FVector MFLoc = WeaponMesh->GetSocketLocation("Weapon_Socket");
		FRotator MFRot = WeaponMesh->GetSocketRotation("Weapon_Socket");
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		ARocket *const Rocket = GetWorld()->SpawnActor<ARocket>(ProjectileClass, MFLoc, MFRot, SpawnParams);
		if (Rocket)
		{

		}
	}

}


