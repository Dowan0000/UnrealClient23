// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

#include "HAL/Runnable.h"

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

private:
	FRunnableThread*		Thread;
	bool					bRunThread;

	SOCKET					Socket;

};
