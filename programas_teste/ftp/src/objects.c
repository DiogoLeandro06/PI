#include <stdio.h>
#include "objects.h"

void init_data(Data_ * info){
    info->user[0] = '\0';
    info->pw[0] = '\0';
    info->host[0] = '\0';
    info->host_ip[0] = '\0';
    info->url_path[0] = '\0';
    info->filename[0] = '\0';
}

void print_data(const Data_ info){
    printf("\nuser = '%s'\npw = '%s'\nhost = '%s'\nhost_ip = '%s'\nurl_path = '%s'\nfilename = '%s'\n",info.user,info.pw,info.host,info.host_ip,info.url_path,info.filename);
}


