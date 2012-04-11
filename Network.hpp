//#include "SDL.h"
#include "SDL_net.h"

class ServerNet
{
	public:
		ServerNet(Uint16);
		~ServerNet();
		bool WaitConnection();
		bool SendMessage(char[], int);
		int ReceiveMessage(char[]);
		int getIP(); 
	private:
		IPaddress ip,*remoteIP;
		TCPsocket server,client; //server and client socket descriptor
		int len;
};

class ClientNet
{
	public:
		ClientNet(Uint16, char[]);
		~ClientNet();
		bool SendMessage(char[], int);
		int ReceiveMessage(char[]);
	private:
		IPaddress ip;
		TCPsocket sd; //server socket descriptor
		int len;
};
