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
#include "server.h"

int main(int argc, char *argv[]) {
    struct sockaddr_in socketaddr;
    char opt;
    int socketfd;
    char *ip = NULL;
    short port = 0;

    // Create socket file descriptor
    // see man: http://man7.org/linux/man-pages/man2/socket.2.html
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // Initialize all values of struct to zero
    memset(&socketaddr, 0, sizeof(socketaddr));
    // Default ip (127.0.0.1)
    inet_pton(AF_INET, DEFAULT_IP_ADDR, &(socketaddr.sin_addr));
    // Set up port
    socketaddr.sin_port = htons(port);
    // Set up socketaddr with defaults
    socketaddr.sin_family = AF_INET;
    // Check if could create filedescriptor
    if (socketfd < 0) {
        printError("Could not create server file descriptor");
        return 1;
    }

    while ((opt = getopt(argc, argv, "p:i:")) != -1) {
        switch(opt) {
            case 'p':
                port = atoi(optarg);
                break;
            case 'i':
                // We put ip directly to avoid use strcopy (vuln.)
                inet_pton(AF_INET, optarg, &(socketaddr.sin_addr));
                break;
            case '?':
                // printError("Unknown option");
                return 1;
        }
    }

    ip = inet_ntoa(socketaddr.sin_addr);

    if (port == 0) {
        printError("Port not defined");
        return 1;
    }

    if (bind(socketfd, (struct sockaddr *) &socketaddr, sizeof(socketaddr)) < 0) {
        printError("Could not bind socket");
        return 1;
    }

    if (listen(socketfd, MAX_CONN) < 0) {
        printError("Could not listen");
        return 1;
    }

    char listen_msg[50];
    sprintf(listen_msg, "Listening on %s:%d", ip, port);
    printMsg("TCP Server", listen_msg);

    struct sockaddr_in clientaddr;
    // Initialize all values of struct to zero
    memset(&clientaddr, 0, sizeof(clientaddr));

    // Main loop
    while(1) {
        int clientfd = accept(socketfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
        if (clientfd < 0) {
            printError("Could not create client file descriptor");
            // return 1;
            continue;
        }
        char *client_ip = inet_ntoa(clientaddr.sin_addr);
        char buffer[BUFF_SIZE];
        char client_msg[50];
        ssize_t recv_len = 0;

        sprintf(client_msg, "Client connected from ip --> %s", client_ip);
        printMsg("TCP Server", client_msg);
        while((recv_len = recv(clientfd, buffer, BUFF_SIZE)) > 0) {
            printMsg("Client", buffer);
        }

        close(clientfd);
    }

    // Close file descriptor
    close(socketfd);

    return 0;
}

