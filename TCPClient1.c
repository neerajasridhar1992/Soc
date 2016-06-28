#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	
	int clientsocket = socket(PF_INET, SOCK_STREAM, 0);
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	bzero((char *) &serverAddr, sizeof(serverAddr));
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(6060);
serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

addr_size = sizeof serverAddr;
connect(clientsocket, (struct sockaddr *) &serverAddr, addr_size);

bzero(buffer,256);
fgets(buffer,255,stdin);
char n;
    n = write(clientsocket,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(clientsocket,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(clientsocket);
//recv(clientsocket, buffer, 1024, 0);

//printf("Data received: %s", buffer);

return 0;
}
