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
    struct addrinfo adinf, *linkedListP, *adinfP;
    char service;
    adinf->ai_socktype = SOCK_DGRAM

    int a = getaddrinfo(arguements[1], "4950", adinf, &linkedListP)
    if(a == 0){
        printf("got something!!!\n")



    } else {
        printf("womp womp\n")

    }

    //get addressinfo

    return 0;
}