#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include "comands.h"
#include "parser.h"
#include <ctype.h>
#include <stdlib.h>

int sendCommand(int sockfd, const char *command) {
    int bytes = write(sockfd, command, strlen(command));
    if (bytes < 0) {
        perror("write()");
        close(sockfd);
        return 1;
    }
    return 0;
}

int sendUser(int sockfd, const char *username) {
    char buf[64];
    snprintf(buf, sizeof(buf), "USER %s\r\n", username);
    return sendCommand(sockfd, buf);
}

int sendPass(int sockfd, const char *password) {
    char buf[64];
    snprintf(buf, sizeof(buf), "PASS %s\r\n", password);
    return sendCommand(sockfd, buf);
}

int sendPasv(int sockfd) {
    return sendCommand(sockfd, "PASV\r\n");
}

int sendRetr(int sockfd, const char *urlPath) {
    char buf[64];
    snprintf(buf, sizeof(buf), "RETR %s\r\n", urlPath);
    return sendCommand(sockfd, buf);
}

int read_response(FILE *fl) {
    char *buf = NULL;
    size_t len = 0;
    ssize_t nread;
    int code = 0;
    int multiline = 0;

    while ((nread = getline(&buf, &len, fl)) != -1) {
        printf("%s", buf);

        if (isdigit(buf[0]) && isdigit(buf[1]) && isdigit(buf[2])) {
            if (buf[3] == '-') {
                multiline = 1;
                code = atoi(buf);
            } 
            else if (buf[3] == ' ') {
                break; 
            }
        } 
        else if (multiline) {
            if (atoi(buf) == code && buf[3] == ' ') {
                break;
            }
        }
    }

    free(buf);

    return 0;
}


int read_response_pasv(FILE * fl, char ip[32], int * port){
    char * buf = NULL;
    size_t bytes = 0;
    bytes = getline(&buf, &bytes, fl);
    buf[bytes] = '\0';
    printf(">%s",buf); 
    if (bytes < 0){
        return 1;
    }
    return parse_pasv_response(buf, ip, port);
}


int read_response_retr(FILE * fl, const char * filename){
    
    FILE* download_file = fopen(filename, "w");
    if (download_file == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    char buf[1028]; 
    size_t bytes;

    while (!feof(fl)) {
        bytes = fread(buf, 1, sizeof(buf), fl);
        if (bytes < 0) {
            perror("Error reading from file");
            fclose(download_file);
            return 1;
        }

        size_t written = fwrite(buf, 1, bytes, download_file);
        if (written < 0) {
            perror("Error writing to file");
            fclose(download_file);
            return 1;
        }
    }

    fclose(download_file);
    return 0;
}
