#include <stdlib.h>
#include <memory.h>
#include "socket.h"

int strtoken(char *str, char *separator, char **token, int size) {
    int i=0;
    token[0] = strtok(str, separator);
    while(token[i++] && i < size)
        token[i] = strtok(NULL, separator);
    return (i);
}

int start(){
    /* Variablen für den Server */
    int sock;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int fileDescriptor;
    char in[2000]; // Daten vom Client an den Server
    char out[2000]; // Daten vom Server an den Client
    char *in_splitted[3]; //Kommando bei 0, key bei 1, value bei 2


    printf("Starting cKey-Server...\n");



    /* Anlegen eines Sockets */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("creating stream socket");
        exit(1);
    }
    else {
        printf("Socket created.\n");
    }


    int option = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    /* Binden eines Sockets */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(1996);

    if(bind( sock, (struct sockaddr *) &server, sizeof(server))<0){
        perror("Error on binding");
    }
    else {
        printf("Socket binded.\n");
    }

    //Shared Memory erstellen
    shmem();



    /* Auf Verbindung hören */
    if(listen(sock, 5)<0){
        perror("Error on listening");
    }
    else {
        printf("Listening...\n");
    }




    /* Verbindung aktzeptieren */
    socklen_t client_len;
    client_len = sizeof(client);

    while(1) {
        fileDescriptor = accept(sock, (struct sockaddr *) &client, &client_len);
        printf("Connection!\n");
        while(read(fileDescriptor, in, 2000) > 0) {
            // Daten vom Socket ==> in

            // Loeschen des "ENTER"s
            strtok(in, "\n");

            // Splitting von Cmd, Key, Value
            strtoken(in, " ", in_splitted, 3);

            printf("Eingabe: %s\n", in);
            printf("Befehl: %s\n", in_splitted[0]);
            printf("Key: %s\n", in_splitted[1]);
            printf("Value: %s\n", in_splitted[2]);



            // Hier wird nun mit den Daten des Clients gearbeitet.






            //Nach Befehl Ausführung in und in_splitted chars wieder loeschen und frei machen
            memset(in,0,strlen(in));
            memset(in_splitted[0],0,strlen(in_splitted[0]));
            memset(in_splitted[1],0,strlen(in_splitted[1]));
            memset(in_splitted[2],0,strlen(in_splitted[2]));
            // write(fileDescriptor, out, 2000); // Daten vom Array out ==> Socket
        }
        close(fileDescriptor);
    }
    return 0;
}

