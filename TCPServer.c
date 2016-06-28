#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

int main(){
  int serversocket, newsocket;
  char buffer[1024];
  struct sockaddr_in serverAddr, server, client;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  
  serversocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(5000);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
bzero((char *) &serverAddr, sizeof(serverAddr));
//  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  /*---- Bind the address struct to the socket ----*/
  bind(serversocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

 listen(serversocket, 5);
 	printf("Listening\n");

 	
  addr_size = sizeof serverStorage;
  newsocket = accept(serversocket, (struct sockaddr *) &serverStorage, &addr_size);
printf("H"); 


     bzero(buffer,256);
char n;
     n = read(newsocket,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsocket,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(newsocket);
     close(serversocket);
     return 0; 

}

//while(1)
// {
//	printf("H");
// strcpy(buffer, "Hello, this is the TCP server\n");
 //send(newsocket, buffer, 1024,0);
 
 //recv(newsocket, buffer, 1024, 0);
 
// }
 
// return 0;
// }
