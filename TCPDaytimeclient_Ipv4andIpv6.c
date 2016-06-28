#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
//#include "errexit.h"
//extern int errno;
int TCPdaytime(const char *host, char *type);
//int errexit(const char *format, ...);
#define LINELEN 128

int connectsock(const char *host, char *type)
{
	struct hostent *phe; /* This is the pointer used for host information entry */
	struct servent *pse; /* This pointer is used for service information entry */
	struct protoent *ppe; /*This pointer is used for protocol information entry*/
	struct sockaddr_in sin;
	struct addrinfo addr, *adrp;
	int i, s;
	if(*type == '6') {
		printf("We are currently in the IPv6 socket connection\n");
		addr.ai_flags = 0;
		addr.ai_family = PF_INET6;
		addr.ai_socktype = SOCK_STREAM;
		addr.ai_protocol = 0;

		if((i = getaddrinfo( host, "daytime", &addr, &adrp)) != 0)
			printf("getaddrinfo failed code\n");
	
		/* This is to allocate a socket */
		s = socket(adrp->ai_family, adrp->ai_socktype, adrp->ai_protocol);
		if (s < 0)
			printf("Error in creating a socket\n");
		/* Connect the socket */
		if(connect(s, adrp->ai_addr, adrp->ai_addrlen) < 0)
			printf("Error in connecting to server\n");
		return s;
	}
	else {
		printf("We are currently in the IPv4 socket connection\n");
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		if ( pse = getservbyname("daytime", "tcp") )
			sin.sin_port = pse->s_port;
		else
			printf("Error in getting service entry\n");

		if ( phe = gethostbyname(host) )
			memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
		else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE )
			printf("Error not able to get \"%s\" host entry\n", host);

		s = socket(PF_INET, SOCK_STREAM, 0);
		if (s < 0)
			printf("Error in creating socket\n");
		/* Connect the socket */
		if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
			printf("Error in connecting to server\n");
		return s;
	}
}

int main(int argc, char *argv[])
{
	char *host, *type = argv[1];
	printf("Type received is: %c\n", *type);
	if(*type == '6') {
		host = "::1";
		printf("Sending IPv6 request \n");
	}
	else if(*type == '4') {
		host = "localhost";
		printf("Sending IPv4 request \n");
	}
	else {
		printf("Unexpected input for the IP version: %c \n", *type);
	}

	TCPdaytime(host, type);
	exit(0);
}

TCPdaytime(const char *host, char *type)
{
	char buf[LINELEN+1]; /* buffer for one line of text */
	int s, n; /* socket, read count */
	s = connectsock(host, type);
	while( (n = read(s, buf, LINELEN)) > 0) {
		buf[n] = '\0'; /* ensure null-terminated */
		(void) fputs( buf, stdout );
	}
}
