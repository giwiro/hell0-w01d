#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
// #include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <netdb.h>

#define DEFAULT_IP_ADDR "127.0.0.1"

int main(int argc, char *argv[]) {
    struct sockaddr_in socketaddr;
    char opt;
    char *ip = NULL;

    memset(&socketaddr, 0, sizeof(socketaddr));

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
                fprintf(stderr, "Unknown option\n");
                break;
        }
    }

    ip = inet_ntoa(socketaddr.sin_addr);
    printf("IP: %s\n", ip);
}

