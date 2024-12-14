#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "./token.h"


int line_number;
const char* token_type_string(token_type t);
bool literal_token_decimal(int first_decimal, FILE *j_file, token *output, bool is_negative) {
    char str[MAX_TOKEN_LENGTH + 1];
    int idx = 0;

    if (is_negative) {
        str[idx++] = '-';
    } 
    
    str[idx++] = first_decimal;

    while (idx < MAX_TOKEN_LENGTH) {
        int c = fgetc(j_file);
        if (c == EOF) {
            if (ferror(j_file)) {
                perror("Error Reading File");
                return false;
            } 
            break;
        } else if (isspace(c)) {
            break;
        } else if (isdigit(c)) {
            str[idx++] = c;
        } else {
            output->type = BAD_TOKEN;
            return true;
        }
    }
    str[idx] = '\0';

    char *endptr;
    int base = 10;

    int32_t value = (int32_t)strtol(str, &endptr, base);

    output->type = LITERAL;
    output->literal_value = value;
    return true;
}

bool literal_token_hex(FILE *j_file, token *output) {
    char str[MAX_TOKEN_LENGTH + 1];
    int idx = 0;
    str[idx++] = '0';
    str[idx++] = 'x';

   
    while (idx < 10) {
        int c = fgetc(j_file);
        if (c == EOF || isspace(c)) {
            if (ferror(j_file)) {
                perror("Error Reading File");
                return false;
            } 

            if (idx > 2) {
                break;
            } else {
                output->type = BAD_TOKEN;
                return true;
            }   
        } else if (isxdigit(c)) {
            str[idx++] = c;
        } else {
            output->type = BAD_TOKEN;
            return true;
        }
    }
    str[idx] = '\0';

    if (idx == 10) {
        int space_eof_check = fgetc(j_file);
        if (isspace(space_eof_check) || space_eof_check == EOF) {
            if (ferror(j_file)) {
                perror("Error Reading File");
                return false;
            } 
            if (isspace(space_eof_check)) {
                ungetc(space_eof_check, j_file);
            }
        } else {
            output->type = BAD_TOKEN;
            return true;
        }
    }

    char *endptr;
    int base = 16;

    int32_t value = (int32_t)strtol(str, &endptr, base);

    output->type = LITERAL;
    output->literal_value = value;
    return true;
}




