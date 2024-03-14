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
    hints.ai_family = AF_INET; // IPv4

    hints.ai_socktype = SOCK_DGRAM;

    int a = getaddrinfo(arguements[1], "4950", &hints, &servinfo);
    if(a == 0){
        printf("got something!!!\n");

        for(p = servinfo; p!= NULL; p = p->ai_next){
            s = socket(p->ai_family, p->ai_socktype,p->ai_protocol)

            if(s > -1){
                break;
            }
            printf("nah\n");
            
        }


    } else {
        printf("womp womp\n");
    }



if (p == NULL) {
		fprintf(stderr, "talker: failed to create socket\n");
		return 2;
	}

	if ((numbytes = sendto(s, argv[2], strlen(argv[2]), 0,
			 p->ai_addr, p->ai_addrlen)) == -1) {
		perror("talker: sendto");
		exit(1);
	}

	freeaddrinfo(servinfo);

	printf("talker: sent %d bytes to %s\n", numbytes, argv[1]);
	close(s);


    //get addressinfo

    return 0;
}