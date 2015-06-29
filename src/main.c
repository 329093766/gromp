#include <stdio.h>

#include "gromp.h"
#include "config.h"

int main() {
    gromp_config *config = read_gromp_config("configs/test.gc");

    gromp_server *gromp = create_gromp_server();
    start_gromp_server(gromp);

    destroy_gromp_server(gromp);
    destroy_gromp_config(config);
}