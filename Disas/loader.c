#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


#include <arpa/inet.h> 

#include "loader.h"

uint16_t read_byte(FILE *target_file, bool *read_success) {
    uint8_t byte_val;
    if (fread(&byte_val, sizeof(uint8_t), 1, target_file) != 1) {
        *read_success = false;
        return 0;
    }
    *read_success = true;
    return byte_val;
}

uint32_t read_word(FILE *target_file, bool *read_success) {
    uint32_t word_val;
    if (fread(&word_val, sizeof(uint32_t), 1, target_file) != 1) {
       *read_success = false;
        return 0;
    }
    *read_success = true;
    return ntohl(word_val);
}


int load_file(uint8_t* data_memory, uint32_t *program_memory, const char* file) {
    FILE *target_file = fopen(file, "rb");
    if (target_file == NULL) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    bool read_success;
    uint32_t magic = read_word(target_file, &read_success);

     if (!read_success) {
        if (ferror(target_file)) {
            perror("Error reading file");
            fclose(target_file);
            return EXIT_FAILURE;
        }
        fclose(target_file);
        return EXIT_SUCCESS;
    } 

    if (magic != 0xCAFEF00D) {
        fprintf(stderr, "Error: Invalid magic word in file %s\n", file);
        fclose(target_file);
        return EXIT_FAILURE;
    }

    while (true) {
        uint16_t section_type;
        size_t bytes_read = fread(&section_type, sizeof(uint16_t), 1, target_file);
        if (bytes_read != 1) {
            if (ferror(target_file)) {
                perror("Error reading file");
                fclose(target_file);
                return EXIT_FAILURE;
            }
            fclose(target_file);
            return EXIT_SUCCESS;
        }
        section_type = ntohs(section_type);

        switch (section_type) {
            case 0xC0DE: {
                bool read_address_success, read_n_success;
                uint32_t address = read_word(target_file, &read_address_success);
                uint32_t n = read_word(target_file, &read_n_success);

                if (!read_address_success || !read_n_success) {
                    if (ferror(target_file)) {
                        perror("Error reading file");
                        fclose(target_file);
                        return EXIT_FAILURE;
                    }
                    fclose(target_file);
                    return EXIT_SUCCESS;
                } 

                for (uint32_t i = 0; i < n; i++) {
                    bool read_success;
                    uint32_t curr_instr = read_word(target_file, &read_success);
                    if (!read_success) {
                        if (ferror(target_file)) {
                            perror("Error reading file");
                            fclose(target_file);
                            return EXIT_FAILURE;
                        }
                        fclose(target_file);
                        return EXIT_SUCCESS;
                    } 
                    uint32_t idx = (address - 0x10000000) / 4 + i;
                    program_memory[idx] = curr_instr;
                }
                break;
            }
            case 0xDADA: {
                bool read_address_success;
                bool read_n_success;
                uint32_t address = read_word(target_file, &read_address_success);
                uint32_t n = read_word(target_file, &read_n_success);


                if (!read_address_success || !read_n_success) {
                    if (ferror(target_file)) {
                        perror("Error reading file");
                        fclose(target_file);
                        return EXIT_FAILURE;
                    }
                    fclose(target_file);
                    return EXIT_SUCCESS;
                } 

                for (uint32_t i = 0; i < n; i++) {
                    bool read_success;
                    uint32_t curr_data = read_byte(target_file, &read_success);
                    if (!read_success) {
                        if (ferror(target_file)) {
                            perror("Error reading file");
                            fclose(target_file);
                            return EXIT_FAILURE;
                        }
                        fclose(target_file);
                        return EXIT_SUCCESS;
                    } 
                    uint32_t idx = (address - 0x20000000) + i;
                    data_memory[idx] = curr_data;
                }
                break;
            }

            case 0xC3B7: {
                bool read_address_success;
                bool read_n_success;
                uint32_t address = read_word(target_file, &read_address_success);
                uint32_t n = read_word(target_file, &read_n_success);

                if (!read_address_success || !read_n_success) {
                    if (ferror(target_file)) {
                        perror("Error reading file");
                        fclose(target_file);
                        return EXIT_FAILURE;
                    }
                    fclose(target_file);
                    return EXIT_SUCCESS;
                } 
                int seek_result = fseek(target_file, n, SEEK_CUR);
                if (seek_result != 0) {
                    if (ferror(target_file)) {
                        perror("Error reading file");
                        fclose(target_file);
                        return EXIT_FAILURE;
                    }
                    fclose(target_file);
                    return EXIT_SUCCESS;
                }

                break;
            
            }   
            case 0xF17E: {
                bool read_n_success;
                uint32_t n = read_word(target_file, &read_n_success);
                if (!read_n_success) {
                    if (ferror(target_file)) {
                        perror("Error reading file");
                        fclose(target_file);
                        return EXIT_FAILURE;
                    }
                    fclose(target_file);
                    return EXIT_SUCCESS;
                } 
                int seek_result = fseek(target_file, n, SEEK_CUR);
                if (seek_result != 0) {
                    if (ferror(target_file)) {
                        perror("Error reading file");
                        fclose(target_file);
                        return EXIT_FAILURE;
                    }
                    fclose(target_file);
                    return EXIT_SUCCESS;
                }
                break;
            }
            case 0x715E: {
                bool read_success;
                read_word(target_file, &read_success);
                if (!read_success) {
                    if (ferror(target_file)) {
                        perror("Error reading file");
                        fclose(target_file);
                        return EXIT_FAILURE;
                    }
                    fclose(target_file);
                    return EXIT_SUCCESS;
                } 
                read_word(target_file, &read_success); 
                if (!read_success) {
                    if (ferror(target_file)) {
                        perror("Error reading file");
                        fclose(target_file);
                        return EXIT_FAILURE;
                    }
                    fclose(target_file);
                    return EXIT_SUCCESS;
                } 
                read_word(target_file, &read_success); 
                if (!read_success) {
                    if (ferror(target_file)) {
                        perror("Error reading file");
                        fclose(target_file);
                        return EXIT_FAILURE;
                    }
                    fclose(target_file);
                    return EXIT_SUCCESS;
                } 
                break;
            }

            default: {
                fclose(target_file);
                return EXIT_FAILURE;
            }                
        }
        
    }

    fclose(target_file);
    return EXIT_SUCCESS;
}