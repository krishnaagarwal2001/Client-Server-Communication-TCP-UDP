#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/time.h>
#include<sys/wait.h>
using namespace std;

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		cerr<<"Missing port number\n";
		exit(0);
	}
	
	int port=atoi(argv[1]);
	
	char msg[2000];
	
	//declare clientSocket and retrieve details fo host
	sockaddr_in clientSocket;
	clientSocket.sin_family=AF_INET;
	clientSocket.sin_port=htons(port);
	inet_pton(AF_INET,"127.0.0.1",&clientSocket.sin_addr);
	
	
	//socket() call to get file descriptor
	int clientSocketID=socket(AF_INET,SOCK_DGRAM,0);
	

	if(clientSocketID<0)
	{
		cout<<"Error connecting\n";
		exit(0);
	}
	
	//start sending and receiving messages
	while(1)
	{
		string data;
		cout<<"Client: ";
		getline(cin,data);
		strcpy(msg,data.c_str());
		if(data=="exit")
		{
			cout<<"Connection terminated";
			break;
		}
		int check=sendto(clientSocketID,msg,sizeof(msg),0,(sockaddr*)&clientSocket,sizeof(clientSocket));
		if(check<0)
		{
			cerr<<"Error in sending\n";
			exit(0);
		}
		
	}
	close(clientSocketID);
}
	
	
	
	
	
	
	
	
	
