// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

#include "HAL/Runnable.h"


#define BUFSIZE 4096

class AClientPC;


struct PacketHeader
{
	uint16 size; // 패킷 크기
	uint16 Packetid; // 프로토콜ID
};

// Packet Type
enum EPacketType
{
	PT_None,
	PT_PlayerInfo,

};

// Player Info
class PlayerInfo
{
public:
	int32 	PlayerID;

	float	PositionX;
	float	PositionY;
	float	PositionZ;

	float	RotationPitch;
	float	RotationYaw;
	float	RotationRoll;

	float	VelocityX;
	float	VelocityY;
	float	VelocityZ;

	friend std::ostream& operator<<(std::ostream& stream, PlayerInfo& info)
	{
		stream << info.PlayerID << std::endl;
		stream << info.PositionX << std::endl;
		stream << info.PositionY << std::endl;
		stream << info.PositionZ << std::endl;
		stream << info.RotationPitch << std::endl;
		stream << info.RotationYaw << std::endl;
		stream << info.RotationRoll << std::endl;
		stream << info.VelocityX << std::endl;
		stream << info.VelocityY << std::endl;
		stream << info.VelocityZ << std::endl;

		return stream;
	}

	friend std::istream& operator>>(std::istream& stream, PlayerInfo& info)
	{
		stream >> info.PlayerID;
		stream >> info.PositionX;
		stream >> info.PositionY;
		stream >> info.PositionZ;
		stream >> info.RotationPitch;
		stream >> info.RotationYaw;
		stream >> info.RotationRoll;
		stream >> info.VelocityX;
		stream >> info.VelocityY;
		stream >> info.VelocityZ;

		return stream;
	}
};




/**
 * 
 */
class CLIENT_API ClientSocket : public FRunnable
{
public:
	ClientSocket();
	~ClientSocket();

	static ClientSocket* GetSocket()
	{
		static ClientSocket Socket;
		return &Socket;
	}

	// FRunnable interface
	virtual bool		Init() override;
	virtual uint32		Run() override;
	virtual void		Stop() override;
	virtual void		Exit() override;

	// Socket Registration
	bool InitSocket();

	// Connect to Server
	bool Connect(const char* IP, const int Port);

	bool StartListen();
	void StopListen();

public:
	void SetPlayerController(AClientPC* pc) { ClientPC = pc; }

	void SendPlayerInfo(PlayerInfo pInfo);
	//void RecvPlayerInfo(char* recvBuffer);


private:
	FRunnableThread*		Thread;
	bool					bRunThread;

	char					recvBuffer[BUFSIZE];
	SOCKET					Socket;

	AClientPC*				ClientPC;

};
