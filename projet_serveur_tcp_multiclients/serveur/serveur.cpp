// serveur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<mutex>
#include "Winsock.h"
#pragma comment(lib, "ws2_32.lib")

char ad[16];
std::mutex lock;
int err, So, lon, size = 0;
struct sockaddr_in machine;

DWORD WINAPI ClientThreadFunc(int client_socket)
{
	char recv_buffer[256];
	char buffer[256];
	while (1) {
		err = recv(client_socket, recv_buffer, 256, 0);		
		std::lock_guard<std::mutex> guard(lock);

		printf("Message recu du client %d: %s", client_socket, recv_buffer);
		printf("\nTapez votre message pour le client %d: ", client_socket);
		
		scanf_s("%256s", buffer, (unsigned)_countof(buffer));
		send(client_socket, buffer, 256, 0);
	}
}

DWORD WINAPI GenThreadFunc()
{
	while (1) {
		DWORD dwThreadID;
		HANDLE hThread;
		int client_socket = accept(So, (struct sockaddr*)&machine, &lon);

		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ClientThreadFunc, (LPVOID)client_socket, NULL, NULL);
		if (hThread == NULL) printf("Creation du Thread impossible");
	}
}

int main()
{
	// Declaration de ce qui est utile a l'initialisation Winsock pour le tcp/ip sous windows

	WORD wVersionRequested;
	WSADATA wsaData;
	/* Initialisation Winsock */

	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return 1;
	}

	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return 1;
	}


	//votre code commence à  partir de ce point

	lon = sizeof(struct sockaddr_in);

	machine.sin_family = AF_INET;
	machine.sin_port = htons(100);
	machine.sin_addr.s_addr = INADDR_ANY;


	So = socket(AF_INET, SOCK_STREAM, 0);

	err = bind(So, (struct sockaddr*)&machine, sizeof(machine));

	listen(So, 16);

	printf("Serveur READY\n");

	DWORD dwThreadID;
	HANDLE hThread;

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GenThreadFunc, (void*) NULL, NULL, NULL);
	if (hThread == NULL) printf("Creation du Thread impossible");

	while (1);

	return 0;

}