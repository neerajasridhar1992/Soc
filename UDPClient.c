/*
 This is the simple UDP Client
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define SERVERIP "127.0.0.1"
/* The below defines the maximum length of the buffer */
#define MAXBUFFLEN 512  
#define CLIENTPORT 8888   
/*The port on which to send data to the server */
 
void die(char *m)
{
    perror(m);
    exit(1);
}
 
int main(void)
{
    struct sockaddr_in soc_udp;
    int m, i, slen=sizeof(soc_udp);
    char buf[MAXBUFFLEN];
    char message[MAXBUFFLEN];
 
    if ( (m=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &soc_udp, 0, sizeof(soc_udp));
    soc_udp.sin_family = AF_INET;
    soc_udp.sin_port = htons(CLIENTPORT);
     
    if (inet_aton(SERVERIP , &soc_udp.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
 
    while(1)
    {
        printf("Enter the message you want to send server : ");
        gets(message);
         
        //send the message
        if (sendto(m, message, strlen(message) , 0 , (struct sockaddr *) &soc_udp, slen)==-1)
        {
            die("sendto()");
        }
         
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', MAXBUFFLEN);
        //try to receive some data, this is a blocking call
        if (recvfrom(m, buf, MAXBUFFLEN, 0, (struct sockaddr *) &soc_udp, &slen) == -1)
        {
            die("recvfrom()");
        }
         
        puts(buf);
    }
 
    close(m);
    return 0;
}
