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
typedef struct vm_{
    int acc;
    int ic;
    int ir;
    int32_t opcode;
    int32_t operand;
    int32_t memory[MEM_MAX];
} VM;
char input[13];
char reg[2];
char operString[5];
char operData[5];
int isHalt = 0;
void setStruct(VM *vm){
    vm->acc = 0;
    vm->ic = 0;
    vm->ir = 0;
    vm->opcode = 0;
    vm->operand = 0;
    memset(vm->memory, 0, MEM_MAX*sizeof(int32_t));
}
void printWord(int32_t word){
    if(word >= 0){
    printf("%+05d", word);
    } else {
    printf("+%+04d",word);
    }
    
}
void printWordTwo(int32_t word){
  
    printf("%04d", word);
    
}

void convert(char *operString, VM *vm){
    if (strcmp(operString, "READ") == 0){
        vm->opcode = 10; 
    } else if(strcmp(operString,"WRIT") == 0){
        vm->opcode = 11;
    }else if(strcmp(operString,"PRNT") == 0){
        vm->opcode = 12;
    }else if(strcmp(operString,"LOAD") == 0){
        vm->opcode = 20;
    }else if(strcmp(operString,"STOR") == 0){
        vm->opcode = 21;
    }else if(strcmp(operString,"SET") == 0){
        vm->opcode = 22;
    }else if(strcmp(operString,"ADD") == 0){
        vm->opcode = 30;
    }else if(strcmp(operString,"SUB") == 0){
        vm->opcode = 31;
    }else if(strcmp(operString,"DIV") == 0){
        vm->opcode = 32;
    }else if(strcmp(operString,"MULT") == 0){
        vm->opcode = 33;
    }else if(strcmp(operString,"MOD") == 0){
        vm->opcode = 34;
    }else if(strcmp(operString,"BRAN") == 0){
        vm->opcode = 40;
    }else if(strcmp(operString,"BRNG") == 0){
        vm->opcode = 41;
    }else if(strcmp(operString,"BRZR") == 0){
        vm->opcode = 42;
    }else if(strcmp(operString,"HALT") == 0){
        isHalt = 1;
        vm->opcode = 99;
    } else {
        printf("Unknown Command - Unrecognized command word, they are case sensitive\n");
        exit(1);
    }
}

void compile(char *input, VM *vm){

    int16_t addr;
    char operandOne[3];
    char operandTwo[3]; 
    int32_t thingToMemCpy;

    

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
    strcpy(operData, strtok(NULL, " \n"));
    
    
    addr = (int32_t)atoi(reg);
    convert(operString,vm);
    
    if(atoi(operData) >= 10000){
        printf("Word Overflow - Attempts to Place a Word in Memory that is Larger than 4 digits");
        exit(1);
    }

    if(vm->opcode == 22){
        memcpy(operandOne, operData,2);
        operandOne[2] = '\0';
        memcpy(operandTwo, &operData[2],2);
        operandTwo[2] = '\0';
        if((int)strlen(operData) > 4){
            printf("Undefined Use - Command is not in the Proper Format");
            exit(2);
        } 
        thingToMemCpy = ((int32_t)atoi(operData));
        memcpy(&vm->memory[addr], &thingToMemCpy, 4);

    } else {
        if((int)strlen(operData) > 2){
            printf("Undefined Use - Command is not in the Proper Format");
            exit(2);
        } 
        vm->operand = (int32_t)atoi(operData);
        thingToMemCpy = (vm->opcode * 100) + vm->operand;
        memcpy(&vm->memory[addr], &thingToMemCpy, 4);
        
    }
    
   
}

