#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "./decoder.h"
#include "./loader.h"

uint8_t data_memory[65536] = {0};
uint32_t program_memory[16384] = {0};

const char* instr_type_to_string(INSTR_TYPE type) {
    switch (type) {
        case LUI:    return "LUI";
        case AUIPC:  return "AUIPC";
        case ADDI:   return "ADDI";
        case SLTI:   return "SLTI";
        case SLTIU:  return "SLTIU";
        case XORI:   return "XORI";
        case ORI:    return "ORI";
        case ANDI:   return "ANDI";
        case SLLI:   return "SLLI";
        case SRLI:   return "SRLI";
        case SRAI:   return "SRAI";

        case ADD:    return "ADD";
        case SUB:    return "SUB";
        case SLL:    return "SLL";
        case SLT:    return "SLT";
        case SLTU:   return "SLTU";
        case XOR:    return "XOR";
        case SRL:    return "SRL";
        case SRA:    return "SRA";
        case OR:     return "OR";
        case AND:    return "AND";

        case LB:     return "LB";
        case LH:     return "LH";
        case LW:     return "LW";
        case LBU:    return "LBU";
        case LHU:    return "LHU";

        case SB:     return "SB";
        case SH:     return "SH";
        case SW:     return "SW";

        case JAL:    return "JAL";
        case JALR:   return "JALR";

        case BEQ:    return "BEQ";
        case BNE:    return "BNE";
        case BLT:    return "BLT";
        case BGE:    return "BGE";
        case BLTU:   return "BLTU";
        case BGEU:   return "BGEU";

        case MUL:    return "MUL";
        case MULH:   return "MULH";
        case MULHSU: return "MULHSU";
        case MULHU:  return "MULHU";
        case DIV:    return "DIV";
        case DIVU:   return "DIVU";
        case REM:    return "REM";
        case REMU:   return "REMU";

        default:     return "INVALID";
    }
}

void print_instr(uint32_t parsed_instr, riscv_instr instr, uint32_t addr, FILE *output_file) {
    const char* instr_str = instr_type_to_string(instr.type);

    fprintf(output_file, "%08x : %08x -> ", addr, parsed_instr);
    switch (instr.type) {
        case ADD: case SUB: case SLL: case SLT: case SLTU:
        case XOR: case SRL: case SRA: case OR: case AND:
        case MUL: case MULH: case MULHSU: case MULHU:
        case DIV: case DIVU: case REM: case REMU:
            fprintf(output_file, "%s x%d, x%d, x%d\n",
                    instr_str, instr.rd, instr.rs1, instr.rs2);
            break;

        case ADDI: case SLTI: case SLTIU: case XORI: case ORI:
        case ANDI: case SLLI: case SRLI: case SRAI:
            fprintf(output_file, "%s x%d, x%d, %d\n",
                    instr_str, instr.rd, instr.rs1, instr.immediate);
            break;

        
        case BEQ: case BNE: case BLT: case BGE: case BLTU: case BGEU:
            fprintf(output_file, "%s x%d, x%d, %d\n",
                    instr_str, instr.rs1, instr.rs2, instr.immediate);
            break;

        case LB: case LH: case LW: case LBU: case LHU:
        case JALR:
            fprintf(output_file, "%s x%d, %d(x%d)\n", instr_str, instr.rd, instr.immediate, instr.rs1);
            break;

        case SB: case SH: case SW:
            fprintf(output_file, "%s x%d, %d(x%d)\n",
                    instr_str, instr.rs2, instr.immediate, instr.rs1);
            break;
        
        case LUI: case AUIPC:
            fprintf(output_file, "%s x%d, %d\n", instr_str, instr.rd, instr.immediate);
            break;

        case JAL:
            fprintf(output_file, "%s x%d, %d\n", instr_str, instr.rd, instr.immediate);
            break;

        default:
            fprintf(output_file, "INVALID INSTRUCTION\n");
            break;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Please provide more an output name and at least one file for the program.\n");
        return EXIT_FAILURE;
    }

    char *output_name = argv[1];
    FILE *output_file = fopen(output_name, "w");
    if (output_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    memset(data_memory, 0, 65536);
    memset(program_memory, 0, 16384 * sizeof(uint32_t));

    for (int i = 2; i < argc; i++) {
        int load_result = load_file(data_memory, program_memory, argv[i]);
        if (load_result) {
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < 16384; i++) {
        uint32_t program_val = program_memory[i];
        if (program_val != 0) {
            riscv_instr decoded_instr = decode_instr(program_val);
            uint32_t addr = 0x10000000 + 4 * i;
            print_instr(program_val, decoded_instr, addr, output_file);
        }
    }

    for (int i = 0; i < 65536; i++) {
        uint8_t data_val = data_memory[i];
        if (data_val != 0) {
            uint32_t addr = 0x20000000 + i;
            fprintf(output_file, "%08x : %02x\n", addr, data_val);
        }
    }


    fclose(output_file);
    return EXIT_SUCCESS;
}