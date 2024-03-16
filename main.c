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

void *get_in_addr(struct sockaddr *sa)
{
	return &(((struct sockaddr_in*)sa)->sin_addr);
}

int main(int argumentsCount, char *arguements[]){
    
    sendMessage(arguements[1], arguements[2]);

    char requestIp[INET6_ADDRSTRLEN];
    waitForMessage(&requestIp);

    return 0;
}

int waitForMessage(char requestIp[]){
    printf("waiting for response...\n");
	int numbytes;

    int sockfd;
	struct addrinfo hints, *servinfo, *p;

	struct sockaddr_storage their_addr;
	socklen_t addr_len;
	char buf[100];

    memset(&hints, 0, sizeof hints);
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    int getaddrinfoResult = getaddrinfo(NULL, "4950", &hints, &servinfo);
    if(getaddrinfoResult != 0){
        printf("Could not get address information!\n");
        return 1;
    }
    
    for(p = servinfo; p != NULL; p = p->ai_next){
        sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol);

        if((sockfd) > -1){
            int b = bind(sockfd, p->ai_addr, p->ai_addrlen);
            break;
        }
    }
    if (p == NULL) {
        printf("Could not create a socket!\n");
        return 1;
    }

    addr_len = sizeof their_addr;

    
    int recvfromResult = recvfrom(sockfd, buf, 99 , 0, (struct sockaddr *)&their_addr, &addr_len);
    if (recvfromResult == -1) {
		printf("Could not get socket information!\n");
        return 1;
	}
    
    printf("they responded!\n");
    printf("they said %s\n", buf);

    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), requestIp, sizeof requestIp);

    freeaddrinfo(servinfo);
    close(sockfd);
    return 0;
}


int sendMessage(char ip[], char message[]){
    int sockfd;
    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof hints); // Initialize hints
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_DGRAM;

    int getaddrinfoResult = getaddrinfo(ip, "4950", &hints, &servinfo);
    if(getaddrinfoResult != 0){
        printf("Could not get address information!\n");
        return 1;
    }

    for(p = servinfo; p != NULL; p = p->ai_next){
        sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol);
        if(sockfd != -1){
            break;
        }
    }
    if (p == NULL) {
        printf("Could not create a socket!\n");
        return 1;
    }

    int sendtoResult = sendto(sockfd, message, strlen(message), 0, p->ai_addr, p->ai_addrlen);
    if (sendtoResult == -1) {
		printf("Could not send message!\n");
        return 1;
	}

    freeaddrinfo(servinfo);
    close(sockfd);
    printf("asking for a cookie!\n");
}