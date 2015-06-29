#include <stdio.h>

#include "gromp.h"

int main() {
    gromp_server *gromp = create_gromp_server();
    start_gromp_server(gromp);
    destroy_gromp_server(gromp);
}