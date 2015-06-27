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

    if (bind(gromp->current_socket, (struct sockaddr*) &address, sizeof(address)) < 0) {
        fprintf(stderr, "error: failed to bind port %d\n", port);
        stop_gromp_server(gromp);
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