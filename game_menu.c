#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h> 
#include "logic.h"

#define QUESTIONS 3

void display_menu(){
    
    printf("\n Options:");
    printf("\n 1. Start a new game.\n 2. Add question.\n 3. Edit question.\n 4. Exit.");
    printf("\n Choice: ");
}

void show_jokers(int jokers_left[3]){
    printf("\nRemaining jokers: %d\n");
    if(jokers_left[0]) printf("1. 50/50 (available)\n"); else printf("1. 50/50 (used)\n");
    if(jokers_left[1]) printf("2. Call a friend (available)\n"); else printf("2. Call a friend (used)\n");
    if(jokers_left[2]) printf("3. Audience help (available)\n"); else printf("3. Audience help (used)\n");
}

char* get_random_wrong_answer(Question *q){
    int wrong_answers[3];
    int count = 0;
    for(int i = 0; i < 4; i++){
        if(strcmp(q->answers[i], q->correctAns) != 0){
            wrong_answers[count++] = i;
        }
    }

    srand(time(NULL));
    int index = rand() % count;
    return q->answers[wrong_answers[index]];
}

void use_5050_joker(Question *q){
    int wrong_answers[3];
    int count = 0;

    for(int i = 0; i < 4; i++){
        if(strcmp(q->answers[i], q->correctAns) != 0){
            wrong_answers[count++] = i;
        }
    }

    srand(time(NULL));
    int remove_idx1 = rand() % count;
    int remove_idx2;
    do{
        remove_idx2 = rand() % count;
    }while(remove_idx2 == remove_idx1);

    for(int i = 0; i < 4;i++){
        if(i == wrong_answers[remove_idx1] || i == wrong_answers[remove_idx2]){
            strcpy(q->answers[i], "");
        }
    }
}

void use_call_friend_joker(Question q, int difficulty){
    printf("Calling a friend....\n");
    srand(time(NULL));
    int chance = rand() % 100;
    printf("Friend suggests the right answer is:");
    if(chance < 50 + difficulty * 5){
        printf("%s\n", q.correctAns);
    }else{
        printf("%s\n",get_random_wrong_answer(&q));
    }

}

void use_audience_help_joker(Question q, int difficulty){
    printf("Audience poll...\n");
    srand(time(NULL));
    int correct_chance = 50 + difficulty *5;
    printf("Audience suggests:\n");

    for(int i = 0; i < 4; i++){
        int chance = rand() % 100;
        if(strcmp(q.answers[i], q.correctAns) == 0){
          printf("%d. %s: %d%%\n", i + 1, q.answers[i], correct_chance);  
        }else{ 
            printf("%d. %s: %d%%\n", i + 1, q.answers[i], 100 - correct_chance);
        }
    }
}


void play_game(Collection* col){
    if(col->size < QUESTIONS){
        printf("Not enough questions to start the game. \n");
        return;
    }

    Question selected_questions[QUESTIONS];
    srand(time(NULL));
    for(int i = 0; i < QUESTIONS; i++){
        int index = rand() % col->size;
        selected_questions[i] = *col->questions[index];
    }

    for(int i = 0; i < QUESTIONS - 1; i++){
        for(int j = 0; j < QUESTIONS - i - 1;j++){
            if(selected_questions[i].difficulty > selected_questions[j + 1].difficulty){
                Question temp = selected_questions[j];
                selected_questions[j] = selected_questions[j+1];
                selected_questions[j + 1] = temp;
            }
        }
    }
    
    int score = 0;
   // int jokers = 3;
    int jokers_left[3] = {1, 1, 1};
    int current_question = 0;

    while(current_question < QUESTIONS){
        Question q = selected_questions[current_question];
        printf("\nQuestion %d: %s\n", current_question + 1, q.question);
        for(int i =  0;i < 4; i++){
            if(strcmp(q.answers[i], "") != 0){
                printf("%d. %s\n", i + 1, q.answers[i]);
            }
        }

        show_jokers(jokers_left);
        printf("Enter your answer (1-4) or 'j' to use a joker: ");
        char choice[QUESTIONS];
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';

        if(strcmp(choice, "j") == 0){
            if(jokers_left[0] || jokers_left[1] || jokers_left[2]){
                int joker_choice;
                printf("Choose a joker:\n");
                show_jokers(jokers_left);
                scanf("%d", &joker_choice);
                getchar();

                switch(joker_choice){
                    case 1: 
                        if(jokers_left[0]){
                            use_5050_joker(&q);
                        } else
                        jokers_left[0] = 0;
                        break;
                    case 2:
                        if(jokers_left[1]){
                            use_call_friend_joker(q, q.difficulty);

                        }
                        jokers_left[1] = 0;
                        break;
                    case 3:
                        if(jokers_left[2]){
                            use_audience_help_joker(q, q.difficulty);
                        }
                        jokers_left[2] = 0;
                        break;
                    default:
                        printf("Invalid joker.\n");
                        break;
                }

            }else{
                printf("No jokers left. \n");
            }
            continue;
        }else{
            int answer_choice = atoi(choice);
            if(answer_choice < 1 || answer_choice > 4 || strcmp(q.answers[answer_choice - 1], "") == 0){
                printf("Invalid answer.\n");
                continue;
            }

            if(strcmp(q.answers[answer_choice - 1], q.correctAns) == 0){
                printf("Correct!\n");
                score++;
                current_question++;
            } else{
                printf("Incorrect. The answer was: %s\n", q.correctAns);
                break;
            }

        }

        if(current_question == QUESTIONS){
            printf("Congratulations!! You won!!\n");
        }
        
    }

    printf("Game over. Your score: %d10\n", score);


}

int main(){
    Collection* col  = read_file("questions.txt");
    int choice; 
    printf("\n BECOME RICH ");

    while(1){
        display_menu();
        scanf("%d", &choice);
        getchar();

        switch(choice){
            
            case 1:
                play_game(col); 
                break;
            case 2:
                add_question("questions.txt",col);
                break;
            case 3:
                edit_question("questions.txt", col);
                break;
            case 4:
                printf("\n Exiting..");
                free(col);
                return 0;
                break;

            default : 
                printf("\nInvalid choice."); 
                break;
        }

    }

    return 0;
}


