#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <winsock2.h> würde bis auf Zeile 55 bei windows alles zum laufen bringen

#include "store_tools.h"


int main() {
    struct key_value kv[10];
    put(8, (char*)'dasd', kv);
    get(8, kv);
    delete(8, kv);




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


    return 0;

}