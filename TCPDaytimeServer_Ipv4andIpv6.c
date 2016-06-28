#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<netdb.h>
#define QLEN 5
 
int passivesock(const char *service, const char *transport, int qlen)
{
     int sockt, newsockt, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in6 serv_addr, cli_addr;
     int n;
     sockt = socket(AF_INET6, SOCK_STREAM, 0);
     if (sockt < 0)
     { 
        printf("ERROR in opening the socket");
        exit(1);
     }
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi("2500");
     serv_addr.sin6_family = AF_INET6;
     serv_addr.sin6_addr= in6addr_any;
     serv_addr.sin6_port = htons(portno);
     if (bind(sockt, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
     {
        printf("ERROR on binding");
        exit(1);
     }   
    listen(sockt,5);
    return sockt;
} 

int passiveTCP(const char *service, int qlen) 
{ 
  return passivesock(service, "tcp", qlen);
}   

int main(int argc, char *arg[]) 
{
 char buffer[256]; 
 struct sockaddr_in6 fsin;
  char *service = "daytime";
  int msock, ssock;
 int alen,pid;
msock = passiveTCP(service, QLEN);
while (1)
 {  alen = sizeof(fsin); 
   ssock = accept(msock, (struct sockaddr *)&fsin, &alen); 
  if (ssock < 0)  
 {  printf("Error in accepting the socket connection\n");
    exit(0);
}  
 pid=fork();
 if(pid==0)
{  printf("This is a new client request\n");
   close(msock);
   TCPdaytimed(ssock); 
   exit(0);
}
}
close(ssock);
}

int
TCPdaytimed(int fd)
{
	char *pts; /* pointer to time string */
	time_t now; /* current time*/
 
	char *ctime();
 
	(void) time(&now);
	pts = ctime(&now);
	(void) write(fd, pts, strlen(pts));
}
