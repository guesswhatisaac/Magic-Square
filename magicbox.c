#include <stdio.h>

void nextPlayerMove(int nRow, int nCol, int nPeg, int nSpace[][3], int *nOk, int *nNext, int *isInvalid,
                    int *isOver, int *isLessThan, int *nOne, int *nTwo, int *nThree, int *nFour, int *nFive, int *nSix,
                    int *nOneCnt, int *nTwoCnt, int *nThreeCnt, int *nFourCnt, int *nFiveCnt, int *nSixCnt);
void gameOver(int nTurn, int isLessThan, char cPlayers[]);
void printBoard(int S[3][3]);

int main()
{
    char cPlayers[] = {'A', 'B'};
    int nSpace[3][3] ={{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int nOne = 0, nTwo = 0, nThree = 0, nFour = 0, nFive = 0, nSix = 0;
    int nOneCnt = 0, nTwoCnt = 0, nThreeCnt = 0, nFourCnt = 0, nFiveCnt = 0, nSixCnt = 0;

    int nOk = 0;
    int isOver = 0;
    int isLessThan = 0;
    int isInvalid = 0;

    int nTurn = 1;
    int nNext = 0;

    int nRow;
    int nCol;
    int nPeg;

    while (!isOver)
    {
        if (nTurn == 1)
            printf("\nPlayer %c turn\n\n", cPlayers[0]);
        else
            printf("\nPlayer %c turn\n\n", cPlayers[1]);

        printBoard(nSpace);

        printf("\nSelect Row: ");
        scanf("%d", &nRow);
        printf("Select Column: ");
        scanf("%d", &nCol);
        printf("Choose Peg (1 - 9): ");
        scanf("%d", &nPeg);

        nextPlayerMove(nRow, nCol, nPeg, nSpace, &nOk, &nNext, &isInvalid,
                       &isOver, &isLessThan, &nOne, &nTwo, &nThree, &nFour, &nFive, &nSix,
                       &nOneCnt, &nTwoCnt, &nThreeCnt, &nFourCnt, &nFiveCnt, &nSixCnt);

        if((nOne == 15) && (nTwo == 15) && (nThree == 15) && (nFour == 15) && (nFive == 15) && (nSix == 15))
            isOver = 1;    // 'pag yung sums ng bawat row and col equals 15, game over na wenk
        
        if((isOver == 0) && (isInvalid == 0))
            nTurn = !nTurn;   // switch turns players kapag hindi pa over
    
    }
    
    printBoard(nSpace);
    gameOver(nTurn, isLessThan, cPlayers);

    return 0;
}

void
nextPlayerMove(int nRow, int nCol, int nPeg, int nSpace[][3], int *nOk, int *nNext, int *isInvalid,
                    int *isOver, int *isLessThan, int *nOne, int *nTwo, int *nThree, int *nFour, int *nFive, int *nSix,
                    int *nOneCnt, int *nTwoCnt, int *nThreeCnt, int *nFourCnt, int *nFiveCnt, int *nSixCnt)
{
	if ((nPeg <= 9) && (nSpace[nRow - 1][nCol - 1] == 0) && (nRow >= 1) && (nRow <= 3) && (nCol >= 1) && (nCol <= 3))
    { 
        nSpace[nRow - 1][nCol - 1] = nPeg;// peg is an element of Peg AND pos is an element of Free
		*nOk = 1; // ok = !ok;
        *isInvalid = 0;
		// Occ = Occ U {pos};
        if (*nOk == 1)
        {
            /*
            if(nOk && pos is an element of T)
            {
                One = One U {peg};
                next = !next;
            }
            */
            if (nRow - 1 == 0)
            {
                *nOne += nPeg;
                *nOneCnt += 1; // add 1 to the no. of elements in row 1 (T)
                *nNext = 1; 

                if ((*nOneCnt == 3) && (*nOne < 15))
                {
                    *isOver = 1;
                    *isLessThan = 1;
                }
            }

            /*
            if(nOk && pos is an element of M)
            {
                Two = Two U {peg};
                next = !next;
            }
            */
            else if (nRow - 1 == 1)
            {
                *nTwo += nPeg;
                *nTwoCnt += 1; // add 1 to the no. of elements in row 1 (T)
                *nNext = 1; 

                if ((*nTwoCnt == 3) && (*nTwo < 15))
                {
                    *isOver = 1;
                    *isLessThan = 1;
                }
            }

            /*
            if(nOk && pos is an element of B)
            {
            Three = Three U {peg};
            next = !next;
            }
            */
            else if (nRow - 1 == 2)
            {
                *nThree += nPeg;
                *nThreeCnt += 1; // add 1 to the no. of elements in row 1 (T)
                *nNext = 1; 

                if ((*nThreeCnt == 3) && (*nThree < 15))
                {
                    *isOver = 1;
                    *isLessThan = 1;
                }
            }

            if (*nNext == 1)
            {

                 /*
                if(nOk && next && pos is an element of L)
                {
                    Four = Four U {peg};
                    next = !next;
                    ok = !ok;
                }
                */
                if(nCol - 1 == 0)
                {
                    *nFour += nPeg;
                    *nFourCnt += 1;
                    *nNext = 0;
                    *nOk = 0;

                    if((*nFourCnt == 3) && (*nFour < 15))
                    {
                        *isOver = 1;
                        *isLessThan = 1;
                    }
                }

                /*
                if(nOk && next && pos is an element of C)
                {
                    Five = Five U {peg};
                    next = !next;
                    ok = !ok;
                }
                */
                else if(nCol - 1 == 1)
                {
                    *nFive += nPeg;
                    *nFiveCnt += 1;
                    *nNext = 0;
                    *nOk = 0;

                    if((*nFiveCnt == 3) && (*nFive < 15))
                    {
                        *isOver = 1;
                        *isLessThan = 1;
                    }
                }
                
                /*
                if(nOk && next && pos is an element of R)
                {
                    Six = Six U {peg};
                    next = !next;
                    ok = !ok;
                }
                */
                else if(nCol - 1 == 2)
                {
                    *nSix += nPeg;
                    *nSixCnt += 1;
                    *nNext = 0;
                    *nOk = 0;

                    if((*nSixCnt == 3) && (*nSix < 15))
                    {
                        *isOver = 1;
                        *isLessThan = 1;
                    }
                }
            }
        }
	}
    
    else if((nPeg >= 10) || (nPeg <= 0) || (nRow <= 0) || (nRow >= 4) || (nCol <= 0) || (nCol >= 4))
    {
        printf("\nInvalid inputs."); //'pag 'di nasatisfy yung required pegs, rows and cols, set to 1 yung isInvalid mamser
        *isInvalid = 1;
    }
    
    else if(nSpace[nRow - 1][nCol - 1] != 0){ 
        printf("\nOccupied cell!"); //'pag occ na yung space, set isInvalid to 1 din
        *isInvalid = 1;                        
    }

}

void
gameOver(int nTurn, int isLessThan, char cPlayers[])
{

    if((nTurn == 0) && (isLessThan == 1)) //if game ends when turn is 0 (Player B's turn) and less is 1 or true (Player B completed a row/column whose summation is < 15),
        printf("Player %c wins!\n", cPlayers[0]); //Player A wins
    
    else if((nTurn == 0) && (isLessThan == 0)) //if game ends when turn is 0 (Player B's turn) and less is 0 or false (Player B ended the game with all rows' and columns' = 15)
        printf("Player %c wins!\n", cPlayers[1]); //Player B wins.
    
    else if((nTurn == 1) && (isLessThan == 1)) //vice versa^
        printf("Player %c wins!\n", cPlayers[1]);
    
    else if((nTurn == 1) && (isLessThan == 0))
        printf("Player %c wins!\n", cPlayers[0]);
}

void
printBoard(int S[3][3])
{
    printf("    1       2       3\n");
    printf(" _______________________\n");
    printf("|       |       |       |\n");
    printf("|   %d   |   %d   |   %d   |    1\n", S[0][0], S[0][1], S[0][2]); // 1
    printf("|_______|_______|_______|\n");
    printf("|       |       |       |\n");
    printf("|   %d   |   %d   |   %d   |    2\n", S[1][0], S[1][1], S[1][2]); // 2
    printf("|_______|_______|_______|\n");
    printf("|       |       |       |\n");
    printf("|   %d   |   %d   |   %d   |    3\n", S[2][0], S[2][1], S[2][2]); // 3
    printf("|_______|_______|_______|\n");
}