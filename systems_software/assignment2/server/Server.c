#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include "date.h"
#include "manager.h"

#define PORT 4452

int main() {
    int count = 0;
    pthread_t tid[count];
    int socket_desc, client_sock , c;
    struct sockaddr_in server, client;
     
    // Creating server socket
    socket_desc = socket(AF_INET, SOCK_STREAM , 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    printf("Socket created");
     
    // sockaddr_in configuration
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
     
    // Bind the socket connection
    if(bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("Bind");
        return 1;
    }
    puts("\nBind Completed");

    // Listen for the socket connection
    listen(socket_desc , 3);    
    printf("Server running\n\n");
    printf("Listening for connections......\n\n");

    // Initialise the thread to be used
    c = sizeof(struct sockaddr_in);
		pthread_t thread_id;

    // Accept new connections by creating a new socket for new client by implementing threads
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
        // Display No. of connection using counter
        count += 1;
        printf("\nNew connection accepted");
        printf("\nJob %d started\n", count);
         
        if( pthread_create( &thread_id, NULL, manager, (void*) &client_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
        printf("Handler assigned\n\n");
    }
     
    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }
     
    return 0;
}