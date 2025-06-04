// s-snt21

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
    #define CLS "cls"
#else
    #define CLS "clear"
#endif

//board dimensions
#define ROWS 6
#define COLS 7

//define player colors for console output
#define RESET  "\033[0m"
#define RED  "\033[1;31m"
#define YELLOW  "\033[0;33m"

void title(void);  //prints the game title
int menu(void);    //displays the main menu
void end(void);    //shows an end message
void instructions(void);                        //displays the game instructions
void initialize(char brd[ROWS][COLS]);          //initializes the board with empty slots
void print_static_board(char brd[ROWS][COLS]);  //prints the static board
//prints the board with an animation of the piece falling into the slot
void dropped_piece_animation(char brd[ROWS][COLS], int column, int empty_row, int plr);
int empty_slot(char brd[ROWS][COLS], int column);  //finds the lowest empty slot in a given column
void insert_piece(char brd[ROWS][COLS], int plr);  //handles player input for piece placement
int game_over(char brd[ROWS][COLS], int plr);      //checks if the current player has won
void print_win(int plr);                //displays a winning animation
void print_draw(char brd[ROWS][COLS]);  //displays a message for a draw

int main() {
    char board[ROWS][COLS];            //game board
    int new_game = 1, pieces = 0;      //flag new game, n of pieces played
    int game_running = 1, player = 0;  //flag game running, current player
    //displays menu and handles choice
    do {
        while (new_game) {
            switch (menu()) {
            case 1:
                player = 0;
                new_game = 0;
                initialize(board);
                break;
            case 2:
                instructions();
                break;
            case 3:
                end();
                return 0;
            default:
                break;
            }
        }
        //main game loop
        insert_piece(board, player);
        pieces++;
        game_running = !(game_over(board, player));

        if (!game_running)
            print_win(player);

        if (pieces == ROWS * COLS) {
            game_running = 0;
            print_draw(board);
        }

        player = !player;
        //asks if players want to start a new game
        while (!game_running) {
            char input = 'd';
            
            system(CLS);
            printf("Would you like to play again? (y/n): ");
            scanf(" %c", &input);
            while (getchar() != '\n');

            switch (input) {
            case 'y':
            case 'Y':
                new_game = 1;
                player = 0;
                game_running = 1;
                pieces = 0;
                break;
            case 'n':
            case 'N':
                end();
                return 0;
            default:
                printf("Invalid input...");
                usleep(2000000);
                break;
            }
        }

    } while (game_running);
    return 0;
}

void title() {
    system(CLS);
    printf("\n\n");
    printf("\t    :::          ::::::::::: ::::    :::            :::            :::::::::   ::::::::  :::       ::: \n");
    printf("\t   :+:               :+:     :+:+:   :+:          :+: :+:          :+:    :+: :+:    :+: :+:       :+: \n");
    printf("\t  +:+ +:+            +:+     :+:+:+  +:+         +:+   +:+         +:+    +:+ +:+    +:+ +:+       +:+ \n");
    printf("\t +#+  +:+            +#+     +#+ +:+ +#+        +#++:++#++:        +#++:++#:  +#+    +:+ +#+  +:+  +#+ \n");
    printf("\t+#+#+#+#+#+          +#+     +#+  +#+#+#        +#+     +#+        +#+    +#+ +#+    +#+ +#+ +#+#+ +#+ \n");
    printf("\t      #+#            #+#     #+#   #+#+#        #+#     #+#        #+#    #+# #+#    #+#  #+#+# #+#+#  \n");
    printf("\t      ###        ########### ###    ####        ###     ###        ###    ###  ########    ###   ###   \n\n\n");
}

