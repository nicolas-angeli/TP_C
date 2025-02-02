// client.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Winsock.h"
#pragma comment(lib, "ws2_32.lib")

char ad[16] = "127.0.0.1", buffer[256];
char val;
int err, So, lon;
struct sockaddr_in machine;


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


	//votre code commence Ã  partir de ce 

	machine.sin_family = AF_INET; 
	machine.sin_port = htons(100);
	machine.sin_addr.s_addr = inet_addr(ad);

	So = socket(AF_INET, SOCK_STREAM, 0);

	connect(So, (struct sockaddr*)&machine, sizeof(machine));

	while (1) {
		printf("Tapez votre message : ");
		scanf_s("%s", buffer, 256);

		send(So, buffer, sizeof(buffer), 0);

		recv(So, buffer, 256, 0);

		printf("Message recu : %s\n", buffer);
	}

	return 0;

}

