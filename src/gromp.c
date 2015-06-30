#include "gromp.h"

const char *REQUESTS[] = {
    "REQUEST_INVALID",
    "REQUEST_GET",
    "REQUEST_HEAD",
    "REQUEST_POST",
    "REQUEST_BAD"
};

gromp_server *create_gromp_server() {
    gromp_server *gromp = malloc(sizeof(*gromp));
    gromp->port = 4444;
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
        gromp_error(gromp, "error: gromp server already running\n");
        return;
    }
    printf("gromp: starting gromp...\n");
    gromp->running = true;
    create_socket(gromp);
    bind_socket(gromp);
    start_listening(gromp);
}

int get_req_type(char *request) {
    char *request_header = request; // todo process
    for (int i = 0; i < ARR_SIZE(REQUESTS); i++) {
        if (!strcmp(request_header, REQUESTS[i])) {
            return i;
        }
    }
    return REQUEST_INVALID;
}

void handle_get_req(gromp_server *gromp, char *buffer) {
    printf("buffer (%d:%d): %s\n", gromp->current_socket, gromp->port, buffer);
}

int gromp_receive(gromp_server *gromp) {
    int packet_length = 0;
    char *buffer = sdsempty();

    if ((packet_length = recv(gromp->current_socket, buffer, 0, false)) == -1) {
        gromp_error(gromp, "error: failed handling request\n");
        return REQUEST_INVALID;
    }

    int request = get_req_type(buffer);
    switch (request) {
        case REQUEST_GET: handle_get_req(gromp, buffer); break;
        case REQUEST_HEAD: break;
        case REQUEST_POST: break;
        default: break; // bad
    }

    sdsfree(buffer);
    return REQUEST_INVALID;
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
        return;
    }
}

void handle_connection(gromp_server *gromp) {
    if (gromp_receive(gromp) < 0) {
        gromp_error(gromp, "error: failed to receive connection");
        return;
    }
}

void accept_connections(gromp_server *gromp) {
    gromp->addr_size = sizeof(gromp->connector);
    gromp->connecting_socket = accept(gromp->current_socket, (struct sockaddr*) &gromp->connector, &gromp->addr_size);

    if (gromp->connecting_socket < 0) {
        gromp_error(gromp, "error: failed to accept socket");
        return;
    }   

    handle_connection(gromp);
    close(gromp->connecting_socket);
}

void start_listening(gromp_server *gromp) {
    if (listen(gromp->current_socket, MAX_CONNECTIONS) < 0) {
        gromp_error(gromp, "gromp: could not listen on port\n");
        return;
    }

    while (gromp->running) {
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
    printf("gromp: server stopped ^_^\n");
    free(gromp);
}