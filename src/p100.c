#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>

#define BASE_DIRECTORY "/var/www/html/"

int is_valid_path(const char *filename) {
    char real_path[PATH_MAX];
    char base_path[PATH_MAX];

    if (realpath(filename, real_path) == NULL) {
        perror("Error resolving file path");
        return 0;
    }

    if (realpath(BASE_DIRECTORY, base_path) == NULL) {
        perror("Error resolving base directory path");
        return 0;
    }

    if (strncmp(real_path, base_path, strlen(base_path)) != 0) {
        printf("Invalid path detected!\n");
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char full_path[PATH_MAX];
    snprintf(full_path, sizeof(full_path), "%s%s", BASE_DIRECTORY, argv[1]);
    printf("%s\n", full_path);

    if (!is_valid_path(full_path)) {
        return 1;
    }

    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);

    return 0;
}
