#include "Network.hpp"
#include <iostream>

ServerNet::ServerNet(Uint16 port)
{	
	/* initialize SDL */
	/*if(SDL_Init(0) == -1)
	{
		printf("SDL_Init: %s\n",SDL_GetError());
		exit(1);
	}*/

	/* initialize SDL_net */
	if(SDLNet_Init() < 0)
	{
		printf("SDLNet_Init: %s\n",SDLNet_GetError());
		exit(2);
	}

	/* Resolve the argument into an IPaddress type */
	if(SDLNet_ResolveHost(&ip,NULL,port) == -1)
	{
		printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
		exit(3);
	}

	/* open the server socket */
	server=SDLNet_TCP_Open(&ip);
	if(!server)
	{
		printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
		exit(4);
	}

	len = 1024;
}

ServerNet::~ServerNet()
{
	for (int i = 0; i < clients.size(); i++)
	{
		SDLNet_TCP_Close(clients[i]);
	}
	SDLNet_TCP_Close(server);
	SDLNet_Quit();
}

bool ServerNet::WaitConnection()
{
	//int quit = 0;
	//while(!quit)
	//{
		TCPsocket temp;
		if ((temp = SDLNet_TCP_Accept(server)))
		{
			//quit = 1;
			/* Now we can communicate with the client using csd socket
			* sd will remain opened waiting other connections */
 
			/* Get the remote address */
			if ((remoteIP = SDLNet_TCP_GetPeerAddress(temp)))
			{
				/* Print the address, converting in the host format */
				printf("Host connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
				clients.push_back(temp);
			}
			else
				fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
			return true;
		}
		return false;
	//}
}

bool ServerNet::SendMessage(char* message, int length, int clientID)
{
	if (SDLNet_TCP_Send(clients[clientID], message, length) < length)
	{
		fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		return false;
	}

	if(strcmp(message, "exit") == 0)
		SDLNet_TCP_Close(clients[clientID]);
	return true;
}

bool ServerNet::Broadcast(char* message, int length)
{
	for(int i = 0; i<clients.size(); i++)
	{
		if (SDLNet_TCP_Send(clients[i], message, length) < length)
		{
			fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
			return false;
		}

		if(strcmp(message, "exit") == 0)
			SDLNet_TCP_Close(clients[i]);
	}
	return true;
}

int ServerNet::ReceiveMessage(char message[], int clientID)
{
	int length = SDLNet_TCP_Recv(clients[clientID], message, len);
	if (length > 0)
	{
		if(strcmp(message, "exit") == 0)	/* Terminate this connection */
		{
			printf("Terminate connection\n");
			SDLNet_TCP_Close(clients[clientID]);
		}
		return length;
	}
	return -1;
}

int ServerNet::getIP()
{
	return ip.host;
}

int ServerNet::getNumberOfClients()
{
	return clients.size();
}

ClientNet::ClientNet(Uint16 port, char hostname[])
{
	/* initialize SDL */
	/*if(SDL_Init(0) == -1)
	{
		printf("SDL_Init: %s\n",SDL_GetError());
		exit(1);
	}*/
	
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}
 
	/* Resolve the host we are connecting to */
	if (SDLNet_ResolveHost(&ip, hostname, port) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(3);
	}
 
	/* Open a connection with the IP provided (listen on the host's port) */
	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(4);
	}
}

ClientNet::~ClientNet()
{
	SDLNet_TCP_Close(sd);
	SDLNet_Quit();
}

bool ClientNet::SendMessage(char* message, int length)
{
	if (SDLNet_TCP_Send(sd, message, length) < length)
	{
		fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		return false;
	}

	if(strcmp(message, "exit") == 0)
		SDLNet_TCP_Close(sd);
	return true;
}

void ClientNet::SetID(int id)
{
	clientID = id;
}

int ClientNet::GetClientID()
{
	return clientID;
}

int ClientNet::ReceiveMessage(char message[])
{
	//std::cout << "before receive\n\n" << std::endl;
	int length = SDLNet_TCP_Recv(sd, message, len);
	//std::cout << "after receive\n\n" << std::endl;
	if (length > 0)
	{
		if(strcmp(message, "exit") == 0)	/* Terminate this connection */
		{
			printf("Terminate connection\n");
			SDLNet_TCP_Close(sd);
		}
		return length;
	}
	return -1;
}