bool next_token(FILE *j_file, token *output) {
    int c;

    while(true) {
        c = fgetc(j_file);
        if (c == EOF) {
            return false;
        }

        if (c == '\n') {
            line_number++;
        }

        if (isspace(c)) {
            continue;
        }

        if (c == ';') {
            while (c != '\n' && c != EOF) {
                c = fgetc(j_file);
            }
            if (c == '\n') {
                line_number++;
            }
            continue;
        } else if (isalpha(c)) {
            char str[MAX_TOKEN_LENGTH + 1]; 
            int idx = 0;
            str[idx++] = c;

            while (idx < MAX_TOKEN_LENGTH) {
                c = fgetc(j_file);
                if (c == EOF) {
                    if (ferror(j_file)) {
                        perror("Error reading file");
                        return false;
                    }
                    break;
                }
                if (isspace(c)) {
                    break;
                }
                if (!(isalnum(c) || c == '_')) {
                    output->type = BAD_TOKEN;
                    return true;
                }
                str[idx++] = c;
            }
            str[idx] = '\0';

            if (strcmp(str, "defun") == 0) {
                output->type = DEFUN;
                return true;
            } else if (strcmp(str, "return") == 0) {
                output->type = RETURN;
                return true;
            } else if (strcmp(str, "if") == 0) {
                output->type = IF;
                return true;
            } else if (strcmp(str, "else") == 0) {
                output->type = ELSE;
                return true;
            } else if (strcmp(str, "endif") == 0) {
                output->type = ENDIF;
                return true;
            } else if (strcmp(str, "while") == 0) {
                output->type = WHILE;
                return true;
            } else if (strcmp(str, "endwhile") == 0) {
                output->type = ENDWHILE;
                return true;
            } else if (strcmp(str, "drop") == 0) {
                output->type = DROP;
                return true;
            } else if (strcmp(str, "dup") == 0) {
                output->type = DUP;
                return true;
            } else if (strcmp(str, "swap") == 0) {
                output->type = SWAP;
                return true;
            } else if (strcmp(str, "rot") == 0) {
                output->type = ROT;
                return true;
            } else if (strcmp(str, "and") == 0) {
                output->type = AND;
                return true;
            } else if (strcmp(str, "or") == 0) {
                output->type = OR;
                return true;
            } else if (strcmp(str, "not") == 0) {
                output->type = NOT;
                return true;
            } else if (strcmp(str, "lt") == 0) {
                output->type = LT;
                return true;
            } else if (strcmp(str, "le") == 0) {
                output->type = LE;
                return true;
            } else if (strcmp(str, "eq") == 0) {
                output->type = EQ;
                return true;
            } else if (strcmp(str, "ge") == 0) {
                output->type = GE;
                return true;
            } else if (strcmp(str, "gt") == 0) {
                output->type = GT;
                return true;
            } else if (strncmp(str, "get_arg", 7) == 0) {
                int arg_num = atoi(str + 7);
                if (arg_num >= 1 && arg_num <= 8) {
                    output->type = GET_ARG;
                    output->arg_no = arg_num;
                    return true;
                } else {
                    output->type = BAD_TOKEN;
                    return true;
                }
            } else if (strncmp(str, "set_arg", 7) == 0) {
                int arg_num = atoi(str + 7);
                if (arg_num >= 1 && arg_num <= 8) {
                    output->type = SET_ARG;
                    output->arg_no = arg_num;
                    return true;
                } else {
                    output->type = BAD_TOKEN;
                    return true;
                }
            } else {
                output->type = IDENT;
                strcpy(output->str, str);
                return true;
            }
        } else if (c == '+' || c == '*' || c == '/' || c == '%') {
            int space_check = fgetc(j_file);
            if (isspace(space_check) || space_check == EOF) {
                switch (c) {
                    case '+':
                        output->type = PLUS;
                        break;
                    case '*':
                        output->type = MUL;
                        break;
                    case '/':
                        output->type = DIV;
                        break;
                    case '%':
                        output->type = MOD;
                        break;
                }
                if (space_check != EOF) {
                    ungetc(space_check, j_file);
                }
                return true; 
            } else {
                output->type = BAD_TOKEN;
                ungetc(space_check, j_file);
                return true;
            }

        } else if (c == '-') {
            int next_c = fgetc(j_file);
            if (isspace(next_c) || next_c == EOF) {
                if (ferror(j_file)) {
                    perror("Error reading file");
                    return false;
                }
                if (isspace(next_c)) {
                    ungetc(next_c, j_file);
                }
                output->type = MINUS;
                return true;
            } else if (isdigit(next_c)) {
                return literal_token_decimal(next_c, j_file, output, true);
            } else {
                output-> type = BAD_TOKEN;
                return true;
            }

        } else if (isdigit(c)) {
            int next_c = fgetc(j_file);
            if (isspace(next_c) || next_c == EOF) {
                if (ferror(j_file)) {
                    perror("Error reading file");
                    return false;
                }
                output->type = LITERAL;
                output->literal_value = c - '0';
                if (isspace(next_c)) {
                    ungetc(next_c, j_file);
                }
                return true;
            } else if (next_c == 'x' && c == '0') {
                return literal_token_hex(j_file, output);
            } else if (isdigit(next_c)) {
                ungetc(next_c, j_file);
                return literal_token_decimal(c, j_file, output, false);
            } else {
                output-> type = BAD_TOKEN;
                return true;
            }

        } else {
            output->type = BAD_TOKEN;
            return true;
        }
    }
}

const char* token_type_string(token_type t) {
    switch (t) {
        case DEFUN:     
            return "DEFUN";
        case IDENT:     
            return "IDENT";
        case RETURN:    
            return "RETURN";
        case PLUS:      
            return "PLUS";
        case MINUS:     
            return "MINUS";
        case MUL:       
            return "MUL";
        case DIV:       
            return "DIV";
        case MOD:       
            return "MOD";
        case AND:       
            return "AND";
        case OR:        
            return "OR";
        case NOT:       
            return "NOT";
        case LT:        
            return "LT";
        case LE:        
            return "LE";
        case EQ:        
            return "EQ";
        case GE:        
            return "GE";
        case GT:        
            return "GT";
        case IF:        
            return "IF";
        case ELSE:      
            return "ELSE";
        case ENDIF:     
            return "ENDIF";
        case WHILE:     
            return "WHILE";
        case ENDWHILE:  
            return "ENDWHILE";
        case DROP:      
            return "DROP";
        case DUP:       
            return "DUP";
        case SWAP:      
            return "SWAP";
        case ROT:       
            return "ROT";
        case GET_ARG:   
            return "GET_ARG";
        case SET_ARG:   
            return "SET_ARG";
        case LITERAL:   
            return "LITERAL";
        case BAD_TOKEN: 
            return "BAD_TOKEN";
    }
}



void print_token (FILE* f, token to_print) {
    fprintf(f, "Token Type: %s\n", token_type_string(to_print.type));
        switch (to_print.type) {
        case IDENT: 
            fprintf(f, "Identifier: %s\n", to_print.str);
            break;
        case LITERAL:
            fprintf(f, "Literal Value: %d\n", to_print.literal_value);
            break;
        case GET_ARG:
        case SET_ARG:
            fprintf(f, "Number of Arguments: %d\n", to_print.arg_no);
            break;
        default:
            break;
    }
}

