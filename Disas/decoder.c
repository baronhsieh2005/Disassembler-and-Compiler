#include "./decoder.h"
#include <stdio.h> // for printf




void decode_s_instr(riscv_instr *result, uint32_t funct3) {
    switch (funct3) {
        case 0x0:
            result->type = SB;
            result->PCMuxCTL = 3;
            result->regFileWE = 0;
            result->regInputMuxCTL = ANY_SIGNAL;
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 1;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 36;
            break;
        case 0x1:
            result->type = SH;
            result->PCMuxCTL = 3;
            result->regFileWE = 0;
            result->regInputMuxCTL = ANY_SIGNAL;
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 3;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 36;
            break;
        case 0x2:
            result->type = SW;
            result->PCMuxCTL = 3;
            result->regFileWE = 0;
            result->regInputMuxCTL = ANY_SIGNAL;
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 15;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 36;
            break;
        default:
            result->type = ILLEGAL_INSTR;
            return;
    }
}

void decode_r_instr(riscv_instr *result, uint32_t funct3, uint32_t funct7) {
    switch (funct3) {
        case 0x0:
            switch (funct7) {
                case 0x00:
                    result->type = ADD;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 9; 
                    break;
                case 0x20:
                    result->type = SUB;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 10; 
                    break;
                case 0x01:
                    result->type = MUL;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 25; 
                    break;
                default:
                    result->type = ILLEGAL_INSTR;
                    return;
            }
            break;
        case 0x1:
            switch (funct7) {
                case 0x00:
                    result->type = SLL;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 11; 
                    break;
                case 0x01:
                    result->type = MULH;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 26; 
                    break;
                default:
                    result->type = ILLEGAL_INSTR;
                    return;
            }
            break;
        case 0x2:
            switch (funct7) {
                case 0x00:
                    result->type = SLT;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 12; 
                    break;
                case 0x01:
                    result->type = MULHSU;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 27; 
                    break;
                default:
                    result->type = ILLEGAL_INSTR;
                    return;
            }
            break;
        case 0x3:
            switch (funct7) {
                case 0x00:
                    result->type = SLTU;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 13; 
                    break;
                case 0x01:
                    result->type = MULHU;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 28; 
                    break;
                default:
                    result->type = ILLEGAL_INSTR;
                    return;
            }
            break;
        case 0x4:
            switch (funct7) {
                case 0x00:
                    result->type = XOR;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 14; 
                    break;
                case 0x01:
                    result->type = DIV;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 29; 
                    break;
                default:
                    result->type = ILLEGAL_INSTR;
                    return;
            }
            break;
        case 0x5:
            switch (funct7) {
                case 0x00:
                    result->type = SRL;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 15; 
                    break;
                case 0x20:
                    result->type = SRA;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 16; 
                    break;
                case 0x01:
                    result->type = DIVU;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 30; 
                    break;
                default:
                    result->type = ILLEGAL_INSTR;
                    return;
            }
            break;
        case 0x6:
            switch (funct7) {
                case 0x00:
                    result->type = OR;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 17; 
                    break;
                case 0x01:
                    result->type = REM;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 31; 
                    break;
                default:
                    result->type = ILLEGAL_INSTR;
                    return;
            }
            break;
        case 0x7:
            switch (funct7) {
                case 0x00:
                    result->type = AND;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 18; 
                    break;
                case 0x01:
                    result->type = REMU;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 0;
                    result->ALUCTL = 32; 
                    break;
                default:
                    result->type = ILLEGAL_INSTR;
                    return;
            }
            break;
        default:
            result->type = ILLEGAL_INSTR;
            return;
    }
}


void decode_i_instr_03(riscv_instr *result, uint32_t funct3) {
    switch (funct3) {
        case 0x0:  
            result->type = LB;
            result->PCMuxCTL = 3;
            result->regFileWE = 1;
            result->regInputMuxCTL = 3; 
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 0;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 0; 
            break;
        case 0x1:  
            result->type = LH;
            result->PCMuxCTL = 3;
            result->regFileWE = 1;
            result->regInputMuxCTL = 2; 
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 0;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 0; 
            break;
        case 0x2:  
            result->type = LW;
            result->PCMuxCTL = 3;
            result->regFileWE = 1;
            result->regInputMuxCTL = 1; 
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 0;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 0; 
            break;
        case 0x4:  
            result->type = LBU;
            result->PCMuxCTL = 3;
            result->regFileWE = 1;
            result->regInputMuxCTL = 3; 
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 0;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 0; 
            break;
        case 0x5: 
            result->type = LHU;
            result->PCMuxCTL = 3;
            result->regFileWE = 1;
            result->regInputMuxCTL = 2; 
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 0;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 0; 
            break;
        default:
            result->type = ILLEGAL_INSTR;
            return;
    }
} 


