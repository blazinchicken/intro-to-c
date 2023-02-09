#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;
int difficulty;
int questions;
int count2;
int score;

int count = 0;
int count2 = 1;

srand(time(NULL));

int main(int argc, char *argv[])
    {
        get_data();
        if (count2 <= count){
            generate_question(difficulty, count);
        }
    }

int get_data()
    {
        printf("How many questions for this test(1-20)? ");
        scanf("%d", &count);
        printf("\n");
        printf("Select Difficulty (1-4): ");
        scanf("%d", &difficulty);
        return difficulty, count ;
    }

int generate_question(int difficulty, int count)
    {
        int bound1;
        int bound2;
        int value1;
        int value2;
        int operation;
        char opstring[] = "void";
        

        if(difficulty == 1){
            bound1 = 1;
            bound2 = 10;
        } else if(difficulty == 2) {
            bound1 = 1;
            bound2 = 50;
        } else if(difficulty == 3) {
            bound1 = 1;
            bound2 = 100;
        } else if(difficulty == 4) {
            bound1 = -100;
            bound2 = 100;
        }

        operation = rand() % 4;

        if(operation == 1){
            char opstring[] = "+";
        } else if(operation == 2){
            char opstring[] = "-";
        } else if(operation == 3){
            char opstring[] = "*";
        } else if(operation == 4){
            char opstring[] = "/";
        }

        value1 = rand() % bound2;
        value2 = rand() % bound2;

        
        printf("Question %d:", count2);
        printf("%d ",value1);
        printf("%s ", opstring);
        printf("%d ",value2);

        count2++;
        
        return operation, count2;
    }

int answer_question(int count, int operation)
    {

    }

int print_response()
    {

    }

