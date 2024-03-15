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

	int s;
	int numbytes;

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof hints); // Initialize hints
    //hints.ai_family = AF_INET; // IPv4
    //hints.ai_socktype = SOCK_DGRAM;

    int a = getaddrinfo(arguements[1], "4950", &hints, &servinfo);
    if(a == 0){
        printf("got something!!!\n");

        for(p = servinfo; p != NULL; p = p->ai_next){
            printf("a-\n");

            s = socket(p->ai_family, p->ai_socktype,p->ai_protocol);
            printf("a0\n");

            if(s > -1){
                break;
                printf("a1\n");

            }
            printf("nah\n");
        }
        printf("a2\n");

    } else {
        printf("womp womp\n");
    }
    printf("a3\n");


    if (p == NULL) {
        fprintf(stderr, "Failed to create socket\n");
        return 1;
    }

    numbytes = sendto(s, arguements[2], strlen(arguements[2]), 0, p->ai_addr, p->ai_addrlen);
    if (numbytes == -1) {
        printf("n\n");

		perror("talker: sendto");
		exit(1);
	} else {
        printf("y\n");

    }

    printf("a4\n");


    freeaddrinfo(servinfo);
    printf("Sent!\n");

    close(s);


    //get addressinfo

    return 0;
}