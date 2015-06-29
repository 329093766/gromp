#ifndef __CONFIG_H
#define __CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sds.h"

typedef struct {
    int position;
    char *input;
} gromp_config;

gromp_config *read_gromp_config(char *config_path);

void destroy_gromp_config(gromp_config *gromp);

#endif // __CONFIG_H