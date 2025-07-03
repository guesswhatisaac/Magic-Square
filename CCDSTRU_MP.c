#include <stdio.h>

#define BOARD_SIZE 3

// represents player's inputs
struct playerTag{
    int row;
    int column;
    int peg;
};


// represents grid's values
struct gridTag{
    int x;
    int y;
    int value;
    int statePos; // free or occupied
};

// represents set's values
struct setsTag{
    int value[6][3];
    int count[6];
    int summation[6];
};

typedef struct playerTag playerTag[2];
typedef struct gridTag gridTag;
typedef struct setsTag setsTag;

void promptUserInput(playerTag player, int *turn);
void nextPlayerMove(playerTag player, gridTag board[][BOARD_SIZE], setsTag *sets, int *turn);
void gameOver(setsTag sets, gridTag board[][BOARD_SIZE], int turn, int *over);
void printBoard(gridTag board[][BOARD_SIZE]);

int main(void){

    // initialize variables
    int turn = 1, over = 0;
    playerTag player;
    gridTag board[BOARD_SIZE][BOARD_SIZE];
    setsTag sets;

    // initialize board
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            board[i][j].value = 0;
            board[i][j].x = i;
            board[i][j].y = j;
            board[i][j].statePos = 0; // 0 means free, 1 means occupied
        }
    }
    
    // initialize sets
    for(int i = 0; i < 6; i++){
        sets.count[i] = 0;
        sets.summation[i] = 0;
    }

    while(!over){
        printBoard(board);
        promptUserInput(player, &turn);
        nextPlayerMove(player, board, &sets, &turn);
        gameOver(sets, board, turn, &over);   
    }

    return 0;
}

void promptUserInput(playerTag player, int *turn){

    int tempRow, tempColumn, tempPeg;
    char whichPlayer;

    // check which player's turn
    if(*turn == 0)
        whichPlayer = 'B';
    if(*turn == 1)
        whichPlayer = 'A';

    printf("  [ Player %c's turn! ]\n\n", whichPlayer);

    // prompt input
    do{
        printf("Input (Row, Column): ");
        scanf("%d %d", &tempRow, &tempColumn);

        if(tempRow > 3 || tempRow < 1){
            printf("Invalid Row\n");
        }
        if(tempColumn > 3 || tempColumn < 1)
            printf("Invalid Column\n");
        
        printf("\n");
    } while(tempRow > 3 || tempRow < 1 || tempColumn > 3 || tempColumn < 1);
    
    do{
        printf("Input Peg: ");
        scanf("%d", &tempPeg);

        if(tempPeg > 9 && tempPeg < 1)
            printf("Invalid Peg\n");
        
    } while(tempPeg > 9 && tempPeg < 1);

    // if all inputs are valid, assign values.
    player[*turn].peg = tempPeg;
    player[*turn].row = tempRow;
    player[*turn].column = tempColumn;

    printf("\n");
    
}

void nextPlayerMove(playerTag player, gridTag board[][BOARD_SIZE], setsTag *sets, int *turn){
    
    int playerRow, playerCol, isUsed;

    // reverts input values to zero index
    playerRow = player[*turn].row - 1;
    playerCol = player[*turn].column - 1;

    // check if peg is used
    isUsed = 0;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].value == player[*turn].peg)
                isUsed = 1;
        }
    }

    // if valid inputs, occupy board.statePos with the peg and update necessary values
    if(board[playerRow][playerCol].statePos == 0 && isUsed == 0){
        
        board[playerRow][playerCol].value = player[*turn].peg;
        board[playerRow][playerCol].statePos = 1;

        // check for peg's x position and assign to corresponding set
        for(int i = 0; i < 3; i++){ // T M B
            if((playerRow+1) == i+1){
                sets->value[i][sets->count[i]] = player[*turn].peg; 
                sets->count[i]++; // increment set's counter
            }
        }

        // check for peg's y position and assign to corresponding set
        for(int i = 0; i < 3; i++){ // L C R
            if((playerCol+1) == i+1){
                sets->value[i+3][sets->count[i+3]] = player[*turn].peg; 
                sets->count[i+3]++; // increment set's counter
            }
        }
    }
    // print error message if invalid
    else if(board[playerRow][playerCol].statePos == 1 || isUsed == 1){
        if(board[playerRow][playerCol].statePos != 0 && isUsed == 1)
            printf("Peg used and position is occupied. Turn skipped!\n\n");
        else if(board[playerRow][playerCol].statePos == 1)
            printf("Position is occupied. Turn skipped!\n\n");
        else if(isUsed == 1)
            printf("Peg used. Turn skipped!\n\n");

    }

    // update turn
    if(*turn == 0)
        *turn = 1;
    else if(*turn == 1)
        *turn = 0;
}

void gameOver(setsTag sets, gridTag board[][BOARD_SIZE], int turn, int *over){

    int all_15 = 0, winner = 0;

    // get summation if a set is built
    for(int i = 0; i < 6; i++){
        if(sets.count[i] == 3){
            for(int j = 0; j < sets.count[i]; j++)
                sets.summation[i] += sets.value[i][j];
        }
    }
    
    for(int i = 0; i < 6; i++){ // there exists a set with set.sum less than 15
        if(sets.count[i] == 3 && sets.summation[i] < 15){ // if a set built is less than 15,
            if(turn == 1){
                winner = 0;
                *over = 1;
            }
            else if(turn == 0){
                winner = 1;
                *over = 1;
            }
        }
    }


    // for all sets, all set.sum is == 15
    for(int i = 0; i < 6; i++){
        if(sets.count[i] == 3 && sets.summation[i] == 15)
            all_15++;
    }

    if(all_15 == 6){ // determines who win in the case that all sets are 15
        if(turn == 1){
            winner = 1;
            *over = 1;
        }
        else if(turn == 0){
            winner = 0;
            *over = 1;
        }
    }

    // print winner and the final board
    if(*over){
        printBoard(board);
        if(winner == 1)
            printf("Player A wins!\n");
        else if(winner == 0)
            printf("Player A wins!\n");
    }
}

void printBoard(gridTag board[][BOARD_SIZE]){

    printf("\n");

    printf(" _______________________\n");
    printf("|       |       |       |\n");
    printf("|   %d   |   %d   |   %d   |\n", board[0][0].value, board[0][1].value, board[0][2].value); // 1
    printf("|_______|_______|_______|\n");
    printf("|       |       |       |\n");
    printf("|   %d   |   %d   |   %d   |\n", board[1][0].value, board[1][1].value, board[1][2].value); // 2
    printf("|_______|_______|_______|\n");
    printf("|       |       |       |\n");
    printf("|   %d   |   %d   |   %d   |\n", board[2][0].value, board[2][1].value, board[2][2].value); // 3
    printf("|_______|_______|_______|\n");

    printf("\n");

}