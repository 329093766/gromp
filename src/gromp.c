#include "gromp.h"

gromp_server *create_gromp_server() {
    gromp_server *gromp = malloc(sizeof(*gromp));

    return gromp;   
}

void start_gromp_server(gromp_server *gromp) {
    if (gromp->running) {
        fprintf(stderr, "error: gromp server already running\n");
        return;
    }
    fprintf(stdout, "starting gromp...\n");
    create_socket(gromp);
    gromp->running = true;
}

void create_socket(gromp_server *gromp) {
    gromp->current_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (gromp->current_socket == -1) {
        fprintf(stderr, "error: could not create socket\n");
        stop_gromp_server(gromp);
        return;
    }
}

void bind_socket(gromp_server *gromp) {
    gromp->address.sin_family = AF_INET;
    gromp->address.sin_addr.s_addr = INADDR_ANY;
    gromp->address.sin_port = htons(gromp->port);

    if (bind(gromp->current_socket, (struct sockaddr*) &gromp->address, sizeof(gromp->address)) < 0) {
        fprintf(stderr, "error: failed to bind port %d\n", gromp->port);
        stop_gromp_server(gromp);
    }
}

void accept_connections(gromp_server *gromp) {
    gromp->addr_size = sizeof(gromp->connector);
    gromp->connecting_socket = accept(gromp->current_socket, (struct sockaddr*) &gromp->connector, &gromp->addr_size);

    if (gromp->connecting_socket < 0) {
        fprintf(stderr, "error: failed to accept socket");
        stop_gromp_server(gromp);
    }   

    // handle
    // close
}

void gromp_start_listening(gromp_server *gromp) {
    if (listen(gromp->current_socket, MAX_CONNECTIONS) < 0) {
        fprintf(stderr, "could not listen on port\n");
        stop_gromp_server(gromp);
    }

    while (true) {
        accept_connections(gromp);
    }
}

void stop_gromp_server(gromp_server *gromp) {
    if (!gromp->running) {
        fprintf(stderr, "error: no gromp server to stop\n");
        return;
    }
    gromp->running = false;
}

void destroy_gromp_server(gromp_server *gromp) {
    if (gromp->running) {
        stop_gromp_server(gromp);
    }
    free(gromp);
}