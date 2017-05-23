//
// Created by User on 22.05.2017.
//


#include "socket.h"

int start(){
    /* Variablen für den Server */
    int sock;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int fileDescriptor;

    printf("Starting cKey-Server...\n");

    /* Anlegen eines Sockets */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("creating stream socket");
        exit(2);
    }
    printf("Socket created.\n");

    /* Binden eines Sockets */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(4711);
    bind( sock, (struct sockaddr *) &server, sizeof(server));
    printf("Socket binded.\n");

    /* Auf Verbindung hören */
    listen(sock, 5);
    printf("Listening...\n");

    /* Verbindung aktzeptieren */
    socklen_t client_len;
    client_len = sizeof(client);

    fileDescriptor = accept(sock, (struct sockaddr*)&client, &client_len);
    printf("Connection!\n");
}

