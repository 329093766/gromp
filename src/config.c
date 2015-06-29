#include "config.h"

gromp_config *read_gromp_config(char *config_path) {
    FILE *file = fopen(config_path, "r");
    char *contents = NULL;

    if (file) {
        if (!fseek(file, 0, SEEK_END)) {
            long file_size = ftell(file);
            if (file_size == -1) {
                perror("ftell: could not read filesize");
                return false;
            }

            contents = malloc(sizeof(*contents) * (file_size + 1));
            if (fseek(file, 0, SEEK_SET)) {
                perror("fseek: could not reset file index");
                return false;
            }

            size_t file_length = fread(contents, sizeof(char), file_size, file);
            if (!file_length) {
                printf("error: gromp configuration file `%s` is empty\n", config_path);
            }

            contents[file_length] = '\0';
        }
        fclose(file);
    } else {
        printf("fopen: could not read file `%s`", config_path);
        free(contents);
        return false;
    }

    // hopefully content isn't null here
    // the function should be returned from if
    // anything went wrong when reading the
    // configuration file.

    gromp_config *config = malloc(sizeof(*config));
    config->input = contents;
    printf("read the config file: \n %s\n", config->input);
    return config;
}

void destroy_gromp_config(gromp_config *gromp) {
    free(gromp->input);
    free(gromp);
}