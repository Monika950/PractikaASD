#include <stdio.h>
#include "logic.h"

void display_menu(){
    
    printf("\n Options:");
    printf("\n 1. Start a new game.\n 2. Add question.\n 3. Edit question.\n 4. Exit.");
    printf("\n Choice: ");

}

void play_game(Collection* col){
    int score = 0;
    int jokers = 3;
    int current_question = 0;

    Question* current_question = col->questions[current_question];


}

int main(){
    Collection* col  = read_file("questions.txt");
    int choice; 
    printf("\n BECOME RICH ");

    while(1){
        display_menu();
        scanf("%d", &choice);

        switch(choice){
            
            case 1:
                play_game(col); 
                break;
            case 2:
                add_question("questions.txt",col);
                break;
            case 3:
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