void decode_i_instr_13(riscv_instr *result, uint32_t funct3, uint32_t funct7, uint32_t instr_bits) {
    uint32_t parsed_imm = (instr_bits >> 20) & 0xFFF;
    int32_t signed_imm;
    if (parsed_imm & 0x800) {
        signed_imm = (parsed_imm | 0xFFFFF000);
    } else {
        signed_imm = parsed_imm;
    }
    uint32_t unsigned_imm = (uint32_t) signed_imm;
    int shift_imm = parsed_imm & 0x1F;
    switch (funct3) {
        case 0x0: 
            result->type = ADDI;
            result->PCMuxCTL = 3;
            result->regFileWE = 1;
            result->regInputMuxCTL = 0;
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 0;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 0;
            break;
        case 0x2: 
            result->type = SLTI;
            result->PCMuxCTL = 3;
            result->regFileWE = 1;
            result->regInputMuxCTL = 0;
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 0;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 1;
            break;
        case 0x3:  
            result->type = SLTIU;
            result->PCMuxCTL = 3;
            result->regFileWE = 1;
            result->regInputMuxCTL = 0;
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 0;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 2;
            result->immediate = unsigned_imm;
            break;
        case 0x4:  
            result->type = XORI;
            result->PCMuxCTL = 3;
            result->regFileWE = 1;
            result->regInputMuxCTL = 0;
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 0;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 3;
            break;
        case 0x6:  
            result->type = ORI;
            result->PCMuxCTL = 3;
            result->regFileWE = 1;
            result->regInputMuxCTL = 0;
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 0;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 4;
            break;
        case 0x7: 
            result->type = ANDI;
            result->PCMuxCTL = 3;
            result->regFileWE = 1;
            result->regInputMuxCTL = 0;
            result->PCAddMuxCTL = ANY_SIGNAL;
            result->DATAWE = 0;
            result->ALUInputMuxCTL = 1;
            result->ALUCTL = 5;
            break;
        case 0x1:  
            if (funct7 == 0x00) {
                result->type = SLLI;
                result->PCMuxCTL = 3;
                result->regFileWE = 1;
                result->regInputMuxCTL = 0;
                result->PCAddMuxCTL = ANY_SIGNAL;
                result->DATAWE = 0;
                result->ALUInputMuxCTL = 1;
                result->ALUCTL = 6;
                result->immediate = shift_imm;
            } else {
                result->type = ILLEGAL_INSTR;
                return;
            }
            break;
        case 0x5: 
            switch (funct7) {
                case 0x00:
                    result->type = SRLI;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 1;
                    result->ALUCTL = 7;
                    result->immediate = shift_imm;
                    break;
                case 0x20:
                    result->type = SRAI;
                    result->PCMuxCTL = 3;
                    result->regFileWE = 1;
                    result->regInputMuxCTL = 0;
                    result->PCAddMuxCTL = ANY_SIGNAL;
                    result->DATAWE = 0;
                    result->ALUInputMuxCTL = 1;
                    result->ALUCTL = 8;
                    result->immediate = shift_imm;
                    break;
                default:
                    result->type = ILLEGAL_INSTR;
                    return;
            }
            break;
        default:
            result->type = ILLEGAL_INSTR;
            return;
    }
}

void decode_b_instr(riscv_instr *result, uint32_t funct3) {
  switch (funct3) {
      case 0x0:
          result->type = BEQ;
          result->PCMuxCTL = 1;
          result->regFileWE = 0;
          result->regInputMuxCTL = ANY_SIGNAL;
          result->PCAddMuxCTL = ANY_SIGNAL;
          result->DATAWE = 0;
          result->ALUInputMuxCTL = 0;
          result->ALUCTL = 19;
          break;
      case 0x1:
          result->type = BNE;
          result->PCMuxCTL = 1;
          result->regFileWE = 0;
          result->regInputMuxCTL = ANY_SIGNAL;
          result->PCAddMuxCTL = ANY_SIGNAL;
          result->DATAWE = 0;
          result->ALUInputMuxCTL = 0;
          result->ALUCTL = 20;
          break;
      case 0x4:
          result->type = BLT;
          result->PCMuxCTL = 1;
          result->regFileWE = 0;
          result->regInputMuxCTL = ANY_SIGNAL;
          result->PCAddMuxCTL = ANY_SIGNAL;
          result->DATAWE = 0;
          result->ALUInputMuxCTL = 0;
          result->ALUCTL = 21;
          break;
      case 0x5:
          result->type = BGE;
          result->PCMuxCTL = 1;
          result->regFileWE = 0;
          result->regInputMuxCTL = ANY_SIGNAL;
          result->PCAddMuxCTL = ANY_SIGNAL;
          result->DATAWE = 0;
          result->ALUInputMuxCTL = 0;
          result->ALUCTL = 22;
          break;
      case 0x6:
          result->type = BLTU;
          result->PCMuxCTL = 1;
          result->regFileWE = 0;
          result->regInputMuxCTL = ANY_SIGNAL;
          result->PCAddMuxCTL = ANY_SIGNAL;
          result->DATAWE = 0;
          result->ALUInputMuxCTL = 0;
          result->ALUCTL = 23;
          break;
      case 0x7:
          result->type = BGEU;
          result->PCMuxCTL = 1;
          result->regFileWE = 0;
          result->regInputMuxCTL = ANY_SIGNAL;
          result->PCAddMuxCTL = ANY_SIGNAL;
          result->DATAWE = 0;
          result->ALUInputMuxCTL = 0;
          result->ALUCTL = 24;
          break;
      default:
          result->type = ILLEGAL_INSTR;
          return;
  }
}

