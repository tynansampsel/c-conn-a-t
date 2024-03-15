#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argumentsCount, char *arguements[]){
    
    //argument 1 is destination IP (ipv4)
    //argument 2 is message
    
    //prepare address information

	int sockfd;
	int numbytes;

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof hints); // Initialize hints
    //hints.ai_family = AF_INET; // IPv4
    //hints.ai_socktype = SOCK_DGRAM;

    int a = getaddrinfo(arguements[1], "4950", &hints, &servinfo);
    if(a == 0){
        printf("got something!!!\n");

        for(p = servinfo; p != NULL; p = p->ai_next){
            sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol);

            if(sockfd > -1){
                break;
            }
            printf("nah\n");
        }
    } else {
        printf("womp womp\n");
    }

    numbytes = sendto(sockfd, arguements[2], strlen(arguements[2]), 0, p->ai_addr, p->ai_addrlen);


    //freeaddrinfo(servinfo);
    printf("Sent!\n");

    //close(s);


    //int sockfd;
	//int rv;
	//int numbytes;

	struct sockaddr_storage their_addr;
	char buf[100];
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];

    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;


    //int r = getaddrinfo(NULL, "4950", &hints, &servinfo);
    int b = bind(sockfd, p->ai_addr, p->ai_addrlen);
          

    freeaddrinfo(servinfo);

    addr_len = sizeof their_addr;
    numbytes = recvfrom(sockfd, buf, 99 , 0, (struct sockaddr *)&their_addr, &addr_len);

    printf("listener: got packet from %s\n",
            inet_ntop(their_addr.ss_family,
                get_in_addr((struct sockaddr *)&their_addr),
                s, sizeof s));
    printf("listener: packet is %d bytes long\n", numbytes);
    buf[numbytes] = '\0';
    printf("listener: packet contains \"%s\"\n", buf);

    close(sockfd);
    
    //get addressinfo

    return 0;
}


void *get_in_addr(struct sockaddr *sa)
{
	return &(((struct sockaddr_in*)sa)->sin_addr);
}
