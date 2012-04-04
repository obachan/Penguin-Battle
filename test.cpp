#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Network.hpp"

void serverCode()
{
	char portNumber[1024];
	printf("Port number: ");
	fgets(portNumber,1024,stdin);
	ServerNet *server = new ServerNet((Uint16)strtol(portNumber,NULL,0));

	server->WaitConnection();

	char buffer[1024];
	int quit = 0;
	int length = 0;
	while(!quit)
	{
		length = server->ReceiveMessage(buffer);
		if(length != -1)
		{
			printf("Message: %.*s\n", length, buffer);
			quit = 1;
		}
	}
	
	char message[1024];
	printf("What message would you like to send: ");
	fgets(message,1024,stdin);
	
	int len = strlen(message);
	message[len-1] = '\0';
	
	if(!(server->SendMessage(message, len)))
		printf("error sending message");
	server->~ServerNet();
}

void clientCode()
{
	char portNumber[1024];
	printf("Port number: ");
	fgets(portNumber,1024,stdin);

	char hostName[1024];
	printf("hostName: ");
	fgets(hostName,1024,stdin);

	hostName[strlen(hostName)-1] = '\0';

	ClientNet *client = new ClientNet((Uint16)strtol(portNumber,NULL,0), hostName);
	
	char message[1024];
	printf("What message would you like to send: ");
	fgets(message,1024,stdin);

	int len = strlen(message);
	message[len-1] = '\0';
	
	if(!(client->SendMessage(message, len)))
		printf("error sending message");

	int quit = 0;
	int length = 0;
	char buffer[1024];
	while(!quit)
	{
		length = client->ReceiveMessage(buffer);
		if(length != -1)
		{
			printf("Message: %.*s\n", length, buffer);
			quit = 1;
		}
	}
	client->~ClientNet();
}

int main(int argc, char **argv)
{
	char buffer[1024];
	int done = 0;
	while (!done)
	{
		printf("Are you server or client: ");
		fgets(buffer,1024,stdin);

		if (strcmp(buffer, "server\n") == 0)
		{
			serverCode();
			done = 1;
		}
		else if (strcmp(buffer, "client\n") == 0)
		{
			clientCode();
			done = 1;
		}
	}
}
