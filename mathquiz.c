#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;
int count2;
int difficulty;
int questions;
int score;
int answer;
int value1;
int value2;
int operation;

int count2 = 1;
int count = 0;

typedef enum OperationType {

    ADD,
    SUB,
    MUL,
    DIV
};

/* srand(time(NULL));*/

void get_data()
    {
        printf("How many questions for this test(1-20)? ");
        scanf("%d", &count);
        printf("\n");
        printf("Select Difficulty (1-4): ");
        scanf("%d", &difficulty);
    }



int generate_question(int difficulty, int count)
    {
        int bound2;
        char opstring;
        

        if(difficulty == 1){
            bound2 = 10;
        } else if(difficulty == 2) {
            bound2 = 50;
        } else if(difficulty == 3) {
            bound2 = 100;
        } else if(difficulty == 4) {
            bound2 = 100;
        }

        operation = (rand() % 4) + 1;

        if(operation == 1){
            opstring = '+';
            /* this declares a new variable */
        } else if(operation == 2){
             opstring = '-';
        } else if(operation == 3){
             opstring = '*';
        } else if(operation == 4){
             opstring = '/';
        }

        value1 = rand() % bound2;
        value2 = rand() % bound2;

        
        printf("Question %d: %d %c %d", count2, value1, opstring, value2);
        scanf("%d", &answer);
        printf("\n");

        
        
        return operation;
    }

int answer_question(int count, int operation, int value1, int value2,int answer)
    {
        int true_answer;
        if (operation == 1) {
            true_answer = value1 + value2;

        } else if (operation == 2){
            true_answer = value1 - value2;
        } else if (operation == 3){
            true_answer = value1 * value2;
        }

    }

int print_response()
    {

    }

int main(int argc, char *argv[])
    {
        int i;
        get_data();
        
        for (i = 0; i < count; i++){
            generate_question(difficulty, count);
            count2++;
            answer_question(count, operation, value1, value2, answer);
        }

        return 0;
    }

