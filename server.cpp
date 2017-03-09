#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc,char* argv[])
{
	int sockfd,connfd;
	struct sockaddr_in srvaddr;
	struct sockaddr_in cliaddr;
	int port;
	char recvbuf[1024],sendbuf[1024];	
	int buflen = -1;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		printf("socket error: %s\n",strerror(errno));
		exit(0);
	}
	bzero(&srvaddr,sizeof(struct sockaddr_in));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port=htons(5006); 
	//srvaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	srvaddr.sin_addr.s_addr = INADDR_ANY;
	//srvaddr.sin_addr.s_addr = inet_addr("10.2.68.120");
	if(bind(sockfd,(struct sockaddr*)(&srvaddr),sizeof(struct sockaddr)) == -1)
	{
		printf("bind error: %s\n",strerror(errno));
		exit(0);
	}

	if(listen(sockfd,5) == -1)
	{
		printf("listen error: %s\n",strerror(errno));
                exit(0);
	}

	socklen_t len = sizeof(struct sockaddr_in);
	printf("\nwait client\n");
	if((connfd = accept(sockfd,(struct sockaddr*)(&cliaddr),&len)) <0)
	{
		printf("accept error: %s\n",strerror(errno));
                exit(0);
	}
	while(1)
	{
		
		printf("server get a client connect from %s\n",inet_ntoa(cliaddr.sin_addr));

		printf("server get a connect\n");

		memset(recvbuf,0,sizeof(recvbuf));
	 	if((buflen = recv(connfd,recvbuf,sizeof(recvbuf),0)) == -1)
    	{
                printf("read client error: %s\n",strerror(errno));
                exit(0);
    	}
    	recvbuf[buflen] = '\0';
        printf("recv from server: %s\n",recvbuf);
        printf("\nconnect success\nsend message to server\n");

		if(0 == strncmp(recvbuf,"byebye",6))
		{
			printf("\nclose client\n");
			close(connfd);
			break;
		}
		
		memset(sendbuf,0,sizeof(sendbuf));
		fgets(sendbuf,sizeof(sendbuf),stdin);
    	if(send(connfd,sendbuf,strlen(sendbuf),0)  == -1)
    	{
            	printf("send message error: %s(error: %d)\n",strerror(errno),errno);
           	    exit(0);
        }

		
		sleep(3);
	}	
	
	close(sockfd);
	return 0;
}
