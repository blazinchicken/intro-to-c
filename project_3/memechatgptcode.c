#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 100

typedef struct {
    int acc; // Accumulator register
    int ic; // Instruction counter
    char ir[5]; // Instruction register (4 digits + null terminator)
    int opcode; // Current instruction's opcode
    int operand; // Current instruction's operand
    int memory[MEMORY_SIZE]; // VM's memory
} VM;

void initialize(VM *vm) {
    vm->acc = 0;
    vm->ic = 0;
    memset(vm->ir, 0, 5);
    vm->opcode = 0;
    vm->operand = 0;
    memset(vm->memory, 0, MEMORY_SIZE);
}

void load_program(VM *vm, int *program, int program_size) {
    memcpy(vm->memory, program, program_size * sizeof(int));
}

void fetch(VM *vm) {
    sprintf(vm->ir, "%04d", vm->memory[vm->ic]);
    vm->ic++;
}

void decode(VM *vm) {
    char opcode_str[3] = {vm->ir[0], vm->ir[1], '\0'};
    char operand_str[3] = {vm->ir[2], vm->ir[3], '\0'};
    vm->opcode = atoi(opcode_str);
    vm->operand = atoi(operand_str);
}

void execute(VM *vm) {
    switch (vm->opcode) {
        case 10: // READ
            printf("Enter a value: ");
            scanf("%d", &vm->memory[vm->operand]);
            break;
        case 11: // WRIT
            printf("%d\n", vm->memory[vm->operand]);
            break;
        case 12: // PRNT
            while (vm->memory[vm->operand] != 0) {
                printf("%c", vm->memory[vm->operand]);
                vm->operand++;
            }
            printf("\n");
            break;
        case 20: // LOAD
            vm->acc = vm->memory[vm->operand];
            break;
        case 21: // STOR
            sprintf(vm->ir, "%04d", vm->acc);
            memcpy(&vm->memory[vm->operand], vm->ir, 4);
            break;
        case 30: // ADD
            vm->acc += vm->memory[vm->operand];
            break;
        case 31: // SUB
            vm->acc -= vm->memory[vm->operand];
            break;
        case 32: // DIV
            vm->acc /= vm->memory[vm->operand];
            break;
        case 33: // MULT
            vm->acc *= vm->memory[vm->operand];
            break;
        case 34: // MOD
            vm->acc %= vm->memory[vm->operand];
            break;
        case 40: // BRAN
            vm->ic = vm->operand;
            break;
        case 41: // BRNG
            if (vm->acc < 0) {
                vm->ic = vm->operand;
            }
            break;
        case 42: // BRZR
            if (vm->acc == 0) {
                vm->ic = vm->operand;
            }
            break;
        case 99: // HALT
            printf("Memory state:\n");
            printf("Addr   Value\n");
            printf("------------\n");
            for (int i = 0; i < MEMORY_SIZE; i++) {

            };
