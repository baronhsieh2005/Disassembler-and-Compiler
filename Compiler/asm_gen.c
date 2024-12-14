#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "token.h"
#include "Deque.h"
#include "rat_num.h"
#include "asm_gen.h"

int while_count = 0;
int if_count = 0;
Deque *while_stack;
Deque *if_stack;


bool create_if_while_stack() {
    while_stack = Deque_Allocate();
    if_stack = Deque_Allocate();
    if (while_stack == NULL || if_stack == NULL) {
        return false;
    }
    return true;
}

void free_if_while_stack() {
    Deque_Free(while_stack);
    Deque_Free(if_stack);
}

void pop_stack(FILE *output, const char *reg) {
    fprintf(output, "lw %s, 0(sp)\n", reg);
    fprintf(output, "addi sp, sp, 4\n");
}

void push_stack(FILE *output, const char *reg) {
    fprintf(output, "addi sp, sp, -4\n");
    fprintf(output, "sw %s, 0(sp)\n", reg);
}


void generate_asm_artihmetic(FILE *output, const char *operator_type) {
    pop_stack(output, "t0");
    pop_stack(output, "t1");

    fprintf(output, "%s t0, t0, t1\n", operator_type);

    push_stack(output, "t0");
}

void generate_asm_logic(FILE *output, const char* operator_type) {
    if (strcmp(operator_type, "not") == 0) {
        pop_stack(output, "t0");
        fprintf(output, "not t1, t0\n");
        push_stack(output, "t1");
    } else {
        pop_stack(output, "t0");
        pop_stack(output, "t1");

        fprintf(output, "%s t0, t0, t1\n", operator_type);

        push_stack(output, "t0");
    }
}

