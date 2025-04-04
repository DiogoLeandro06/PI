#ifndef __COMANDS_H__
#define __COMANDS_H__

#include <stdio.h>

int sendCommand(int sockfd, const char *command);

int sendUser(int sockfd, const char *username);

int sendPass(int sockfd, const char *password);

int sendPasv(int sockfd);

int sendRetr(int sockfd, const char *url_path);

int read_response(FILE * fl);

int read_response_pasv(FILE * fl, char ip[32], int * port);

int read_response_retr(FILE * fl, const char * filename);

#endif