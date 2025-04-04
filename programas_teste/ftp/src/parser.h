#ifndef __PARSER_H__
#define __PARSER_H__

#include "objects.h"

int parse_data(Data_ * info, const char * arg);

int get_host_ip(Data_ * info);

int parse_pasv_response(const char buf[64], char ip[32], int * port);


#endif