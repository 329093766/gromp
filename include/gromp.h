#ifndef __GROMP_H
#define __GROMP_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    bool running;
    int current_socket;
    struct sockaddr_in address;
    struct sockaddr_storage connector;
    int connecting_socket;
    socklen_t addr_size;
} gromp_server;

gromp_server *create_gromp_server();

void start_gromp_server(gromp_server *gromp);

void create_socket(gromp_server *gromp);

void stop_gromp_server(gromp_server *gromp);

void destroy_gromp_server(gromp_server *gromp);

#endif // __GROMP_H