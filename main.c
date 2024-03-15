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

int main(int argumentsCount, char *arguments[]) {
    if (argumentsCount != 3) {
        fprintf(stderr, "Usage: %s <destination IP> <message>\n", arguments[0]);
        return 1;
    }

    int s;
    int numbytes;

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof hints); // Initialize hints
    hints.ai_family = AF_UNSPEC; // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM; // Datagram socket

    int status = getaddrinfo(arguments[1], "4950", &hints, &servinfo);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    // Iterate through all the results and make a socket
    for (p = servinfo; p != NULL; p = p->ai_next) {
        s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (s == -1) {
            perror("socket");
            continue;
        }
        break; // If we successfully create a socket, exit the loop
    }

    if (p == NULL) {
        fprintf(stderr, "Failed to create socket\n");
        return 1;
    }

    // Send the message
    numbytes = sendto(s, arguments[2], strlen(arguments[2]), 0, p->ai_addr, p->ai_addrlen);
    if (numbytes == -1) {
        perror("sendto");
        return 1;
    }

    printf("Sent %d bytes to %s\n", numbytes, arguments[1]);

    freeaddrinfo(servinfo);
    close(s);

    return 0;
}