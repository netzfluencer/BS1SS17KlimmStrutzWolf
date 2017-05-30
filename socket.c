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
    int run = 1;

    struct sockaddr_in server;
    struct sockaddr_in client;
    int fileDescriptor;
    char in[2000];
    char out[2000];
    //char in[BUFSIZ]; // Daten vom Client an den Server
    //char out[BUFSIZ]; // Daten vom Server an den Client
    char *in_splitted[3]; //Kommando bei 0, key bei 1, value bei 2
    char *resp = "";
    //char resp[BUFSIZ];


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



    /* Auf Verbindung hören */
    if(listen(sock, 5)<0){
        perror("Error on listening");
    }
    else {
        printf("Listening...\n");
    }




    socklen_t client_len;
    client_len = sizeof(client);

    while(1) {
        /* Verbindung aktzeptieren */
        fileDescriptor = accept(sock, (struct sockaddr *) &client, &client_len);

        int pid = fork();
        if (pid < 0){
            perror("Error on fork");
            exit(1);
        }
        if (pid == 0){

        printf("Connection!\n");
        while(run == 1) {
            read(fileDescriptor, in, 2000);
            // Daten vom Socket ==> in

            //bzero(resp,BUFSIZ);

            // Loeschen des "ENTER"s & des "Carriage Return" (letzte zwei Zeichen)
            in[strlen(in) - 1] = 0;
            in[strlen(in) - 1] = 0;


            // Check: Keine leere Eingabe
            if (strlen(in) > 0) {

                // Splitting von Cmd, Key, Value
                strtoken(in, " ", in_splitted, 3);

                if (strcmp(in_splitted[0], "get") == 0) {
                    // Prüfen ob der key Parameter existiert
                    if (in_splitted[1] != NULL) {

                        //HIER GET FUNKTION AUFRUFEN
                        get(in_splitted[1], (char*) &resp);
                        strcpy(out, "cKey-Action: get\n");
                    } else {
                        strcpy(out, "Err on get: No key submitted\n");
                    }
                } else if (strcmp(in_splitted[0], "put") == 0) {
                    if (in_splitted[1] != NULL) {
                        // Prüfen ob ein value übergeben wurde
                        if (in_splitted[2] != NULL) {

                            // HIER PUT FUNKTION AUFRUFEN
                            put(in_splitted[1], in_splitted[2], (char *) &resp);
                            printf("Alt: %s\n", resp);

                            strcpy(out, "cKey-Action: put\n");
                        } else {
                            strcpy(out, "Err on put: No Value submitted\n");
                        }
                    } else {
                        strcpy(out, "Err on put: No key submitted\n");
                    }
                } else if (strcmp(in_splitted[0], "delete") == 0) {
                    if (in_splitted[1] != NULL) {

                        // HIER DELETE FUNKTION AUFRUFEN
                        delete(in_splitted[1], (char*) &resp);

                        strcpy(out, "cKey-Action: delete\n");
                    } else {
                        strcpy(out, "Err on delete: No key submitted\n");
                    }
                } else if (strcmp(in_splitted[0], "exit") == 0) {
                    run = -1;
                } else {
                    strcpy(out, "Err: Unknown command\n");
                }

                // "in_splitted" chars wieder loeschen und frei machen
                memset(in_splitted[0], 0, strlen(in_splitted[0]));
                if (in_splitted[1] != NULL) memset(in_splitted[1], 0, strlen(in_splitted[1]));
                if (in_splitted[2] != NULL) memset(in_splitted[2], 0, strlen(in_splitted[2]));
            }




            write(fileDescriptor, out, strlen(out)); // Daten vom Array out ==> Socket

            // "in" und "out" chars wieder loeschen und frei machen
            memset(in,0,strlen(in));
            memset(out,0,strlen(out));

        }
        close(fileDescriptor);

    } else close(fileDescriptor);

} return 0;
}

