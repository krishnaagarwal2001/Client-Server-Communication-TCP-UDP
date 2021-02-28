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
	
	//define a sockeraddr_in struct for server socket
	sockaddr_in serverSocket;
	serverSocket.sin_family=AF_INET;
	serverSocket.sin_port=htons(port);
	serverSocket.sin_addr.s_addr=htonl(INADDR_ANY);
	
	//socket() for server socket
	//int socketID=socket(Family,Type,Protocol)
	int serverSocketID=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(serverSocketID<0)
	{
		cerr<<"Missing serverSocketID\n";
		exit(0);
	}
	
	//bind() the socket to a port
	//int status=bind(socketID,&addressPort,sizeof(Port)
	int bindStatus=bind(serverSocketID,(struct sockaddr *) &serverSocket, sizeof(serverSocket));
	
	if(bindStatus<0)
	{
		cerr<<"Error in bindStatus\n";
		exit(0);
	}

	
	
	sockaddr_in client_Socket;
	socklen_t clientSocketLen=sizeof(client_Socket);
	
	while(1)
	{
		cout<<"Waiting for a message from client...\n";
		memset(msg,'\0',sizeof(msg));
		int r_len=recvfrom(serverSocketID,msg,sizeof(msg),0,(struct sockaddr*)&client_Socket,&clientSocketLen);
		if(r_len<0)
		{
			cerr<<"Error in receiving\n";
			break;	
		}
		if(!strcmp(msg,"exit"))
		{
			cout<<"Session Terminated";
			break;
		}
		cout<<msg<<endl;
		string data;
		cin>>data;
		memset(msg,'\0',sizeof(msg));
		strcpy(msg,data.c_str());
		if(data=="exit")
		{
			cout<<"Session Terminated";
			break;
		}
		
		int s_len=recvfrom(serverSocketID,msg,sizeof(msg),0,(struct sockaddr*)&client_Socket,&clientSocketLen);
		if(s_len<0)
		{
			cerr<<"Error in sending\n";
			break;	
		}
	}

	close(serverSocketID);
	
}
	
	
	
	
	
	
	
	
	
