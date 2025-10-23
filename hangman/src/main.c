#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>   
#include <stdbool.h>  
#include <ctype.h>    

const char* WORD_BANK[] = {
    "Wonderful",
    "Develop",
    "Constant",
    "Giraffe",
    "Hippo",
    "Human",
    "Banana",
    "Apple",
    "Peach",
    "Computer"
};

const char* HANG_STATES[] = {
    "        \n         \n         \n          \n         \n         ",
    "        \n         \n         \n          \n         \n ________",
    "        \n|        \n|        \n|         \n|        \n|________",
    "________\n|        \n|        \n|         \n|        \n|________",
    "________\n|       |\n|       O\n|         \n|        \n|________",
    "________\n|       |\n|       O\n|       | \n|        \n|________",
    "________\n|       |\n|       O\n|      /|     \n|          \n|________",
    "________\n|       |\n|       O\n|      /|\\ \n|          \n|________",    
    "________\n|       |\n|       O\n|      /|\\ \n|        \\ \n|________",
    "________\n|       |\n|       O\n|      /|\\ \n|      / \\ \n|________"
};

void clearScreen() {
    printf("\033[2J\033[H");
    fflush(stdout); 
}

const char* select_random_word(){
    int len_word_bank = sizeof(WORD_BANK) / sizeof(WORD_BANK[0]);
    int random_position = rand() % len_word_bank;
    return WORD_BANK[random_position];
}

void print_hang_state(int state){
    int num_states = sizeof(HANG_STATES) / sizeof(HANG_STATES[0]);
    if (state >= 0 && state < num_states) {
        printf("%s\n", HANG_STATES[state]);
    }
}

int main() {
    srand(time(NULL));
    
    const char* random_word = select_random_word();
    int word_len = strlen(random_word);
    int state = 0; 

    char lower_word[word_len + 1];
    for (int i = 0; i < word_len; i++) {
        lower_word[i] = tolower(random_word[i]);
    }
    lower_word[word_len] = '\0';

    char display_word[word_len + 1];
    for (int i = 0; i < word_len; i++) {
        display_word[i] = '_';
    }
    display_word[word_len] = '\0';

    char guessed_letters[27]; 
    int guessed_count = 0;
    guessed_letters[0] = '\0';

    printf("Welcome to Hangman! 🎮\n");

    while (true) {
        print_hang_state(state);
        printf("Word:    %s\n", display_word);
        printf("Guessed: %s\n\n", guessed_letters); // Show letters they've tried

        if (state >= 9) { 
            printf("Game Over! You lost! 💀\n");
            printf("The correct word was: %s\n", random_word);
            break;
        }

        if (strcmp(display_word, random_word) == 0) {
            printf("Congratulations! You guessed the word: %s 🎉\n", random_word);
            break;
        }

        char guess[100]; 
        printf("Guess a letter or the whole word: ");
        scanf("%s", guess);

        if (strlen(guess) == 1) {
            // --- Process single letter guess ---
            char letter = tolower(guess[0]);

            if (!isalpha(letter)) {
                printf("Please enter a letter.\n");
                continue; // Ask for input again
            }

            // --- FIX: Check if letter was already guessed ---
            if (strchr(guessed_letters, letter) != NULL) {
                printf("You already guessed '%c'. Try again.\n", letter);
                clearScreen();
                continue; // Ask for input again, don't penalize
            }

            // Add to guessed letters
            guessed_letters[guessed_count++] = letter;
            guessed_letters[guessed_count] = '\0';

            // --- FIX: Check if letter is in the word ---
            bool found_letter = false;
            for (int i = 0; i < word_len; i++) {
                if (lower_word[i] == letter) {
                    display_word[i] = random_word[i]; // Reveal original cased letter
                    found_letter = true;
                }
            }

            if (found_letter) {
                printf("Correct letter guess! 👍\n");
            } else {
                printf("Incorrect letter guess. 👎\n");
                state++; // --- FIX: Only increment state on *wrong* guess ---
            }

        } else {
            // --- Process whole word guess ---
            if (strlen(guess) != word_len) {
                printf("Your guess has the wrong number of letters. 👎\n");
                state++; // --- FIX: Count as wrong guess ---
            } else {
                // Convert guess to lowercase for comparison
                char lower_guess[word_len + 1];
                for(int i = 0; i < word_len; i++) {
                    lower_guess[i] = tolower(guess[i]);
                }
                lower_guess[word_len] = '\0';

                if (strcmp(lower_guess, lower_word) == 0) {
                    printf("Congratulations! You guessed the word: %s 🎉\n", random_word);
                    break; 
                } else {
                    printf("Incorrect word guess. 👎\n");
                    state++; 
                }
            }
        }
        clearScreen();
        printf("\n------------------------------------\n"); 
    }

    return 0;
}