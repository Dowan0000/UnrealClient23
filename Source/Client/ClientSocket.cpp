// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSocket.h"
#include <sstream>


ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
	Thread->Kill();
	delete Thread;
	Thread = nullptr;
}

bool ClientSocket::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("ClientSocket::Init()"));
	return true;
}

uint32 ClientSocket::Run()
{
	while (true)
	{
		UE_LOG(LogTemp, Warning, TEXT("ClientSocket::Run()"));
		FPlatformProcess::Sleep(0.1f);

		// Recv
		
	}
	

	return 0;
}

void ClientSocket::Stop()
{
}

void ClientSocket::Exit()
{
}

bool ClientSocket::InitSocket()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("WSAStartup() Error!"));
		return false;
	}

	Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
	if (Socket == INVALID_SOCKET)
	{
		UE_LOG(LogTemp, Warning, TEXT("WSASocket() Error!"));
		return false;
	}

	return true;
}

bool ClientSocket::Connect(const char* IP, const int Port)
{
	SOCKADDR_IN ServerAddr;
	ZeroMemory(&ServerAddr, sizeof(ServerAddr));
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.s_addr = inet_addr(IP);

	if (SOCKET_ERROR == connect(Socket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)))
	{
		UE_LOG(LogTemp, Warning, TEXT("connect() Error!"));
		return false;
	}

	return true;
}

bool ClientSocket::StartListen()
{
	if (Thread) return false;
	
	Thread = FRunnableThread::Create(this, TEXT("ClientSocket"));
	return Thread != nullptr;
}

void ClientSocket::StopListen()
{
	if (Thread)
	{
		Stop();
		Thread->WaitForCompletion();
		Thread->Kill();
		delete Thread;
		Thread = nullptr;
	}
}

void ClientSocket::SendPlayerInfo(PlayerInfo pInfo)
{
	std::stringstream sendStream;

	sendStream << EPacketType::PT_PlayerInfo << std::endl;
	sendStream << pInfo;

	if (-1 == send(Socket, sendStream.str().c_str(), sendStream.str().length(), 0))
		return;
}
