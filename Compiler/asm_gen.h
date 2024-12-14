#ifndef ASM_GEN_H
#define ASM_GEN_H

bool create_if_while_stack();
void free_if_while_stack();
bool generate_asm(FILE *j_file, FILE *output, token targetToken);

#endif