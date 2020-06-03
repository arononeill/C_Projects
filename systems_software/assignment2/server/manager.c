#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "date.h"

#define LOG_DIR "./storage/log.txt"
#define CRED_DIR "./storage/loginCredentials.txt"
#define GROUP_DIR "./storage/groupList.txt"
#define MSG_SIZE 200
#define PATH_SIZE 200
#define FILE_SIZE 512

char delimiter[] = "?";
pthread_mutex_t lock;

void *manager(void *socket_desc) {

    // Defined variables for handling socket connection function
    int socket = *(int*)socket_desc;
    int read_size, bytes, verified = 0, userFound = 0;
    FILE *fp;
    char *message;
    char file_name[300], file_path[50], client_message[MSG_SIZE],
    server_filepath[PATH_SIZE], file_buffer[PATH_SIZE];
    char * dateBuffer[80], username[50], logPath[50], logFile[50], password[50], choice2[50], file[15],  client_filename[MSG_SIZE], client_filepath[MSG_SIZE];
    char * date = getDate(dateBuffer);

    // Base path for saving files to server
    char base_path[200] = "/home/ubunutu/Documents/systems_software/assignment_02/server/intranet/";

    // Variables to be read in user & group credentials
    char user_auth[50], pass_auth[50], group_auth[50], guid_auth[50], users_auth[50], line[500], userUID[50];

    while((read_size = recv(socket, client_message, MSG_SIZE, 0)) > 0) {

        // Login Functionality
        if (strcmp(client_message, "LOGIN") == 0) {
            printf("Login Started");

            // Server recevies user inputted username & password
            recv(socket, username, 50, 0);
            recv(socket, password, 50, 0);

            // Opens the loginCredentials.txt & error checks
            FILE *cred_file = fopen(CRED_DIR, "r");
            if (cred_file == NULL) {
                printf("Error opening userCredentials file\n");
                exit(1);
            }

            // Reads each line to check if the details entered are valid
            while (fgets(line, 80, cred_file)) {
                sscanf(line, "username: %s password: %s UserUID: %s", user_auth, pass_auth, userUID);

                // Compares users details with stored users
                if((strcmp(username, user_auth) == 0) && (strcmp(password, pass_auth) == 0)) {
                    userFound = 1;
                }
            }
            fclose(cred_file);

            // Sends the appropriate resposne to the client if the user was found
            if (userFound == 1) {
                send(socket, "200", sizeof("200"), 0);
            } else {
                send(socket, "401", sizeof("401"), 0);
                puts("\nLogin Aborted");
                pthread_exit(NULL);
            }
            printf("\nLogin Completed\n");
        }
    
        // Transfer Functionality
        if (strcmp(client_message, "TRANSFER") == 0) {
            puts("Transfer Started");

            // Receive & Handle filename & path 
            if ((bytes = recv(socket, client_filename, MSG_SIZE, 0)) == 0) {
                printf("No data recevied");
                free(socket_desc);
                pthread_exit(NULL);
                send(socket, "401", sizeof("401"), 0);
                puts("Transfer Aborted");
            }

            if ((bytes = recv(socket, client_filepath, MSG_SIZE, 0)) == 0) {
                printf("No data recevied");
                free(socket_desc);
                pthread_exit(NULL);
                send(socket, "401", sizeof("401"), 0);
                puts("Transfer Aborted");
            }

            if (strstr(client_filepath, "intranet") != 0) {
                strcpy(client_filepath, "intranet");
            } else if (strstr(client_filepath, "sales") != 0) {
                strcpy(client_filepath, "sales");
            } else if (strstr(client_filepath, "promotions") != 0) {
                strcpy(client_filepath, "promotions");
            } else if (strstr(client_filepath, "offers") != 0) {
                strcpy(client_filepath, "offers");
            } else if (strstr(client_filepath, "marketing") != 0) {
                strcpy(client_filepath, "marketing");
            } else {
                printf("\nError recognising path");
            }

            printf("\nFile name: %s", client_filename);
            printf("\nFile path: %s\n", client_filepath);

            // Open groups file needed to check privileges
            FILE *group_file = fopen(GROUP_DIR, "r");
            if (group_file == NULL) {
                printf("Error opening userCredentials file\n");
                exit(1);
            }
            while (fgets(line, 80, group_file)) {
                sscanf(line, "group: %s gUID: %s users: %s", group_auth, guid_auth, users_auth);

                // Checks if the group read in matches the users directory choice
                if((strcmp(client_filepath, group_auth) == 0)) {
                    printf("\n%s Group Users: %s\n%s Group IDs: %s\n", client_filepath, users_auth, client_filepath, guid_auth);                    
                    
                    // Checks if the chosen group contains the current user's GUID
                    if(strstr(guid_auth, userUID) != 0) {
                        verified = 1;
                    }
                }        
            }
            fclose(group_file);

            // If the user has the required privileges
            if (verified == 1) {
                /* Used to lock the thread to ensure other clients can't access the thread and
                   modify data at the same time so that each thread will have to be seperate 
                   for each user */
                pthread_mutex_lock(&lock);

                uid_t uid = getuid();
                uid_t gid = getgid();
                uid_t ueid = geteuid();
                uid_t geid = getegid();

                // Display original file owner UIDs
                printf("\nOriginal File Owner IDs are:\nUser ID: %d\n", uid);
                printf("Group ID: %d\n", gid);
                printf("E User ID: %d\n", ueid);
                printf("E Group ID: %d\n", geid);
                
                int myUID = atoi(userUID);
                printf("Current User UID is %d\n", myUID);

                // Set current user's UID as file owner UIDs
                setreuid(myUID, uid);
                setregid(myUID, gid);
                seteuid(myUID);
                setegid(myUID);

                printf("\nNew File Owner IDs are:\nUser ID: %d\n", getuid());
                printf("Group ID: %d\n", getgid());
                printf("E User ID: %d\n", geteuid());
                printf("E Group ID: %d\n", getegid());

                //Create Server Path needed to transfer
                strcpy(server_filepath, base_path);

                // Modifies the created file path based on if they have selected intranet folder or not
                if((strcmp(client_filepath, "intranet") != 0)) {
                    strcat(server_filepath, client_filepath);
                    strcat(server_filepath, "/");
                }
                strcat(server_filepath, client_filename);
                printf("\nserver_filepath: %s", server_filepath);
                send(socket, "200", sizeof("200"), 0);

                printf("\nReceiving filename from client\n");
                recv(socket, client_message, sizeof(client_message), 0);
                char testFileName[20];
                strcpy(testFileName, client_message);
                client_message[0] = 1;
                send(socket, client_message, sizeof(client_message), 0);
                bzero(client_message, sizeof(client_message));

                strcpy(logPath, client_filepath);
                strcpy(logFile, client_filename);

                // Read in the file to be transferred contents
                while((read_size = recv(socket, client_message, 2000, 0)) > 0)
                {
                    char *ptr = strtok(client_message, delimiter);
                    strcat(base_path, testFileName);

                    // Write to the desired path created previously
                    fp = fopen(server_filepath, "w");
                    
                    if(fp != NULL) {
                        fwrite(client_message, sizeof(char), read_size, fp);
                        send(socket, "200", sizeof("200"), 0);
                    }
                    else {
                        perror("File Write");
                    }
                    fclose(fp);

                    write(socket, client_message, strlen(client_message));
                    memset(client_message, 0, 2000);
                
                } // end while

                /* Unlocks the thread to allow other client's to transfer their file using 
                   another created thread */
                pthread_mutex_unlock(&lock);
                
                fwrite(client_message, sizeof(char), read_size, fp);
                printf("\nSuccessfully transfered file\n");
                
                char breakline[] = "-----------------------------------------";
                FILE *fptr2;
                // Open the file used to log transfer details
                fptr2 = fopen(LOG_DIR, "a");
                if(fptr2 == NULL) {
                    printf("Error");
                    exit(1);
                }

                // Log the current user's details & date
                fprintf(fptr2, "\nUser: %s", username);
                fprintf(fptr2, "\nDate: %s", date);
                fprintf(fptr2, "\nUpdated File: %s", logFile);
                fprintf(fptr2, "\nUpdated Directory: %s", logPath);
                fprintf(fptr2, "\n%s", breakline);
                fclose(fptr2);
            }
            else {
                // Display Incorrect Permissions to the server & send to client
                printf("\n *** Incorrect Permissions *** \n");
                printf("\nClient Disconnecting\n");
                send(socket, "401", sizeof("401"), 0);
            }
        }
    }
    pthread_exit(NULL);
}