bool generate_asm(FILE *j_file, FILE *output, token targetToken) {
    switch (targetToken.type) {
        case PLUS: {
            generate_asm_artihmetic(output, "add");
            break;
        }
        case MINUS: {
            generate_asm_artihmetic(output, "sub");
            break;
        }
         case MUL: {
            generate_asm_artihmetic(output, "mul");
            break;
         }
        
        case DIV: {
            generate_asm_artihmetic(output, "div");
            break;
        }
        case MOD: {
            generate_asm_artihmetic(output, "rem");
            break;
        }
        case AND: {
            generate_asm_logic(output, "and");
            break;
        }
        case OR: {
            generate_asm_logic(output, "or");
            break;
        }
        case NOT: {
            generate_asm_logic(output, "not");
            break;
        }
        case LT: {
            pop_stack(output, "t0");
            pop_stack(output, "t1");
            fprintf(output, "slt t0, t0, t1\n");
            push_stack(output, "t0");
            break;
        } 
        case LE: {
            pop_stack(output, "t0");
            pop_stack(output, "t1");
            fprintf(output, "slt t0, t1, t0\n");
            fprintf(output, "xori t0, t0, 1\n");
            push_stack(output, "t0");
            break;
        }
        case EQ: {
            pop_stack(output, "t0");
            pop_stack(output, "t1");
            fprintf(output, "sub t2, t0, t1\n");
            fprintf(output, "sltiu t2, t2, 1\n");
            push_stack(output, "t2");
            break;
        }
        case GE: {
            pop_stack(output, "t0");
            pop_stack(output, "t1");
            fprintf(output, "slt t0, t0, t1\n");
            fprintf(output, "xori t0, t0, 1\n");
            push_stack(output, "t0");
            break;
        } 
        case GT: {
            pop_stack(output, "t0");
            pop_stack(output, "t1");
            fprintf(output, "slt t0, t1, t0\n");
            push_stack(output, "t0");
            break;
        }
        case DROP: {
            pop_stack(output, "t0");
            break;
        }
        case DUP: {
            fprintf(output, "lw t0, 0(sp)\n");
            push_stack(output, "t0");
            break;
        }
        case SWAP: {
            pop_stack(output, "t0");
            pop_stack(output, "t1");
            push_stack(output, "t0");
            push_stack(output, "t1");
            break;
        }
        case ROT: {
            pop_stack(output, "t0");
            pop_stack(output, "t1");
            pop_stack(output, "t2");
            push_stack(output, "t1");
            push_stack(output, "t0");
            push_stack(output, "t2");
            break;
        }
        case GET_ARG: {
            int arg_reg_num = targetToken.arg_no - 1;
            fprintf(output, "addi sp, sp, -4\n");
            fprintf(output, "sw a%d, 0(sp)\n", arg_reg_num);
            break;
        } 
        case SET_ARG: {
            int arg_reg_num = targetToken.arg_no - 1;
            pop_stack(output, "t0");  
            fprintf(output, "mv a%d, t0\n", arg_reg_num);
            break;
        }
        case LITERAL: {
            fprintf(output, "li t0, %d\n", targetToken.literal_value);
            push_stack(output, "t0");
            break;
        }
        case BAD_TOKEN: {
            return false;
            break;
        }
        case DEFUN: {
            bool next_token_check = next_token(j_file, &targetToken);
            if (!next_token_check || targetToken.type != IDENT) {
                fprintf(stderr, "Invalid Syntax: IDENT should follow DEFUN\n");
                return false;
            }
            fprintf(output, ".text\n");
            fprintf(output, ".p2align 2\n");
            fprintf(output, ".globl %s\n", targetToken.str);
            fprintf(output, "%s:\n", targetToken.str);
            fprintf(output, "addi sp, sp, -8\n");
            fprintf(output, "sw ra, 4(sp)\n");
            fprintf(output, "sw fp, 0(sp)\n");
            fprintf(output, "mv fp, sp\n");
            while (true) {
                bool next_token_check = next_token(j_file, &targetToken);
                if (!next_token_check || targetToken.type == BAD_TOKEN) {
                    fprintf(stderr, "BAD TOKEN deteced.\n");
                    return false;
                } 
                if (!generate_asm(j_file, output, targetToken)) {
                    return false;
                }
                if (targetToken.type == RETURN) {
                    break;
                }
            }
            break;
        }
        case IDENT: {
            fprintf(output, "call %s\n", targetToken.str);
            push_stack(output, "a0");
            break;
        }
        case RETURN: {
            pop_stack(output, "a0");
            fprintf(output, "mv sp, fp\n");
            fprintf(output, "lw fp, 0(sp)\n");
            fprintf(output, "lw ra, 4(sp)\n");
            fprintf(output, "addi sp, sp, 8\n");
            fprintf(output, "ret\n");
            break;
        }
        case IF: {
            if_count++;
            pop_stack(output, "t0");
            fprintf(output, "beq t0, x0, ELSE%d\n", if_count);
            rat_num if_payload = (rat_num) {
                .numerator = if_count,
                .denominator = 1
            };
            Deque_Push_Back(if_stack, if_payload);

            while (true) {
                bool next_token_check = next_token(j_file, &targetToken);
                if (!next_token_check || targetToken.type == BAD_TOKEN) {
                    fprintf(stderr, "BAD TOKEN deteced.\n");
                    return false;
                }
                if (targetToken.type == ENDIF || targetToken.type == ELSE) {
                    rat_num curr_if_payload;
                    if (!Deque_Peek_Back(if_stack, &curr_if_payload)) {
                        fprintf(stderr, "Stack is empty");
                        return false;
                    }
                    fprintf(output, "j END_IF%d\n", curr_if_payload.numerator);
                    fprintf(output, "ELSE%d:\n", curr_if_payload.numerator);
                    if (!generate_asm(j_file, output, targetToken)) {
                        return false;
                    }
                    break;
                }
                if (!generate_asm(j_file, output, targetToken)) {
                    return false;
                }
            }
            break;
        }
        case ELSE: {
            while (true) {
                bool next_token_check = next_token(j_file, &targetToken);
                if (!next_token_check || targetToken.type == BAD_TOKEN) {
                    fprintf(stderr, "BAD TOKEN deteced.\n");
                    return false;
                }
                if (targetToken.type == ENDIF) {
                    if (!generate_asm(j_file, output, targetToken)) {
                        return false;
                    }
                    break;
                }
                if (!generate_asm(j_file, output, targetToken)) {
                    return false;
                }
            }
            break;
        }
        case ENDIF: {
            rat_num if_payload;
            if (!Deque_Pop_Back(if_stack, &if_payload)) {
                fprintf(stderr, "Syntax error: ENDIF without matching IF.\n");
                return false;
            }
            fprintf(output, "END_IF%d:\n", if_payload.numerator);
            break;
        }
        case WHILE: {
            while_count++;
            fprintf(output, "WHILE%d:\n", while_count);
            pop_stack(output, "t0");
            fprintf(output, "beq t0, x0, ENDWHILE%d\n", while_count);
            rat_num while_payload = (rat_num) {
                .numerator = while_count,
                .denominator = 1
            };
            Deque_Push_Back(while_stack, while_payload);

            while (true) {
                bool next_token_check = next_token(j_file, &targetToken);
                if (!next_token_check || targetToken.type == BAD_TOKEN) {
                    fprintf(stderr, "BAD TOKEN deteced.\n");
                    return false;
                }
                if (targetToken.type == ENDWHILE) {
                    if (!generate_asm(j_file, output, targetToken)) {
                        return false;
                    }
                    break;
                }
                if (!generate_asm(j_file, output, targetToken)) {
                    return false;
                }
            }
            break;
        }
        case ENDWHILE: {
            rat_num while_payload;
            if (!Deque_Pop_Back(while_stack, &while_payload)) {
                fprintf(stderr, "Syntax error: ENDWHILE without matching WHILE.\n");
                return false;
            }
            fprintf(output, "j WHILE%d\n", while_payload.numerator);
            fprintf(output, "ENDWHILE%d:\n", while_payload.numerator);
            break;
        }
    }
    return true;
}
