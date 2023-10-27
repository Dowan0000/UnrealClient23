// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"

#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

#include "HAL/Runnable.h"


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
	int32 	ID;

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
		//stream << info.SessionId << endl;
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
	void SendPlayerInfo(PlayerInfo pInfo);

private:
	FRunnableThread*		Thread;
	bool					bRunThread;

	SOCKET					Socket;

};
