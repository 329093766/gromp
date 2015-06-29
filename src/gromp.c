#include "gromp.h"

gromp_server *create_gromp_server() {
    gromp_server *gromp = malloc(sizeof(*gromp));
    gromp->port = 80;
    return gromp;   
}

int gromp_error(gromp_server *gromp, const char *fmt, ...) {
    va_list arguments;
    va_start(arguments, fmt);
    int result = vfprintf(stderr, fmt, arguments);
    va_end(arguments);

    stop_gromp_server(gromp);
    return result;
}

void start_gromp_server(gromp_server *gromp) {
    if (gromp->running) {
        fprintf(stderr, "error: gromp server already running\n");
        return;
    }
    printf("starting gromp...\n");
    create_socket(gromp);
    gromp->running = true;
}

int gromp_receive(gromp_server *gromp) {
    int packet_length = 0;
}

void create_socket(gromp_server *gromp) {
    gromp->current_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (gromp->current_socket == -1) {
        gromp_error(gromp, "error: could not create socket\n");
        return;
    }
}

void bind_socket(gromp_server *gromp) {
    gromp->address.sin_family = AF_INET;
    gromp->address.sin_addr.s_addr = INADDR_ANY;
    gromp->address.sin_port = htons(gromp->port);

    if (bind(gromp->current_socket, (struct sockaddr*) &gromp->address, sizeof(gromp->address)) < 0) {
        gromp_error(gromp, "error: failed to bind port %d\n", gromp->port);
    }
}

void handle_connection(gromp_server *gromp) {
    if (gromp_receive(gromp) < 0) {
        gromp_error(gromp, "failed to receive connection");
    }
}

void accept_connections(gromp_server *gromp) {
    gromp->addr_size = sizeof(gromp->connector);
    gromp->connecting_socket = accept(gromp->current_socket, (struct sockaddr*) &gromp->connector, &gromp->addr_size);

    if (gromp->connecting_socket < 0) {
        gromp_error(gromp, "error: failed to accept socket");
    }   

    // handle
    // close
}

void gromp_start_listening(gromp_server *gromp) {
    if (listen(gromp->current_socket, MAX_CONNECTIONS) < 0) {
        gromp_error(gromp, "could not listen on port\n");
    }

    while (true) {
        accept_connections(gromp);
    }
}

void stop_gromp_server(gromp_server *gromp) {
    if (!gromp->running) {
        gromp_error(gromp, "error: no gromp server to stop\n");
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