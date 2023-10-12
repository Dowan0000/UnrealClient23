// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientPC.h"
#include "ClientSocket.h"

AClientPC::AClientPC()
{
	Socket = ClientSocket::GetSocket();
	Socket->InitSocket();
	if (Socket->Connect("127.0.0.1", 9000))
	{
		UE_LOG(LogTemp, Warning, TEXT("Connect Success!"));
	}
}
