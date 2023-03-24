#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/*Steps to Success
    1. Create Processor
        -Memory = 100 addresses
        -Accumulator - int - Register that operations are preformed upon, data buffer
        -InstructionCounter - stores address of currect instruction to be executed
        -InstructionRegister - stores the current instruction fetched from VM memory
        -OperationCode and Operand - storing decoded components of current instructions
    2. Create two functions
        Compile() - accept written commands as a file
        Execute() - execute what is in memory
    3. Print out Array of ASCII numbers for the different memory addresses
    4. Specific Error Handling
        Compile Errors
        Runtime Errors
        
    5. run commands from a file and get specific results */
#define MEM_MAX 100

/*typedef struct {
    int acc;    accumulator
    int ic;     instruction counter
    char ir[5]; 
    int opcode; 
    int operand;
    int memory[MEM_MAX];
} VM;
*/
int acc;
int ic;
char ir[5];
int32_t opcode;
int32_t operand;
int memory[MEM_MAX] = {0};
char input[13];
char reg[2];
char operString[5];
char operData[5];
/*void setStruct(VM *vm){
    vm->acc = 0;
    vm->ic = 0;
    memset(vm->ir, 0 ,5);
    vm->opcode = 0;
    vm->operand = 0;
    memset(vm->memory, 0, MEM_MAX);
}*/
void printWord(int32_t word){
    int16_t firstHalf;
    int16_t secondHalf;

    firstHalf = (word >> 16) & 0xFFFF;
    secondHalf = word & 0xFFFF;

    printf("%02d%02d",firstHalf,secondHalf);
    
}


void convert(char *operString){
    if (strcmp(operString, "READ") == 0){
        opcode = 10; 
    } else if(strcmp(operString,"WRIT") == 0){
        opcode = 11;
    }else if(strcmp(operString,"PRNT") == 0){
        opcode = 12;
    }else if(strcmp(operString,"LOAD") == 0){
        opcode = 20;
    }else if(strcmp(operString,"STOR") == 0){
        opcode = 21;
    }else if(strcmp(operString,"SET") == 0){
        opcode = 22;
    }else if(strcmp(operString,"ADD") == 0){
        opcode = 30;
    }else if(strcmp(operString,"SUB") == 0){
        opcode = 31;
    }else if(strcmp(operString,"DIV") == 0){
        opcode = 32;
    }else if(strcmp(operString,"MULT") == 0){
        opcode = 33;
    }else if(strcmp(operString,"MOD") == 0){
        opcode = 34;
    }else if(strcmp(operString,"BRAN") == 0){
        opcode = 40;
    }else if(strcmp(operString,"BRNG") == 0){
        opcode = 41;
    }else if(strcmp(operString,"BRZR") == 0){
        opcode = 42;
    }else if(strcmp(operString,"HALT") == 0){
        opcode = 99;
    } else {
        printf("Unrecognized command word, they are case sensitive\n");
    }
}

void compile(char *input){
   /* setStruct();*/
    int16_t addr;
   /* for(i=0;i<2;i++){
        reg[i] = input[i];
        printf("%c",reg[i]);
    }
    for(i=3;i<7;i++){
        operString[i-3] = input[i];
        printf("%c",operString[i-3]);
    }
    for(i=7;i<13;i++){
        operData[i-7] = input[i];
        printf("%c",operData[i-7]);
    }*/
    strcpy(reg, strtok(input, " "));
    strcpy(operString, strtok(NULL, " "));
    /*printf("%s\n",operString);*/ 
    strcpy(operData, strtok(NULL, " "));
    operand = (int32_t)atoi(operData);
    addr = (int32_t)atoi(reg);
    convert(operString);
    if(opcode == 22){
        memcpy(&memory[addr],&operand,4); /* buggg - split into 2 - 2bytes*/

    } else {
        /*printf("%d%02d\n", opcode,operand);*/
        int32_t thingToMemCpy = (opcode << 16) | operand;
        memcpy(&memory[addr], &thingToMemCpy, 4);
        
    }
    
   
}


void execute(){

}
int main(void) {
    int i;
    while(fgets(input, 13, stdin)) {
		/* printf("%s\n", input); */
        compile(input);
    }
    for(i=0;i<100;i++){
        printWord(memory[i]);
        printf(" ");
        if (((i % 10) == 0 ) && (i != 0)) {
            printf("\n");
        }
    }
    return 0;
}



/* %04d  for setting SET*/