int menu() {
    //this function shows a menu with 3 options, it takes
    //an input and returns it to the main function only if it is valid
    int input = 0;
    char buffer[10];
    
    do {
        system(CLS);
        title();
        printf("\n\t\t WELCOME TO \"4 IN A ROW\"\n\n");
        printf("\tType:\n");
        printf("\t1 - to start a new game\n");
        printf("\t2 - to view the instructions\n");
        printf("\t3 - to quit\n\n");
        printf("\tSelect an option and type the number\n");
        printf("\tand press enter to continue: ");

        //input validating
        fgets(buffer, sizeof(buffer), stdin);

        if (buffer[strlen(buffer) - 1] != '\n') {
            int ch;
            while ((ch = getchar()) != '\n');
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (sscanf(buffer, "%d", &input) != 1) {
            input = -1;
        }
        
    } while (input < 1 || input > 3); //input conditions

    return input;
}

void end() {
    system(CLS);
    title();
    printf("\n\tThanks for playing,\n\t\tGoodbye!");
    usleep(1500000);
}

void instructions() {
    system(CLS);
    printf("\t\t\t\t*** 4 IN A ROW INSTRUCTIONS ***\n\n");
    printf("1. The game board is made up of 6 rows and 7 columns.\n\n");
    printf("2. On each turn, a player selects a column to drop their piece into.\n\n");
    printf("3. Players take turns placing a piece in a column of their choice.\n\n");
    printf("4. The piece falls to the lowest available \"slot\" in the selected column.\n\n");
    printf("5. The objective is to align four pieces of the same color in a row either horizontally,\n");
    printf("   vertically, or diagonally.\n\n");
    printf("6. The first player to align four pieces in a row wins the game.\n\n");
    printf("7. If the board fills up without any player connecting four pieces,\n");
    printf("   the game ends in a draw.\n");
    printf("\n\t\t\t\t\t*** PIECES ***\n\n");
    printf("\t\t\t\t\tPlayer 1: %s0%s\n", RED, RESET);
    printf("\t\t\t\t\tPlayer 2: %s0%s\n\n", YELLOW, RESET);
    printf("\tPress Enter to return to the main menu...\n");
    while(getchar() != '\n');
}

void initialize(char brd[ROWS][COLS]) {
    //it initializes the board with empty slots ('O' characters)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            brd[i][j] = 'O';
        }
    }
}

int empty_slot(char brd[ROWS][COLS], int column) {
    //this one returns the first empty slot in the column selected by the user
    //it returns -1 if the column is full
    for (int i = ROWS - 1; i >= 0; i--) {
        if (brd[i][column] == 'O') 
            return i;
    }
    return -1;
}

void print_static_board(char brd[ROWS][COLS]) {
    //this function prints the board
    system(CLS);
    title();

    for (int i = 0; i < ROWS; i++) {
        printf("\t\t\t\t|");
        for (int j = 0; j < COLS; j++) {
            switch (brd[i][j]) {
            case 'R':
                printf("%s0%s|", RED, RESET);
                break;
            case 'Y':
                printf("%s0%s|", YELLOW, RESET);
                break;
            default:
                printf("O|");    
                break;
            }
        }
        printf("\n");
    }
    printf("\t\t\t\t 1 2 3 4 5 6 7\n");
}

