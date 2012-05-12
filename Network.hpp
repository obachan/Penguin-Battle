//#include "SDL.h"
#include "SDL_net.h"
#include <vector>
using namespace std;

class ServerNet
{
	public:
		ServerNet(Uint16);
		~ServerNet();
		bool WaitConnection();
		bool SendMessage(char[], int, int);
		bool Broadcast(char[], int);
		int ReceiveMessage(char[], int);
		int getIP(); 
		int getNumberOfClients();
	private:
		IPaddress ip,*remoteIP;
		TCPsocket server;
		vector<TCPsocket> clients; //server and client socket descriptor
		int len;
};

class ClientNet
{
	public:
		ClientNet(Uint16, char[]);
		~ClientNet();
		bool SendMessage(char[], int);
		int ReceiveMessage(char[]);
		void SetID(int);
		int GetClientID();
	private:
		IPaddress ip;
		TCPsocket sd; //server socket descriptor
		int len;
		int clientID;
};
