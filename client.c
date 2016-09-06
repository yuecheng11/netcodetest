#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>

int main(int argc,char* argv[])
{
	int sockfd;
	char buf[1024];
	struct sockaddr_in srvaddr;
	if(argc != 3)
	{
		printf("para error");
	}	
	//client start creat sockfd
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		printf("client create socket error: %s(error : %d)!!!\n",strerror(errno),errno);
		exit(0);
	}
	
	//set ip and  port...of servers'
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(atoi(argv[2]));
	if(inet_pton(AF_INET,argv[1],&srvaddr.sin_addr) <= 0)
	{
		printf("client set server ip error : %s(error: %d)\n",strerror(error),error);
		exit(0);
	}
	
	//client start connet server
	if(connect(sockfd,(struct sockaddr_in*)&srvaddr),sizeof(struct sockaddr) == -1)
	{
		printf("client connect server error : %s(error : %d)\n",strerror(error),error);
		exit(0);
	}	
	
	printf("send message to server\n");
	fgets(buf,1024,stdin);
	if(send(sockfd,buf,strlen(buf),0) < 0)
	{
		printf("send message error: %s(error: %d)\n",strerror(error),error);
		exit(0);
	}

	close(sockfd);
	printf("comunication with server over\n");
	return 0;


}
