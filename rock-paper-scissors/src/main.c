#include <stdio.h> 
#include <stdlib.h>

typedef struct {
    int player_score;
    int computer_score;
} Scores;

Scores evaluate_game(int user_choice, int computer_choice, Scores scores) {
    if (user_choice == computer_choice) {
        printf("It's a tie!\n");
    } else if ((user_choice == 1 && computer_choice == 3) ||
               (user_choice == 2 && computer_choice == 1) ||
               (user_choice == 3 && computer_choice == 2)) {
        printf("You win!\n");
        scores.player_score += 1;
    } else {
        printf("Computer wins!\n");
        scores.computer_score +=1;
    };
    return scores;
}

int get_user_choise() {
    int user_choice;
    printf("Enter your choice (1: Rock, 2: Paper, 3: Scissors): ");
    scanf("%d", &user_choice); // read input

    if (user_choice < 1 || user_choice > 3) {
        printf("Invalid choice! Please select 1, 2, or 3.\n");
        return 1;
    }
    return user_choice;
}

int get_computer_choise(){
    return  (rand() % 3) + 1; 
}

void print_running_scores(Scores scores){
    printf("Computer Score: %d Player Score: %d \n", scores.computer_score, scores.player_score);
}

int main() {

    printf("Welcome to Rock, Paper, Scissors!\n");
    Scores scores = {0,0}; // initalise them to 0.
    while (true) {
        print_running_scores(scores);
        int user_choice = get_user_choise();
        int computer_choice = get_computer_choise();
        printf("Computer chose: %d\n", computer_choice);
        scores = evaluate_game(user_choice, computer_choice,scores);
        // next game?
        char user_continue;
        printf("Continue to next game (y/n)? ");
        scanf(" %c", &user_continue); // read input
        if (user_continue == 'y' || user_continue =='Y') {
            continue;
        } else {
            break;
        }
    }
    printf("Goodbye! Final Score is...\n");
    print_running_scores(scores);
    return 0;
}