void printAll(VM *vm){
    int i;

    printf("\n");
    printf("REGISTERS: \n");
    printf("Accumulator:            %+05d\n", vm->acc);
    printf("Instruction Counter:    %02d\n", vm->ic);
    printf("Instruction Register:   ");
    printWordTwo(vm->ir);
    printf("\n");
    printf("OperationCode:          %02d\n", vm->opcode);
    printf("Operand:                %02d\n", vm->operand);
    printf("\n");
    printf("MEMORY:\n");
    printf("     0      1      2      3      4      5      6      7      8      9\n");
    printf("0   ");
        for(i=0;i<10;i++){
            printWord(vm->memory[i]);
            printf("  ");
        }
    printf("\n10  ");
        for(i=10;i<20;i++){
            printWord(vm->memory[i]);
            printf("  ");
        }
    printf("\n20  ");
        for(i=20;i<30;i++){
            printWord(vm->memory[i]);
            printf("  ");
        }
    printf("\n30  ");
        for(i=30;i<40;i++){
            printWord(vm->memory[i]);
            printf("  ");
        }
    printf("\n40  ");
        for(i=40;i<50;i++){
            printWord(vm->memory[i]);
            printf("  ");
        }
    printf("\n50  ");
        for(i=50;i<60;i++){
            printWord(vm->memory[i]);
            printf("  ");
        }
    printf("\n60  ");
        for(i=60;i<70;i++){
            printWord(vm->memory[i]);
            printf("  ");
        }
    printf("\n70  ");
        for(i=70;i<80;i++){
            printWord(vm->memory[i]);
            printf("  ");
        }
    printf("\n80  ");
        for(i=80;i<90;i++){
            printWord(vm->memory[i]);
            printf("  ");
        }
    printf("\n90  ");
        for(i=90;i<100;i++){
            printWord(vm->memory[i]);
            printf("  ");
            
        }
        printf("\n");

}
void execute(VM *vm){
    int k = 1;
    int i;
    int32_t op1 = 0;
    int32_t op2 = 0;
    int scanBuff = 0;

    while(k == 1){
        vm->ir = vm->memory[vm->ic];
        vm->opcode = vm->ir / 100;
        vm->operand = vm->ir % 100; 
        if(vm->operand >= 100){
            printf("Segmentation Fault - Tries to Access Unknown Address");
            exit(1);
        }
        switch (vm->opcode){
            case 10: /*READ*/
                scanBuff = 0;
                scanf("%d", &scanBuff);
                if(scanBuff >= 10000){
                    printf("Word Overflow - Attempts to place a Word in Memory larger than 4 digits");
                    break;
                } else {
                    vm->memory[vm->operand] = scanBuff;
                }
                vm->ic++;
                break;
            case 11: /*WRIT*/
                printWordTwo(vm->memory[vm->operand]);
                vm->ic++;
                break;
            case 12: /*PRNT*/
                for(i=vm->operand; ; i++){ 
                    op1 = vm->memory[i] / 100;
                    op2 = vm->memory[i] % 100;
                    if(op1 == 10 || op1 == '\0' || (op1 >= 65 && op1 <= 90)){
                        
                    } else {
                        printf("Unknown Character - When printing a String, an Unknown Character was reached");
                        exit(1);
                    }
                    if(op1 == '\0'){
                        break;
                    } else {
                        printf("%c",op1);
                    }
                    if(op2 == 10 || op2 == '\0' || (op2 >= 65 && op2 <= 90)){
                    
                    } else {
                        printf("Unknown Character - When printing a String, an Unknown Character was reached");
                        exit(1);
                    }
                    if(op2 == '\0'){
                        break;
                    } else {
                    printf("%c",op2);
                    }
                } 
                vm->ic++;            
                break;
            case 20: /*LOAD*/
                vm->acc = vm->memory[vm->operand];
                vm->ic++;
                break;
            case 21: /*STOR*/
                vm->memory[vm->operand] = vm->acc;
                vm->ic++;
                break;
            case 30: /*ADD*/
                vm->acc = vm->acc + vm->memory[vm->operand];
                vm->ic++;
                break;
            case 31: /*SUB*/
                vm->acc = vm->acc - vm->memory[vm->operand];
                vm->ic++;
                break;
            case 32: /*DIV*/
                if(vm->memory[vm->operand] == 0){
                    printf("Divide 0 - Division by 0 was attempted");
                    exit(1);
                    break;
                }
                vm->acc = vm->acc / vm->memory[vm->operand];
                vm->ic++;
                break;
            case 33: /*MULT*/
                vm->acc = vm->acc * vm->memory[vm->operand];
                vm->ic++;
                break;
            case 34: /*MOD*/
                if(vm->memory[vm->operand] == 0){
                    printf("Divide 0 - Division by 0 was attempted");
                    exit(1);
                    break;
                }
                vm->acc = vm->acc % vm->memory[vm->operand];
                vm->ic++;
                break;
            case 40: /*BRAN*/
                vm->ic = vm->operand;
                break;
            case 41: /*BRNG*/
                if(vm->acc < 0){
                    vm->ic = vm->operand;
                } else {
                    vm->ic++;
                }
                break;      
            case 42: /*BRZR*/
                if(vm->acc == 0){
                    vm->ic = vm->operand;
                } else {
                    vm->ic++;
                }
                break;
            case 99: /*HALT*/
                vm->ic++;
                printAll(vm);
                goto endOfForever;
                break;
            default:
            printf("Unknown command - Unrecognized command code");
            exit(1);

        }
        if(vm->ic >= 100 || vm->ic < 0){
            printf("Segmentation Fault - Tries to Access Unknown Address");
            exit(1);
        }
        if(vm->acc >= 10000){
            printf("Word Overflow - Attempts to Place a Word in Accumulator so that it is Larger than 4 digits");
            exit(1);
        }
    }       
    endOfForever:
    return;
}


int main(void) {
    VM vm;
    setStruct(&vm);
    while(fgets(input, 13, stdin)) {
		/* printf("%s\n", input); */
        compile(input,&vm);
    }
    if(isHalt == 0){
        printf("No HALT - No Halt Command is Ever Given");
        exit(3);
    }
    printf("Executing......\n");
    stdin = fopen("/dev/tty", "r");
    execute(&vm);
    return 0;
}



