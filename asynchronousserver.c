/*This is the program to execute server using asyncronous I/O*/
#define _GNU_SOURCE
#include "arpa/inet.h"
#include "netinet/in.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"#include "signal.h"
#include "unistd.h"
#include "fcntl.h"
#define BUFNEELEN 512
#define NPACK 10
#define PORT 9930
#define ASYNC
int sock;
void error(char *s)
{
perror(s);
exit(1);
}
void sigio_handler(int sig)
{
char buffer[BUFNEELEN]="";
static int count = 0;
struct sockaddr_in si_other;
int slen=sizeof(si_other);
if (recvfrom(sock, &buffer, BUFNEELEN, 0, (struct sockaddr *)&si_other, &slen)==-1)
error("Error while executing the recvfrom() call");
printf("Received a packet from %s:%d\nData: %s\n\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buffer);
if( ++count == NPACK )
exit(0);
}
int enable_asynch(int sock)
{
int stat = -1;
int flags;
struct sigaction sa;
flags = fcntl(sock, F_GETFL);
fcntl(sock, F_SETFL, flags | O_ASYNC);
sa.sa_flags = 0;
sa.sa_handler = sigio_handler;
sigemptyset(&sa.sa_mask);
if (sigaction(SIGIO, &sa, NULL))
error("Error:");
if (fcntl(sock, F_SETOWN, getpid()) < 0)
error("Error:");
}
if (fcntl(sock, F_SETSIG, SIGIO) < 0)
error("Error:");
return 0;
int main(void){
struct sockaddr_in si_me, si_other;
int i, slen=sizeof(si_other);
char buf[BUFNEELEN];
if ((sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
error("Error while creating the socket");
memset((char *) &si_me, 0, sizeof(si_me));
si_me.sin_family = AF_INET;
si_me.sin_port = htons(PORT);
si_me.sin_addr.s_addr = htonl(INADDR_ANY);
if (bind(sock, (struct sockaddr *)&si_me, sizeof(si_me))==-1)
error("Error while binding the socket");
#ifdef ASYNC
enable_asynch(sock);
while(1) { pause(); }
#else
for (i=0; i < NPACK; i++) {
if (recvfrom(sock, buf, BUFNEELEN, 0, (struct sockaddr *)&si_other, &slen)==-1)
error("error while executing recvfrom() call");
printf("Received a packet from %s:%d\nData: %s\n\n",
inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);
}
close(sock);
#endif
return 0;
}
