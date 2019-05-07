#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int FA_Stop(char*, char*); //Finite automaton to check for stop command cuz the normal method isnt working :(

int main( )
{
    int sock, cli, len;
    struct sockaddr_in Server, Client;
    
    char cmd[100], stop_cmd[] = "stop";
    
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("\n\tSocket creation error: ");
        exit(-1);
    }
    
    Server.sin_port = htons(9001);
    Server.sin_family = AF_INET;
    Server.sin_addr.s_addr = INADDR_ANY;
    bzero(&(Server.sin_zero), 8);
    
    if(bind(sock, (struct sockaddr*)&Server, sizeof(Server)) == -1)
    {
        perror("\n\tBind error: ");
        exit(-1);
    }
    
    if(listen(sock, 10) == -1)
    {
        perror("\n\tListen error: ");
        exit(-1);
    }
    
    while(1)
    {
        
        if((cli = accept(sock, (struct sockaddr*)&Client, &len)) == -1)
        {
            perror("\n\tError accepting connections: ");
            exit(-1);
        }
        
        recv(cli, cmd, 100, 0);
        
        if(FA_Stop(cmd, stop_cmd) == 1)
        {
            break;
        }
        
        system(cmd);
    }
    
    close(sock);
    
}


int FA_Stop(char cmd[], char stop_cmd[])
{
    int i;
    for(i=0;i<strlen(stop_cmd);i++)
    {
        if(cmd[i] != stop_cmd[i])
            break;
    }
    
    if(i == strlen(stop_cmd))
        return 1;
    else
    {
        printf("\n\ti: %d\tlength of cmd: %d\tlength of stop_cmd: %d\n", i, strlen(cmd), strlen(stop_cmd));
        return 0;
    }
}
