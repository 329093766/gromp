#ifndef __GROMP_H
#define __GROMP_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/wait.h>

#define MAX_CONNECTIONS 16

typedef struct {
    bool running;
    int port;
    int current_socket;
    struct sockaddr_in address;
    struct sockaddr_storage connector;
    int connecting_socket;
    socklen_t addr_size;
} gromp_server;

gromp_server *create_gromp_server();

void start_gromp_server(gromp_server *gromp);

void create_socket(gromp_server *gromp);

void bind_socket(gromp_server *gromp);

void accept_connections(gromp_server *gromp);

void gromp_start_listening(gromp_server *gromp);

void stop_gromp_server(gromp_server *gromp);

void destroy_gromp_server(gromp_server *gromp);

#endif // __GROMP_H