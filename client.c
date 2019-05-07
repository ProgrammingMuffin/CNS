#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<unistd.h>

int main( )
{
    int sock;
    struct sockaddr_in Server;
    
    char cmd[100];
    
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("\n\tError creating socket: ");
        exit(-1);
    }
    
    Server.sin_port = htons(9001);
    Server.sin_family = AF_INET;
    Server.sin_addr.s_addr = INADDR_ANY;
    bzero(&(Server.sin_zero), 8);
    
    if(connect(sock, (struct sockaddr*)&Server, sizeof(Server)) == -1)
    {
        perror("\n\tConnect error: ");
        exit(-1);
    }
    
    printf("\n\tEnter command: ");
    fgets(cmd, 100, stdin);
    send(sock, cmd, strlen(cmd), 0);
    
    close(sock);
    
    return 0;
}