void parse_s_imm(riscv_instr *result, uint32_t instr_bits) {
    uint32_t imm_4_to_0 = (instr_bits >> 7) & 0x1F;   
    uint32_t imm_11_to_5 = (instr_bits >> 25) & 0x7F;   
    uint32_t parsed_imm = (imm_11_to_5 << 5) | imm_4_to_0;
    int32_t signed_imm;
    if (parsed_imm & 0x800) {
        signed_imm = (parsed_imm | 0xFFFFF000);
    } else {
        signed_imm = parsed_imm;
    }
    result->immediate = signed_imm;
}

void parse_i_imm(riscv_instr *result, uint32_t instr_bits) {
    uint32_t parsed_imm = (instr_bits >> 20) & 0xFFF;
    int32_t signed_imm;
    if (parsed_imm & 0x800) {
        signed_imm = (parsed_imm | 0xFFFFF000);
    } else {
        signed_imm = parsed_imm;
    }
    result->immediate = signed_imm;
}


void parse_b_imm(riscv_instr *result, uint32_t instr_bits) {
    uint32_t imm_11 = ((instr_bits >> 7) & 0x1) << 11;
    uint32_t imm_4_to_1 = ((instr_bits >> 8) & 0x0F) << 1;
    uint32_t imm_10_to_5 = ((instr_bits >> 25) & 0x3F) << 5;
    uint32_t imm_12 = ((instr_bits >> 31) & 0x1) << 12;
    uint32_t parsed_imm = imm_12 | imm_11 | imm_10_to_5 | imm_4_to_1;
    int32_t signed_imm;
    if (parsed_imm & 0x1000) {
        signed_imm = (parsed_imm | 0xFFFFE000);
    } else {
        signed_imm = parsed_imm;
    }
    result->immediate = signed_imm;
}

void parse_u_imm(riscv_instr *result, uint32_t instr_bits) {
    uint32_t parsed_imm = (instr_bits >> 12) & 0xFFFFF;
    int32_t signed_imm;
    if (parsed_imm & 0x80000) {
        signed_imm = (parsed_imm | 0xFFF00000);
    } else {
        signed_imm = parsed_imm;
    }
    result->immediate = signed_imm;
}

void parse_j_imm(riscv_instr *result, uint32_t instr_bits) {
    uint32_t imm_20     = ((instr_bits >> 31) & 0x1) << 20;
    uint32_t imm_19_12  = ((instr_bits >> 12) & 0xFF) << 12;
    uint32_t imm_11     = ((instr_bits >> 20) & 0x1) << 11;
    uint32_t imm_10_to_1= ((instr_bits >> 21) & 0x3FF) << 1;

    uint32_t parsed_imm = imm_20 | imm_19_12 | imm_11 | imm_10_to_1;
    int32_t signed_imm;

    if (parsed_imm & 0x100000) { 
        signed_imm = (int32_t)(parsed_imm | 0xFFE00000);
    } else {
        signed_imm = (int32_t)parsed_imm;
    }

    result->immediate = signed_imm;
}

