#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define PORT 4452
#define FILE_SIZE 512
#define PATH_SIZE 500
#define CLIENT_STORAGE "./storage/"

int main() {
    int sfd = 0, b;
    char rbuff[1024];
    char sendbuffer[100];
    char client_message[100], option[10], username[10], password[10], response[10];
    char file[300], file_path[50], choice2[20], file_dir[FILE_SIZE];
    char server_path[50];
    char message[300], message2[50];
    FILE *fp;

    // Configure the client connection
    struct sockaddr_in serverAddr;
    memset(rbuff, '0', sizeof(rbuff));
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    b = connect(sfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (b ==- 1) {
        perror("Connect");
        return 1;
    }

    // Send a 'LOGIN' message to the server to keep track of which functionality it's executing
    send(sfd, "LOGIN", strlen("LOGIN"), 0);

    printf("Username: ");
    scanf("%s", username);
    send(sfd, username, strlen(username), 0);

    printf("Password: ");
    scanf("%s", password);
    send(sfd, password, strlen(password), 0);

    // Receive Authentication
    recv(sfd, response, 10, 0);
    if (strcmp(response, "200") == 0) {
        puts("\nLogin Successful\n");
    }
    else {
        puts("\nLogin Unsuccessful\n");
        return 1;
    }

    while(1) {
        puts("Menu:\n 1: Transfer File \n 2: Logout \n Select Option: ");
        scanf("%s", option);

        if (strcmp(option, "1") == 0) {

            printf("Starting transfer\n");
            // Send a 'TRANSFER' message to the server to keep track of which functionality it's executing
            send(sfd, "TRANSFER", strlen("TRANSFER"), 0);

            printf("Please enter the file name\n");
            scanf("%s", message);
            send(sfd, message, strlen(message), 0);      

            printf("\nPlease enter the files destination\n1) root\n2) sales\n3) promotions\n4) offers\n5) marketing\n6) exit\n");
            scanf("%s", server_path);       

            if (strcmp(server_path, "1") == 0) {
                strcpy(message2, "intranet");
            } else if (strcmp(server_path, "2") == 0) {
                strcpy(message2, "sales");
            } else if (strcmp(server_path, "3") == 0) {
                strcpy(message2, "promotions");
            } else if (strcmp(server_path, "4") == 0) {
                strcpy(message2, "offers");
            } else if (strcmp(server_path, "5") == 0) {
                strcpy(message2, "marketing");
            } else if (strcmp(server_path, "6") == 0) {
                printf("\nExiting\n");
                return 0;
            } else {
                printf("\nInput was not an option");
                return 1;
            }
            // Send the chosen directory path to the server
            send(sfd, message2, strlen(message2), 0);
            
            // Receive the repsonse & display to the client if they have invalid permissions
            recv(sfd, response, 10, 0);
            if (strcmp(response, "200") == 0) {
                puts("\nChosen Directory sent Successful");
            } else {
                printf("\n *** Invalid Permissions *** \n");
                return 0;
            }

            FILE *fp = fopen(message, "r");
            if(fp == NULL){
                perror("File");
                return 0;
            }
            strcat(file, "?");
            
            strcpy(sendbuffer, message);
            send(sfd, sendbuffer, sizeof(sendbuffer), 0);
            bzero(sendbuffer, sizeof(sendbuffer));
            recv(sfd, sendbuffer,300, 0);
            bzero(sendbuffer, sizeof(sendbuffer));

            // After opening the chosen file, send its contents to the server
            while((b = fread(sendbuffer, sizeof(char), sizeof(sendbuffer), fp))>0 ){
                send(sfd, sendbuffer, b, 0);
                bzero(sendbuffer, sizeof(sendbuffer));
            }

            // Resceive & handle whether the transfer has been a success
            recv(sfd, response, 10, 0);
            if (strcmp(response, "200") == 0) {
                printf("\n *** Transfer Successful *** \n\n");
            } else {
                printf("\n *** Transfer Failure *** \n");
                return 0;
            }
            fclose(fp);
            
        } 
        // Log Client Out & Close connection
        else if (strcmp(option, "2") == 0) {
            printf("\n *** Closing Client *** \n");
            close(sfd);
            return 0;
        } 
        else {
            puts("\nEnter Valid Option");
        }
    }
}