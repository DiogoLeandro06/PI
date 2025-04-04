#ifndef __OBJECTS_H__
#define __OBJECTS_H__

typedef struct Data_ {
    char user[64];
    char pw[64];
    char host[64];
    char url_path[64];
    char host_ip[64];
    char filename[64];
} Data_;

void init_data(Data_ * info);

void print_data(const Data_ info);

#endif