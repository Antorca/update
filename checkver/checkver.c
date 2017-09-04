#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

char *latest_version = "5.0.0";
int latest_build_int = 2017090420;
char *latest_build_char = "2017090420";
bool update_available = false;

bool main(int *argc, char *argv[]) {
    if (access("/etc/antorca/antorca-build", F_OK) == -1) {
        fprintf(stderr, "Antorca build file is missing!\n");
        update_available = false;
        return update_available;
    } else {
        FILE *build_file = fopen("/etc/antorca/antorca-build", "r");
        if (build_file == NULL) {
            fprintf(stderr, "Can't access build file!\n");
            update_available = false;
            return update_available;
        }
        char check_build_buffer[64];
        int check_build;
        int i = 0;
	char cbuffer;
	while (1) {
            cbuffer = fgetc(build_file);
            if (feof(build_file)) {
                check_build_buffer[i] = '\0';
                break;
            }
            check_build_buffer[i] = cbuffer;
            i++;
        }
	// printf("Found: %s\n", check_build_buffer);
        if (strlen(check_build_buffer) == 0) {
            fprintf(stderr, "Build file is empty!\n");
            update_available = false;
            return update_available;
        } else {
            check_build = atoi(check_build_buffer);
            // printf("%s --> %d\n", check_build_buffer, check_build);
            if (latest_build_int == check_build) {
                // printf("Up to date!\n");
                // printf("This build: %d\nLatest build: %d\n", check_build, latest_build_int);
                update_available = true;
                return update_available;
            } else if (latest_build_int > check_build) {
                // printf("There's a new version available!\n");
                // printf("This build: %d\nLatest build: %d\n", check_build, latest_build_int);
                update_available = false;
                return update_available;
            }
        }
    }
}