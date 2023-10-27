// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClientPC.generated.h"

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

private:
	class ClientSocket* Socket;

	class AClientCharacter* Character;

	FTimerHandle PlayerInfoHandle;
};
