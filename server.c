#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "logger.h"
#include "common.h"

int main(int argc, char *argv[]) {
    struct sockaddr_in socketaddr;
    char opt;
    int socketfd;
    char *ip = NULL;
    short port = 0;
    char buffer[BUFF_SIZE];

    memset(&socketaddr, 0, sizeof(socketaddr));

    // Create socket file descriptor
    // see man: http://man7.org/linux/man-pages/man2/socket.2.html
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // Check if could create filedescriptor
    if (socketfd < 0) {
        
    }
    // Set up socketaddr with defaults
    socketaddr.sin_family = AF_INET;
    inet_pton(AF_INET, DEFAULT_IP_ADDR, &(socketaddr.sin_addr));

    while ((opt = getopt(argc, argv, "p:i:")) != -1) {
        switch(opt) {
            case 'p':
                socketaddr.sin_port = htons(atoi(optarg));
                break;
            case 'i':
                inet_pton(AF_INET, optarg, &(socketaddr.sin_addr));
                break;
            case '?':
                // printError("Unknown option");
                return 1;
        }
    }

    ip = inet_ntoa(socketaddr.sin_addr);
    port = ntohs(socketaddr.sin_port);

    if (port == 0) {
        fprintf(stderr, "Error: Port not defined\n");
        return 1;
    }
    printf("IP: %s\n", ip);
    printf("Port: %d\n", port);
    

    return 0;
}

