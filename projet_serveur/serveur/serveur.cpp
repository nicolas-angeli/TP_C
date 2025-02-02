// serveur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Winsock.h"

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


	//votre code commence à  partir de ce point

	lon = sizeof(struct sockaddr_in);

	machine.sin_family = AF_INET;
	machine.sin_port = htons(100);
	machine.sin_addr.s_addr = INADDR_ANY;


	So = socket(AF_INET, SOCK_DGRAM, 0);

	err = bind(So, (struct sockaddr*)&machine, sizeof(machine));

	printf("ready\n");

	while (1) {
		err = recvfrom(So, buffer, 256, 0, (struct sockaddr*)&machine, &lon);
		printf("%s\nreponse : ", buffer);
		scanf_s("%256s", buffer, (unsigned)_countof(buffer));
		sendto(So, buffer, 256, 0, (struct sockaddr*)&machine, sizeof(struct sockaddr));
	}

	return 0;

}

