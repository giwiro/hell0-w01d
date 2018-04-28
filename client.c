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
    struct sockaddr_in server_address;
    char opt;
    int socketfd;
    char *ip = DEFAULT_IP_ADDR;
    short port = 0;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0) {
        printError("Could not create file descriptor");
        return 1;
    }

    // Initialize server_address struct values to zero
    memset(&server_address, 0, sizeof(server_address));
    // Set address family
    server_address.sin_family = AF_INET;
    // Set default ip
    inet_pton(AF_INET, DEFAULT_IP_ADDR, &(server_address.sin_addr));


    while ((opt = getopt(argc, argv, "p:i:")) != -1) {
        switch(opt) {
            case 'p':
                port = atoi(optarg);
                break;
            case 'i':
                // We put ip directly to avoid use strcopy (vuln.)
                inet_pton(AF_INET, optarg, &(server_address.sin_addr));
                break;
            case '?':
                // printError("Unknown option");
                return 1;
        }
    }

    ip = inet_ntoa(server_address.sin_addr);

    if (port == 0) {
        printError("Port not defined");
        return 1;
    }

    server_address.sin_port = htons(port);

    // Connect to socket
    if (connect(socketfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        printError("Could not connect to host");
        return 1;
    }

    char message[BUFF_SIZE] = "Hello mother fucker\0";
    send(socketfd, message, BUFF_SIZE, 0);

    // close socket
    close(socketfd);
}