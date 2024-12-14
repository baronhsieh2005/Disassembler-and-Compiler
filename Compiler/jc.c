#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "token.h"
#include "asm_gen.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Please only provide one J file.\n");
        fprintf(stderr, "Usage: %s source.j\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (create_if_while_stack() == false) {
        return EXIT_FAILURE;
    }


    char *input_filename = argv[1];
    FILE *input = fopen(input_filename, "r");
    if (input == NULL) {
        fprintf(stderr, "Error opening input file\n");
        return EXIT_FAILURE;
    }

    int len = strlen(input_filename);
    char output_filename[len + 1];
    strncpy(output_filename, input_filename, len - 1);
    output_filename[len - 1] = 's';
    output_filename[len] = '\0';

    FILE *output = fopen(output_filename, "w");
    if (output == NULL) {
        fprintf(stderr, "Error opening output file\n");
        fclose(input);
        return EXIT_FAILURE;
    } 

    token targetToken;
    while (true) {
        if (!next_token(input, &targetToken)) {
            if (feof(input)) {
                break;
            } else {
                fprintf(stderr, "Error reading token\n");
                return EXIT_FAILURE;
            }
        }

        if (!generate_asm(input, output, targetToken)) {
            return EXIT_FAILURE;
        }
    }

    free_if_while_stack();
    fclose(output);
    fclose(input);
    return EXIT_SUCCESS;
}