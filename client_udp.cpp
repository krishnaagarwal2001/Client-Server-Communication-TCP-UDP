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
	if(argc!=3)
	{
		cerr<<"Missing hostname and port number\n";
		exit(0);
	}
	
	char *serverName=argv[1];
	int port=atoi(argv[2]);
	
	char msg[2000];
	
	//declare clientSocket and retrieve details fo host
	sockaddr_in clientSocket;
	clientSocket.sin_family=AF_INET;
	clientSocket.sin_port=htons(port);
	clientSocket.sin_addr.s_addr=INADDR_ANY;
	
	
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
		cin>>data;
		strcpy(msg,data.c_str());
		if(data=="exit")
		{
			cout<<"Connection terminated";
			break;
		}
		send(clientSocketID,msg,sizeof(msg),0);
		cout<<"Server: ";
		recv(clientSocketID,msg,sizeof(msg),0);
		if(!strcmp(msg,"exit"))
		{
			cout<<"Connection terminated";
			break;
		}
		cout<<msg<<endl;
	}
	close(clientSocketID);
}
	
	
	
	
	
	
	
	
	
