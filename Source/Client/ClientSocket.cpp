// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSocket.h"
#include <sstream>
#include "ClientPC.h"


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

		int recvLen = recv(Socket, recvBuffer, BUFSIZE, 0);
		UE_LOG(LogTemp, Warning, TEXT("RecvPlayerInfo 00000!"));
		
		PacketHeader* header = (PacketHeader*)recvBuffer;

		if (recvLen > 0)
		{
			switch (header->Packetid)
			{
			case::EPacketType::PT_Join:
				//PlayerInfo* pInfo = new PlayerInfo();
				//memcpy(pInfo, recvBuffer + sizeof(PacketHeader), sizeof(PlayerInfo));
				//if (ClientPC == nullptr) return 0;

				//ClientPC->RecvJoin(recvBuffer);
				
				// 플레이어 접속시 작업중 ... 


			case::EPacketType::PT_PlayerInfo:
				{
					// 수정 - 여기로 안들어옴

					UE_LOG(LogTemp, Warning, TEXT("RecvPlayerInfo 11111!"));

					//RecvPlayerInfo(recvBuffer);
					PlayerInfo* pInfo = new PlayerInfo();
					memcpy(pInfo, recvBuffer + sizeof(PacketHeader), sizeof(PlayerInfo));

					if (ClientPC == nullptr) return 0;
					ClientPC->RecvPlayerInfo(pInfo);

					delete pInfo;
				}
			}

		}
		
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
	inet_pton(AF_INET, IP, &ServerAddr.sin_addr);

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

	PacketHeader* header = new PacketHeader();
	header->size = sizeof(PacketHeader) + sizeof(PlayerInfo);
	header->Packetid = EPacketType::PT_PlayerInfo;

	sendStream << header << std::endl;
	sendStream << pInfo;

	if (-1 == send(Socket, sendStream.str().c_str(), sendStream.str().length(), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("SendPlayerInfo() Error!"));
		delete header;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SendPlayerInfo() Success!"));
		delete header;
	}
}

//void ClientSocket::RecvPlayerInfo(char* recvBuffer)
//{
//	/*PlayerInfo* pInfo = new PlayerInfo();
//	memcpy(pInfo, recvBuffer + sizeof(PacketHeader), sizeof(PlayerInfo));
//
//	if (ClientPC == nullptr) return;
//	ClientPC->RecvPlayerInfo(pInfo);
//	
//
//	delete pInfo;*/
//}
