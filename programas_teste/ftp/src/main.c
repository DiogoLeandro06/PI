#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "objects.h"
#include "parser.h"
#include "comands.h"

#define SERVER_PORT 21

int main(int argc, char **argv){
    
    if (argc != 2){
        fprintf(stderr,"Correct usage : ./projeto ftp://[<user>:<password>@]<host>/<url-path>\n");
        return EXIT_FAILURE;
    }
    
    Data_ info;

    init_data(&info);

    if ((parse_data(&info, argv[1])) != 0){
        fprintf(stderr,"The given url syntax is incorrect\n");
        return EXIT_FAILURE;
    }

    // PARSING DATA DONE

    if ((get_host_ip(&info)) != 0){
        return EXIT_FAILURE;
    }

    print_data(info);

    

    // GET HOST IP DONE

    int sockfd;
    struct sockaddr_in server_addr;

    //server address handling
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(info.host_ip);
    server_addr.sin_port = htons(SERVER_PORT);        

    //open a TCP socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        return EXIT_FAILURE;
    }

    //connect to the server
    if (connect(sockfd,
                (struct sockaddr *) &server_addr,
                sizeof(server_addr)) < 0) {
        perror("connect()");
        return EXIT_FAILURE;
    }

    printf("\nConnection open on hostname = '%s' and ip = '%s'\n",info.host,info.host_ip);

    FILE * fl = fdopen(sockfd,"r");

    if ((read_response(fl)) != 0){
        fprintf(stderr,"Error reading answer from server\n");
        return EXIT_FAILURE;
    }

    if ((sendUser(sockfd, info.user)) != 0){
        fprintf(stderr,"Error sending user\n");
        return EXIT_FAILURE;
    }

    printf("\nSent command : 'USER %s'\n",info.user);

    if ((read_response(fl)) != 0){
        fprintf(stderr,"Error reading answer from server\n");
        return EXIT_FAILURE;
    }
    
    if ((sendPass(sockfd, info.pw)) != 0){
        fprintf(stderr,"Error sending password\n");
        return EXIT_FAILURE;
    }

    printf("\nSent command : 'PASS %s'\n",info.pw);

    if ((read_response(fl)) != 0){
        fprintf(stderr,"Error reading answer from server\n");
        return EXIT_FAILURE;
    }

    if ((sendPasv(sockfd)) != 0){
        fprintf(stderr,"Error sending passive mode command\n");
        return EXIT_FAILURE;
    }

    printf("\nSent command : 'pasv'\n");

    char ip[32] = {0};
    int port = 21;
    if ((read_response_pasv(fl, ip, &port)) != 0){    
        fprintf(stderr,"Error read passive mode server answer\n");
        return EXIT_FAILURE;
    }


    int sockfd2;
    struct sockaddr_in data_server_addr;

    //server address handling
    bzero((char *) &data_server_addr, sizeof(data_server_addr));
    data_server_addr.sin_family = AF_INET;
    data_server_addr.sin_addr.s_addr = inet_addr(ip);
    data_server_addr.sin_port = htons(port);

    //open a TCP socket
    if ((sockfd2 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        return EXIT_FAILURE;
    }

    //connect to the server
    if (connect(sockfd2, (struct sockaddr *) &data_server_addr, sizeof(data_server_addr)) < 0) {
        perror("connect()");
        return EXIT_FAILURE;
    }

    printf("\nConnection open on hostname = '%s' and ip = '%s'\n",info.host,info.host_ip);

    FILE *fl2 = fdopen(sockfd2, "r");

    if ((sendRetr(sockfd, info.url_path)) != 0) {
        fprintf(stderr, "Error sending RETR command\n");
        return EXIT_FAILURE;
    }

    printf("\nSent command : 'RETR %s'\n", info.url_path);

    if ((read_response_retr(fl2, info.filename)) != 0) {
        fprintf(stderr, "Error reading RETR command response\n");
        return EXIT_FAILURE;
    }

    printf("\nDownloaded '%s' on host = '%s'\n", info.url_path, info.host);


    if ((fclose(fl2)) < 0) {
        perror("close()");
        return EXIT_FAILURE;
    }    

    if ((fclose(fl)) < 0) {
        perror("close()");
        return EXIT_FAILURE;
    }

    printf("\nClosed connection\n");
    


    return EXIT_SUCCESS;
}
    