riscv_instr decode_instr(uint32_t instr_bits) {
  // TODO: implement me
  // for hw08 you don't need to parse out the registers or the integer immediate
  // you just need to set the type and the control signals->
  riscv_instr result = {0};  // 0's out the struct to start

  uint32_t opcode = instr_bits & 0x7F;
  uint32_t funct3 = (instr_bits >> 12) & 0x07;
  uint32_t funct7 = (instr_bits >> 25) & 0x7F;

  uint32_t rd = (instr_bits >> 7) & 0x1F;
  uint32_t rs1 = (instr_bits >> 15) & 0x1F;
  uint32_t rs2 = (instr_bits >> 20) & 0x1F;

  switch (opcode) {
      case 0x23:
         result.rs1 = rs1;
         result.rs2 = rs2;
         parse_s_imm(&result, instr_bits);
         decode_s_instr(&result, funct3);
         break;
      case 0x33: 
          result.rd = rd;
          result.rs1 = rs1;
          result.rs2 = rs2;
          decode_r_instr(&result, funct3, funct7);
          break;
      case 0x63:
          result.rs1 = rs1;
          result.rs2 = rs2;
          parse_b_imm(&result, instr_bits);
          decode_b_instr(&result, funct3);
          break;
      case 0x13:
          result.rd = rd;
          result.rs1 = rs1;
          parse_i_imm(&result, instr_bits);
          decode_i_instr_13(&result, funct3, funct7, instr_bits);
          break;
      case 0x03:
          result.rd = rd;
          result.rs1 = rs1;
          parse_i_imm(&result, instr_bits);
          decode_i_instr_03(&result, funct3);
          break;
      case 0x37:  
          result.type = LUI;
          result.PCMuxCTL = 3;
          result.regFileWE = 1;
          result.regInputMuxCTL = 0;
          result.PCAddMuxCTL = ANY_SIGNAL;
          result.DATAWE = 0;
          result.ALUInputMuxCTL = 1;
          result.ALUCTL = 33; 
          result.rd = rd;
          parse_u_imm(&result, instr_bits);
          break;
      case 0x17: 
          result.type  = AUIPC;
          result.PCMuxCTL = 3;
          result.regFileWE = 1;
          result.regInputMuxCTL = 4;
          result.PCAddMuxCTL = 1;
          result.DATAWE = 0;
          result.ALUInputMuxCTL = ANY_SIGNAL;
          result.ALUCTL = ANY_SIGNAL;     
          result.rd = rd;      
          parse_u_imm(&result, instr_bits);
          break;
      case 0x6f:
          result.type = JAL;
          result.PCMuxCTL = 2;
          result.regFileWE = 1;
          result.regInputMuxCTL = 4;
          result.PCAddMuxCTL = 0;
          result.DATAWE = 0;
          result.ALUInputMuxCTL = ANY_SIGNAL;
          result.ALUCTL = ANY_SIGNAL;
          result.rd = rd;
          parse_j_imm(&result, instr_bits);
          break;
      case 0x67:
          result.type = JALR;
          result.PCMuxCTL = 0;
          result.regFileWE = 1;
          result.regInputMuxCTL = 4;
          result.PCAddMuxCTL = 0;
          result.DATAWE = 0;
          result.ALUInputMuxCTL = 1;
          result.ALUCTL = 34;
          result.rd = rd;
          result.rs1 = rs1;
          parse_i_imm(&result, instr_bits);
          break;
      default:
          result.type = ILLEGAL_INSTR;
          break;
  }

  // You will need to parse the immediate and registerss for hw09 though->
  return result;
}


// Implementation of helper funtcion that may be useful for debugging
// You should not modify this function, nor do you need to understand how it works
// If you do want to know how this works, we left some comments->->
//
// Given an INSTR_TYPE, prints out the corresponding string for that type->
// This is provided for debugging purposes, you should not modify the method
void print_type(INSTR_TYPE type) {
  // declares an array of C-strings containing the string of every
  // riscv instruction type-> This array exists in global memory
  // and is generated exactly once->
  static const char* type_strings[] = {
    "ILLEGAL_INSTR",
    "LUI", "AUIPC",
    "ADDI", "SLTI", "SLTIU", "XORI", "ORI", "ANDI", "SLLI", "SRLI", "SRAI",
    "ADD", "SUB", "SLL", "SLT", "SLTU", "XOR", "SRL", "SRA",  "OR", "AND",
    "LB", "LH", "LW", "LBU", "LHU",
    "SB", "SH", "SW",
    "JAL", "JALR",
    "BEQ", "BNE", "BLT", "BGE", "BLTU", "BGEU",
    "MUL", "MULH", "MULHSU", "MULHU",
    "DIV", "DIVU", "REM", "REMU",
  };

  // Note that an ENUM variable instance is internally implemented as a
  // integer variable-> The value of that integer corresponds with the order in which
  // the possible enum values are declared-> So ILLEGAL_INSTR is represented as the integer 0
  // and the enum value LUI is implemented as the integer 1->
  printf("%s", type_strings[type]);
}



