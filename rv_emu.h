// RISC-V emulator types and constants

#include <stdint.h>
#include <stdbool.h>

// ABI register mappings
#define RV_ZERO      0
#define RV_RA        1
#define RV_SP        2
#define RV_A0       10
#define RV_A1       11
#define RV_A2       12
#define RV_A3       13
#define RV_NUM_REGS 32

// Opcodes for instr formats
typedef enum {
    FMT_R       = 0b0110011,
    FMT_I_LOAD  = 0b0000011,
    FMT_I_JALR  = 0b1100111,
    FMT_I_ARITH = 0b0010011,
    FMT_S       = 0b0100011,
    FMT_SB      = 0b1100011,
    FMT_UJ      = 0b1101111
} rv_format;

// Width values for FMT_I_LOAD and FMT_S
#define LDST_BYTE   0
#define LDST_WORD   2
#define LDST_DOUBLE 3

#define STACK_SIZE 8192

// Sentinel value for stopping the emulator
#define RV_STOP 0

// Dynamic analysis structs

typedef struct {
    int i_count;
    int ir_count;
    int ld_count;
    int st_count;
    int j_count;
    int b_taken;
    int b_not_taken;
} rv_analysis;


typedef struct {
    uint64_t regs[RV_NUM_REGS];
    uint64_t pc;

    uint8_t stack[STACK_SIZE];

    bool analyze;
    bool verbose;

    rv_analysis  analysis;
} rv_state;

void rv_init(rv_state *state, uint32_t *target, 
             uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t rv_emulate(rv_state *state);
void rv_print(rv_analysis *analysis);
