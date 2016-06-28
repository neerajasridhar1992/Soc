*This is the program for a client using asynchronous I/O */
#define SRV_IP "127.0.0.1"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#define BUFNEELEN 512
#define NPACK 10
#define PORT 9930
void error(char *s)
{
perror(s);
exit(1);
}int main(void)
{
struct sockaddr_in si_other;
int s, i, slen=sizeof(si_other);
char buf[BUFNEELEN];
if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
error("socket");
memset((char *) &si_other, 0, sizeof(si_other));
si_other.sin_family = AF_INET;
si_other.sin_port = htons(PORT);
if (inet_aton(SRV_IP, &si_other.sin_addr)==0)
error("inet_aton:");
for (i=0; i<NPACK; i++) {
printf("Sending packet %d\n", i);
sprintf(buf, "This is packet %d\n", i);
if (sendto(s, buf, BUFNEELEN, 0, (struct sockaddr *)&si_other, slen)==-1)
error("sendto()");
sleep(1);
}
close(s);
return 0;
}
