// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientPC.h"
#include "ClientSocket.h"
#include "ClientCharacter.h"
#include "Kismet/GameplayStatics.h"

AClientPC::AClientPC()
{
	Socket = ClientSocket::GetSocket();
	Socket->InitSocket();
	if (Socket->Connect("127.0.0.1", 8765))
	{
		UE_LOG(LogTemp, Warning, TEXT("Connect Success!"));
	}
}

void AClientPC::BeginPlay()
{
	if (Socket) Socket->StartListen();

	GetWorldTimerManager().SetTimer(PlayerInfoHandle, this, &AClientPC::SendPlayerInfo, 0.1, true);
}

void AClientPC::SendPlayerInfo()
{
	if(Character == nullptr)
		Character = Cast<AClientCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(Character == nullptr) return;

	const FVector& Position = Character->GetActorLocation();
	const FRotator& Rotation = Character->GetActorRotation();
	const FVector& Velocity = Character->GetVelocity();

	PlayerInfo pInfo;

	pInfo.PositionX = Position.X;
	pInfo.PositionY = Position.Y;
	pInfo.PositionZ = Position.Z;

	pInfo.RotationPitch = Rotation.Pitch;
	pInfo.RotationYaw = Rotation.Yaw;
	pInfo.RotationRoll = Rotation.Roll;

	pInfo.VelocityX = Velocity.X;
	pInfo.VelocityY = Velocity.Y;
	pInfo.VelocityZ = Velocity.Z;

	Socket->SendPlayerInfo(pInfo);
}
