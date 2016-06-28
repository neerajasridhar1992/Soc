#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
     int sockt;
     int n1,n2,n3,n4,n5,n6;
     int sndbuf=0;
     int rcvbuf=0;
     socklen_t len;
    // socklen_t clilen;
    // char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     sockt = socket(AF_INET, SOCK_STREAM, 0);
     if (sockt < 0)
     { 
        printf("Error in opening socket");
        exit(1);
     }
    len= sizeof sndbuf;
    n1=getsockopt(sockt,SOL_SOCKET,SO_SNDBUF,&sndbuf,&len);
    if(n1<0)
   {
     printf("Error in socket options");
   }
  len= sizeof rcvbuf;
  n2=getsockopt(sockt,SOL_SOCKET,SO_RCVBUF,&rcvbuf,&len);
  printf("Socket:%d\n",sockt);
  printf("Size of send buffer in bytes:%d\n",sndbuf);
  printf("Size of receive buffer in bytes:%d\n",rcvbuf);
  sndbuf= 68240;
  printf("Setting send buffer size\n");
  n3=setsockopt(sockt,SOL_SOCKET,SO_SNDBUF,&sndbuf,sizeof(sndbuf));
  if(n3<0)
  {
    printf("Error in setting socket options\n");
  }
  len= sizeof sndbuf;
  n4=getsockopt(sockt,SOL_SOCKET,SO_SNDBUF,&sndbuf,&len);
  if(n4<0)
  {
   printf("Error in getting socket options\n");
 }
 rcvbuf= 56904;
 printf("SIze of send buffer in bytes:%d\n",sndbuf);
 printf("Setting receive buffer size\n");
 n5=setsockopt(sockt,SOL_SOCKET,SO_RCVBUF,&rcvbuf,sizeof(rcvbuf));
 if(n5<0)
 {
  printf("Error in setting socket options\n");
 }
 len-sizeof rcvbuf;
 n6=getsockopt(sockt,SOL_SOCKET,SO_RCVBUF,&rcvbuf,&len);
 if(n6<0)
 {
   printf("Error in getting socket options\n");
 }
 printf("Size of receive buffer in bytes:%d\n",rcvbuf);
 

     close(sockt);
     return 0;  
}