void dropped_piece_animation(char brd[ROWS][COLS], int column, int empty_row, int plr) {
    //This function prints an animation of the piece falling into the slot
    //thanks to an auxiliary game board that copies the state
    //of the original before the piece is played and is updated every frame
    //to show the piece falling
    char aux_board[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {     
        for (int j = 0; j < COLS; j++)
            aux_board[i][j] = brd[i][j];
    }
    print_static_board(brd);
    for (int i = 0; i <= empty_row; i++) {
        system(CLS);
        for (int j = 0; j < ROWS; j++){
            for (int k = 0; k < COLS; k++)
                aux_board[j][k] = brd[j][k];
        }
        aux_board[i][column] = plr ? 'Y' : 'R'; 
        print_static_board(aux_board);
        usleep(600000);
    }
}

void insert_piece(char brd[ROWS][COLS], int plr) {
    //this function handles the player's turn for inserting a piece,
    //it prompts the player to choose a column, validates the input
    //and updates the board accordingly sets
    //the color for the current player
    int column;
    int invalid_input = 0;
    const char *player_color = plr ? YELLOW : RED;

    do {
        print_static_board(brd); //displays the current state of the board

        if (invalid_input) {
            printf("\nThe selected column is invalid or might be full.\n");
            usleep(2000000);
            print_static_board(brd);
        }
        printf("\n%sPlayer %d%s ", player_color, plr +1, RESET);
        printf("it's your turn. Which column do you want to drop your piece in?\n");
        if (invalid_input) {
            printf("\nPlease enter a valid column.\n\n");
            printf("Enter the number (from 1 to 7) of the desired column: ");
        } else
            printf("Enter the number (from 1 to 7) of the desired column: ");

        if (scanf("%d", &column) != 1) {
            while (getchar() != '\n');
            column = -1;
        }
        column--;
        //checks if the selected column is within range and not full
        invalid_input = ((column < 0 || column > 6) || empty_slot(brd,column) == -1);

    }while (invalid_input);

    int empty_row = empty_slot(brd,column);                //gets the lowest empty row in the chosen column
    dropped_piece_animation(brd, column, empty_row, plr);  //piece falling into position
    brd[empty_row][column] = plr ? 'Y' : 'R';              //places the player's piece on the board
}

int game_over(char brd[ROWS][COLS], int plr) {
    char player_piece = plr ? 'Y' : 'R';
    //horizontal check
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) { //make sure there are enough columns
            if (brd[i][j] == player_piece && brd[i][j + 1] == player_piece &&
                brd[i][j + 2] == player_piece && brd[i][j + 3] == player_piece) {
                return 1; //4 consecutive horizontal pieces
            }
        }
    }
    //vertical check
    for (int i = 0; i < ROWS - 3; i++) { //make sure there are enough rows
        for (int j = 0; j < COLS; j++) {
            if (brd[i][j] == player_piece && brd[i + 1][j] == player_piece &&
                brd[i + 2][j] == player_piece && brd[i + 3][j] == player_piece) {
                return 1; //4 consecutive vertical pieces
            }
        }
    }
    //diagonal check top-left to bottom-right
    for (int i = 0; i < ROWS - 3; i++) { //make sure there are enough rows
        for (int j = 0; j < COLS - 3; j++) { //make sure there are enough columns
            if (brd[i][j] == player_piece && brd[i + 1][j + 1] == player_piece &&
                brd[i + 2][j + 2] == player_piece && brd[i + 3][j + 3] == player_piece) {
                return 1; //4 consecutive descending diagonal pieces
            }
        }
    }
    //diagonal check top-right to bottom-left
    for (int i = 3; i < ROWS; i++) { //make sure there are enough rows
        for (int j = 0; j < COLS - 3; j++) { //make sure there are enough columns
            if (brd[i][j] == player_piece && brd[i - 1][j + 1] == player_piece &&
                brd[i - 2][j + 2] == player_piece && brd[i - 3][j + 3] == player_piece) {
                return 1; //4 consecutive ascending diagonal pieces
            }
        }
    }
    return 0; //no winning condition found
}


void print_win(int plr) {
    const char *winner_color = plr ? YELLOW : RED;
    char phrase[40];
    sprintf(phrase, "CONGRATULATIONS PLAYER %d! YOU WIN!", plr + 1);

    for (int i = 0; i < 40; i++) { //shows a little animation
        system(CLS);
        title();
        printf("\t\t\t");
        for (int j = 0; j < i; j++) {
            printf("%c", phrase[j]);
        }
        printf("%s0%s\n", winner_color, RESET);
        usleep(100000);
    }
    usleep(2000000);
}

void print_draw(char brd[ROWS][COLS]) {
    print_static_board(brd);
    printf("\n");
    printf("\t\t\t   THE GAME BOARD IS FULL,\n");
    printf("\t\t\tTHE GAME ENDS WITH A DRAW!");
    usleep(3000000);
}