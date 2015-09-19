// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponEssentials.h"
#include "Rocket.h"
#include "GameFramework/ProjectileMovementComponent.h"


ARocket::ARocket(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, "CollisionComp");
	CollisionComp->InitSphereRadius(5.0f);
	//CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ARocket::OnCollision);
	RootComponent = CollisionComp;

	ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, "ProjectileComp");
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 5.f;
}

void ARocket::OnCollision(AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		AEnemy *Enemy = Cast<AEnemy>(OtherActor);
		if (Enemy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "YOU BLEW UP AN ENEMY!!");
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.f, GetActorLocation());
			Enemy->Destroy();
			Destroy();
		}
	}
	AEnemy *Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "YOU BLEW UP AN ENEMY!!");
		Enemy->Destroy();
		Destroy();
	}
}


