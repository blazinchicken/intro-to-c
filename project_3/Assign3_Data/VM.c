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
int ic = 0;
int ir;
int32_t opcode;
int32_t operand;
int memory[MEM_MAX] = {0};
char input[13];
char reg[2];
char operString[5];
char operData[5];
int isHalt = 0;
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
        isHalt = 1;
        opcode = 99;
    } else {
        printf("Unknown Command - Unrecognized command word, they are case sensitive\n");
        exit(1);
    }
}

void compile(char *input){
   /* setStruct();*/
    int16_t addr;
    char operandOne[3];
    char operandTwo[3]; 
    int32_t thingToMemCpy;
    int i;
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
    if((int)(strlen(reg)) != 2){
        printf("Undefined Use - Command is not in the Proper Format");
        exit(2);
    }                   
    strcpy(operString, strtok(NULL, " "));
    if(!(((int)strlen(operString) == 4 )||((int)strlen(operString) == 3 ))){
        printf("Undefined Use - Command is not in the Proper Format");
        exit(2);
    }
    /*printf("%s\n",operString);*/ 
    strcpy(operData, strtok(NULL, " \n"));
    
    
    addr = (int32_t)atoi(reg);
    convert(operString);
    
    if(atoi(operData) >= 10000){
        printf("Word Overflow - Attempts to Place a Word in Memory that is Larger than 4 digits");
        exit(1);
    }

    if(opcode == 22){
        memcpy(operandOne, operData,2);
        operandOne[2] = '\0';
        memcpy(operandTwo, &operData[2],2);
        operandTwo[2] = '\0';
        if((int)strlen(operData) > 4){
            printf("Undefined Use - Command is not in the Proper Format1");
            exit(2);
        } 
        thingToMemCpy = (((int32_t)atoi(operandOne)) << 16) | ((int32_t)atoi(operandTwo));
        memcpy(&memory[addr], &thingToMemCpy, 4);

    } else {
        /*printf("%d%02d\n", opcode,operand);*/
        if((int)strlen(operData) > 2){
            printf("Undefined Use - Command is not in the Proper Format%s%d", operData,(int)strlen(operData));
            exit(2);
        } 
        operand = (int32_t)atoi(operData);
        thingToMemCpy = (opcode << 16) | operand;
        memcpy(&memory[addr], &thingToMemCpy, 4);
        
    }
    
   
}

void printAll(){
    int i;

    printf("\n");
    printf("REGISTERS: \n");
    printf("Accumulator:            %+05d\n", acc);
    printf("Instruction Counter:    %+02d\n", ic);
    printf("Instruction Register:   ");
    printWord(ir);
    printf("\n");
    printf("OperationCode:          %02d\n", opcode);
    printf("Operand:                %02d\n", operand);
    printf("\n");
    printf("MEMORY:\n");
    printf("     0      1      2      3      4      5      6      7      8      9\n");
    printf("0   ");
        for(i=0;i<10;i++){
            printf("+");
            printWord(memory[i]);
            printf("  ");
        }
    printf("\n10  ");
        for(i=10;i<20;i++){
            printf("+");
            printWord(memory[i]);
            printf("  ");
        }
    printf("\n20  ");
        for(i=20;i<30;i++){
            printf("+");
            printWord(memory[i]);
            printf("  ");
        }
    printf("\n30  ");
        for(i=30;i<40;i++){
            printf("+");
            printWord(memory[i]);
            printf("  ");
        }
    printf("\n40  ");
        for(i=40;i<50;i++){
            printf("+");
            printWord(memory[i]);
            printf("  ");
        }
    printf("\n50  ");
        for(i=50;i<60;i++){
            printf("+");
            printWord(memory[i]);
            printf("  ");
        }
    printf("\n60  ");
        for(i=60;i<70;i++){
            printf("+");
            printWord(memory[i]);
            printf("  ");
        }
    printf("\n70  ");
        for(i=70;i<80;i++){
            printf("+");
            printWord(memory[i]);
            printf("  ");
        }
    printf("\n80  ");
        for(i=80;i<90;i++){
            printf("+");
            printWord(memory[i]);
            printf("  ");
        }
    printf("\n90  ");
        for(i=90;i<100;i++){
            printf("+");
            printWord(memory[i]);
            printf("  ");
        }

}
void execute(){
    int k = 1;
    int i;
    int32_t op1;
    int32_t op2;
    int scanBuff;

    while(k == 1){
        ir = memory[ic];
        opcode = (ir >> 16) & 0xFFFF;
        operand = ir & 0xFFFF; 
        if(operand >= 100){
            printf("Segmentation Fault - Tries to Access Unknown Address");
            exit(1);
        }
        switch (opcode){
            case 10: /*READ*/
                /*scanf("%d", &scanBuff);
                if(scanBuff >= 10000){
                    printf("Word Overflow - Attempts to place a Word in Memory larger than 4 digits");
                    break;
                } else {
                    memory[operand] = scanBuff;
                }
                ic++;
                break;*/
            case 11: /*WRIT*/
                printWord(memory[operand]);
                ic++;
                break;
            case 12: /*PRNT*/
                for(i=operand; ; i++){ 
                    op1 = (memory[i] >> 16) & 0xFFFF;
                    op2 = memory[i] & 0xFFFF;
                    if(op1 == '\0'){
                        break;
                    } else {
                        printf("%c",op1);
                    }
                    if(op2 == '\0'){
                        break;
                    } else {
                    printf("%c",op2);
                    }
                } 
                ic++;            
                break;
            case 20: /*LOAD*/
                acc = memory[operand];
                ic++;
                break;
            case 21: /*STOR*/
                memory[operand] = acc;
                ic++;
                break;
            case 30: /*ADD*/
                acc = acc + memory[operand];
                ic++;
                break;
            case 31: /*SUB*/
                acc = acc - memory[operand];
                ic++;
                break;
            case 32: /*DIV*/
                if(memory[operand] == 0){
                    printf("Divide 0 - Division by 0 was attempted");
                    exit(1);
                    break;
                }
                acc = acc / memory[operand];
                ic++;
                break;
            case 33: /*MULT*/
                acc = acc * memory[operand];
                ic++;
                break;
            case 34: /*MOD*/
                if(memory[operand] == 0){
                    printf("Divide 0 - Division by 0 was attempted");
                    exit(1);
                    break;
                }
                acc = acc % memory[operand];
                ic++;
                break;
            case 40: /*BRAN*/
                ic = operand;
                break;
            case 41: /*BRNG*/
                if(acc < 0){
                    ic = operand;
                } else {
                    ic++;
                }
                break;      
            case 42: /*BRZR*/
                if(acc == 0){
                    ic = operand;
                } else {
                    ic++;
                }
                break;
            case 99: /*HALT*/
                printAll();
                goto endOfForever;
                ic++;
                break;
            default:
            printf("Unknown command - Unrecognized command code");
            exit(1);

        }
        if(acc >= 10000){
            printf("Word Overflow - Attempts to Place a Word in Accumulator so that it is Larger than 4 digits");
            exit(1);
        }
    }       
    endOfForever:
    return;
}


int main(void) {
    while(fgets(input, 13, stdin)) {
		/* printf("%s\n", input); */
        compile(input);
    }
    if(isHalt == 0){
        printf("No HALT - No Halt Command is Ever Given");
        exit(3);
    }
    /* stdin = fopen("/dev/tty", "r"); */
    execute();
    return 0;
}



/* %04d  for setting SET*/
/* TODO

1. Make Read Work
2.RT Error: WORD OVERFLOW - mostly done
            Segmentation Fault - should be done
            UnknownCharacter - if statement? - lots of ||*/