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
int true_answer;
int correct = 0;

int count2 = 1;
int count = 0;
time_t t;

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

        if(operation == 4 && value2 == 0){
            value2 = rand() % bound2;
        }

        if(operation == 4 && value1 == 0){
            value1 = rand() % bound2;
        }

        
        printf("Question %d: %d %c %d = ", count2, value1, opstring, value2);
        scanf("%d", &answer);
        printf("\n");

        
        
        return operation;
    }

int answer_question(int count, int operation, int value1, int value2,int answer)
    {
        
        if (operation == 1) {
            true_answer = value1 + value2;
        } else if (operation == 2){
            true_answer = value1 - value2;
        } else if (operation == 3){
            true_answer = value1 * value2;
        } else if (operation == 4){
            true_answer = value1 / value2;
        }

        if (true_answer == answer){
            correct = 1;
            score++;
        } else {
            correct = 0;
        }
        return correct;
        return true_answer;
    }

void print_response(int correct, int true_answer)
    {
        int rand_response;

        if (correct == 1){
            rand_response = rand() % 3;
            if(rand_response == 0) {
                printf("Good Job!\n");
            } else if(rand_response == 1) {
                printf("Nice Work!\n");
            } else if(rand_response == 2) {
                printf("Awesome!\n");
            }
        } else if (correct == 0) {
            rand_response = rand() % 3;
            if(rand_response == 0) {
                printf("Nice Try!\n");
            } else if(rand_response == 1) {
                printf("Sorry!\n");
            } else if(rand_response == 2) {
                printf("Maybe Next Time!\n");
            }
            printf("The correct answer was %d\n",true_answer);
        }

    }

int main(void)
    {
        int i;
        get_data();
        srand((int) time(0));
        
        for (i = 0; i < count; i++){
            generate_question(difficulty, count);
            count2++;
            answer_question(count, operation, value1, value2, answer);
            print_response(correct, true_answer);
        }
        printf("Score %d/%d", score, count);

        return 0;
    }

