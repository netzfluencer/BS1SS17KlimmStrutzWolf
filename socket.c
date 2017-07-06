#include "socket.h"
#include "persistent.h"

int strtoken(char *str, char *separator, char **token, int size) {
    int i = 0;
    token[0] = strtok(str, separator);
    while (token[i++] && i < size)
        token[i] = strtok(NULL, separator);
    return (i);
}

int start() {
    /* Variablen für den Server */
    int sock, sem_id, mutex, runput, rundel;
    int run = 1;
    unsigned short marker[1], markerM[1];
    sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0644);
    if (sem_id == -1) {
        printf("Die Gruppe konnte nicht angelegt werden!\n");
        exit(1);
    }
    marker[0] = 1;
    semctl(sem_id, 1, SETALL, marker);

    mutex = semget(IPC_PRIVATE, 1, IPC_CREAT | 0644);
    if (mutex == -1) {
        printf("Die Gruppe konnte nicht angelegt werden!\n");
        exit(1);
    }
    markerM[0] = 1;
    semctl(mutex, 0, SETALL, markerM);

    struct sockaddr_in server;
    struct sockaddr_in client;
    int fileDescriptor;
    char in[2000];
    char out[2000];
    //char in[BUFSIZ]; // Daten vom Client an den Server
    //char out[BUFSIZ]; // Daten vom Server an den Client
    char *in_splitted[3]; //Kommando bei 0, key bei 1, value bei 2
    char savefile[BUFSIZ];
    char resp[BUFSIZ];


    printf("Starting cKey-Server...\n");



    /* Anlegen eines Sockets */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("creating stream socket");
        exit(1);
    } else {
        printf("Socket created.\n");
    }


    int option = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    /* Binden eines Sockets */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(1996);

    if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Error on binding");
    } else {
        printf("Socket binded.\n");
    }

    /* Nach persistenten Daten suchen */
    auslesen(savefile);

    /* Store füllen mit Daten */
    fillStore(savefile);

    /* Auf Verbindung hören */
    if (listen(sock, 5) < 0) {
        perror("Error on listening");
    } else {
        printf("Listening...\n");
    }

    /* Verbindung aktzeptieren */
    socklen_t client_len;
    client_len = sizeof(client);

    while (1) {
        fileDescriptor = accept(sock, (struct sockaddr *) &client, &client_len);
        int pid = fork();
        if (pid < 0) {
            perror("Error on fork");
            exit(1);
        }
        if (pid == 0) {

            struct sembuf enter, leave; //structs für up und down
            enter.sem_num, leave.sem_num = 0;
            enter.sem_flg, leave.sem_flg = SEM_UNDO;
            enter.sem_op = -1; //blockieren, DOWN
            leave.sem_op = 1; //freigeben, UP
            printf("Connection!\n");
            while (run == 1) {
                bzero(in, 2000);
                read(fileDescriptor, in, 2000);
                // Daten vom Socket ==> in



                // Loeschen des "ENTER"s & des "Carriage Return" (letzte zwei Zeichen)
                in[strlen(in) - 1] = 0;
                in[strlen(in) - 1] = 0;


                // Check: Keine leere Eingabe
                if (strlen(in) > 0) {

                    // Splitting von Cmd, Key, Value
                    strtoken(in, " ", in_splitted, BUFSIZ);

                    if (strcmp(in_splitted[0], "get") == 0) {
                        // Prüfen ob der key Parameter existiert
                        if (in_splitted[1] != NULL) {
                            semop(mutex, &enter, 1);
                            *rc = *rc + 1;
                            if(*rc == 1) {
                                semop(sem_id, &enter, 1); //In den krit. Bereich
                            }
                            //printf("Einer da\n"); Tester
                            semop(mutex, &leave, 1);
                            //sleep(10); tester für raceconditions
                            get(in_splitted[1], resp);
                            semop(mutex, &enter, 1);
                            *rc = *rc - 1;
                            if (*rc == 0){
                                semop(sem_id, &leave, 1);
                            }
                            semop(mutex, &leave, 1);

                            char strget[BUFSIZ] = "cKey-Action: get\n";
                            strcpy(out, strcat(strget, resp));
                        } else {
                            strcpy(out, "Err on get: No key submitted\n");
                        }
                    } else if (strcmp(in_splitted[0], "put") == 0) {
                        if (in_splitted[1] != NULL) {
                            // Prüfen ob ein value übergeben wurde
                            if (in_splitted[2] != NULL) {
                                char valueStr[80];
                                // Check if value starts with " - Ascii 34
                                if (in_splitted[2][0] == 34) {
                                    in_splitted[2]++;
                                    int counter = 2;
                                    strcpy(valueStr, "");
                                    while(counter > 0) {

                                        if(in_splitted[counter][strlen(in_splitted[counter])-1] == 34) {
                                            in_splitted[counter][strlen(in_splitted[counter])-1] = 0;
                                            strcat(valueStr, in_splitted[counter]);
                                            strcpy(in_splitted[2], valueStr);
                                            counter = -1;
                                        }

                                        else {
                                            strcat(valueStr, in_splitted[counter]);
                                            strcat(valueStr, " ");
                                            counter++;
                                        }
                                    }


                                }

                                runput = 0;
                                while(runput == 0){
                                semop(mutex, &enter, 1); //In den krit. bereich LeserSchreiber
                                if(*rc == 0) {
                                    semop(sem_id, &enter, 1); //In den krit. Bereich
                                    runput = -1;
                                }
                                semop(mutex, &leave, 1); //Aus dem dem krit. Bereich LeserSchreiber

                                }

                                put(in_splitted[1], in_splitted[2], resp);

                                semop(sem_id, &leave, 1); //Aus dem krit. Bereich

                                char strput[BUFSIZ] = "cKey-Action: put\n";
                                strcpy(out, strcat(strput, resp));
                            } else {
                                strcpy(out, "Err on put: No Value submitted\n");
                            }
                        } else {
                            strcpy(out, "Err on put: No key submitted\n");
                        }
                    } else if (strcmp(in_splitted[0], "delete") == 0) {
                        if (in_splitted[1] != NULL) {
                            rundel = 0;
                            while(rundel == 0){
                                semop(mutex, &enter, 1);
                                if(*rc == 0) {
                                    semop(sem_id, &enter, 1); //In den krit. Bereich
                                    rundel = -1;
                                }
                                semop(mutex, &leave, 1);

                            }

                            delete(in_splitted[1], resp);

                            semop(sem_id, &leave, 1); //Aus dem krit. Bereich

                            char strdel[BUFSIZ] = "cKey-Action: delete\n";
                            strcpy(out, strcat(strdel, resp));

                        } else {
                            strcpy(out, "Err on delete: No key submitted\n");
                        }
                    } else if (strcmp(in_splitted[0], "exit") == 0) {
                        schreiben();
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
                memset(in, 0, strlen(in));
                memset(out, 0, strlen(out));

            }
            close(fileDescriptor);
        } else close(fileDescriptor);

    }
    return 0;
}

