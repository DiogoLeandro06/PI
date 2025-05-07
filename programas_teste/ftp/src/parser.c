#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "parser.h"


int parse_data(Data_ * info, const char * arg){
    int control = 1;
    size_t len = strlen(arg);
    if (len > 6) {
        char tmp[64] = {0};
        strncpy(tmp, arg, 6);
        if ((strcmp(tmp, "ftp://")) != 0) {
            fprintf(stderr, "Received prefix %s", tmp);
            return 1;
        }
        strcpy(tmp, "\0");
        int j = 0;
        for (int i = 6; i < len; i++) {
            if (arg[i] == '/') {
                if (control != 4) {
                    tmp[j] = '\0';
                    strcpy(info->host, tmp);
                    j = 0;
                    strcpy(tmp, "\0");
                    control++;
                }
                else {
                    tmp[j] = arg[i];
                    j++;
                }
            } 
            else if (arg[i] == ':') {
                tmp[j] = '\0';
                strcpy(info->user, tmp);
                j = 0;
                strcpy(tmp, "\0");
                control++;
            } 
            else if (arg[i] == '@') {
                tmp[j] = '\0';
                strcpy(info->pw, tmp);
                j = 0;
                strcpy(tmp, "\0");
                control++;
            } 
            else {
                tmp[j] = arg[i];
                j++;
            }
        }
        tmp[j] = '\0';
        strcpy(info->url_path, tmp);
        j = 0;
        strcpy(tmp, "\0");

        char *lastSlash = strrchr(info->url_path, '/');
        if (lastSlash != NULL) {
            strcpy(info->filename, lastSlash + 1);
        } 
        else {
            strcpy(info->filename, info->url_path);
        }

        return 0;
    }
    return 1;
}


int get_host_ip(Data_ * info){
    
    struct hostent *h;

    if ((h = gethostbyname(info->host)) == NULL) {
        herror("gethostbyname()");
        return 1;
    }

    strcpy(info->host_ip ,inet_ntoa(*((struct in_addr *) h->h_addr)));

    return 0;
}



int parse_pasv_response(const char buf[64], char ip[32], int * port){
    
    int a, b, c, d, e, f;

    if (sscanf(buf, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)",
               &a, &b, &c, &d, &e, &f) == 6) {

        snprintf(ip, 32, "%d.%d.%d.%d", a, b, c, d);

        *port = (e * 256) + f;

        return 0;
    }

    return 1;
}
