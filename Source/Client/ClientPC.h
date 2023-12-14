// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClientPC.generated.h"


class PlayerInfo;
class AClientCharacter;

/**
 * 
 */
UCLASS()
class CLIENT_API AClientPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	AClientPC();

protected:
	virtual void BeginPlay() override;

protected:
	void SendPlayerInfo();

public:
	void RecvPlayerInfo(PlayerInfo* pInfo);
	//void RecvJoin()
	
private:
	class ClientSocket*			Socket;
	
	FTimerHandle				PlayerInfoHandle;

	// Character Á¢¼Ó½Ã Add
	TArray<AClientCharacter*>	OtherCharacters;

public:
	AClientCharacter* Character;

	uint16						PlayerID;
};
