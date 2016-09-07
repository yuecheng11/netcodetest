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
	int sockfd,connfd;
	struct sockaddr_in srvaddr;
	struct sockaddr_in cliaddr;
	int len,port;
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
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
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

	len = sizeof(struct sockaddr_in);
	while(1)
	{
		printf("\nwait client\n");
		if((connfd = accept(sockfd,(struct sockaddr*)(&cliaddr),&len)) == -1)
		{
			printf("accept error: %s\n",strerror(errno));
	                exit(0);
		}
		//printf("server get a client connect from %s\n",inet_ntoa(cliaddr.sin_addr));
		printf("server get a connect\n");
	 	if((buflen = read(connfd,recvbuf,1024)) == -1)
        	{
                        printf("read client error: %s\n",strerror(errno));
                        exit(0);
        	}
        	recvbuf[buflen] = '\0';
	        printf("recv from server: %s\n",recvbuf);
	        printf("\nconnect success\nsend message to server\n");
        	
		fgets(sendbuf,1024,stdin);
        	if(send(connfd,sendbuf,strlen(sendbuf),0) < 0)
        	{
                	printf("send message error: %s(error: %d)\n",strerror(errno),errno);
               	        exit(0);
	        }

		printf("\ntest over\n");
		sleep(3);
		close(connfd);
	}	
	close(sockfd);
	return 0;
}
