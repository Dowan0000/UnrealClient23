// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientPC.h"
#include "ClientSocket.h"
#include "ClientCharacter.h"
#include "Kismet/GameplayStatics.h"

AClientPC::AClientPC()
{
	Socket = ClientSocket::GetSocket();
	Socket->InitSocket();
	Socket->SetPlayerController(this);
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

	pInfo.PlayerID = 1;
	PlayerID = 1;

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

void AClientPC::RecvPlayerInfo(PlayerInfo* pInfo)
{
	// 수정 필요
	AClientPC* ClientPC = nullptr;
	for (auto& OtherCharacter : OtherCharacters)
	{
		ClientPC = Cast<AClientPC>(OtherCharacter->GetController());
		if (ClientPC->PlayerID == pInfo->PlayerID)
			break;
	}

	FVector Position = { pInfo->PositionX, pInfo->PositionY, pInfo->PositionZ };
	FRotator Rotation = { pInfo->RotationPitch, pInfo->RotationYaw, pInfo->RotationRoll };
	FVector Velocity = { pInfo->VelocityX, pInfo->VelocityY, pInfo->VelocityZ };
	ClientPC->Character->SetActorLocation(Position);
	ClientPC->Character->SetActorRotation(Rotation);
	
}
