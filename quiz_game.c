#include <stdio.h>
#include <time.h>
#include "game_menu.c"

void show_jokers(int jokers){
    printf("\nRemaining jokers: %d\n", jokers);
}

char* get_random_wrong_answer(Question q){
    int wrong_answers[2];
    int count = 0;

    for(int i = 0; i < 4; i++){
        if(strcmp(q.answers[i], q.correctAns)!= 0){
            wrong_answers[count++] = i;
        }
    }

    srand(time(NULL));
    int index = rand()% count;
    return q.answers[wrong_answers[index]];
}

double simulate_friend_hint(Question q, int difficulty){
    double chance;
    switch(difficulty){

        case 1: 
            chance = 0.8; 
            break;
        case 2:
            chance = 0.6;
            break;
        case 3: 
            chance = 0.3;
            break;
        default: 
            chance = 0.5;
            break;
    }

    return chance;

}

double simulate_audience_vote(Question q, int difficulty){
    double votes[4] = {0};
    srand(time(NULL));
    for(int i = 0;i < 4; i++){
        votes[i] += ((rand()% 100) / 100.0);
    }

    double max_vote = *max_element(votes,votes + 4);
    return max_vote;
}