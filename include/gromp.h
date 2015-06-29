#ifndef __GROMP_H
#define __GROMP_H

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/wait.h>

#include "sds.h"

#define MAX_CONNECTIONS 16
#define ARR_SIZE(x) ((int) (sizeof(x) / sizeof(x[0])))

typedef enum {
    REQUEST_INVALID, // invalid request, something fucked up
    REQUEST_GET,
    REQUEST_HEAD, // ayy lmao
    REQUEST_POST,
    REQUEST_BAD, // 400, no idea
} RequestType;

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

void start_listening(gromp_server *gromp);

void stop_gromp_server(gromp_server *gromp);

void destroy_gromp_server(gromp_server *gromp);

#endif // __GROMP_H