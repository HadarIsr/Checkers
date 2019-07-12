//
//  Ques7.c
//  FinalProj
//
//  Created by Hadar Israeli on 03/07/2019.
//  Copyright © 2019 Hadar Israeli. All rights reserved.
//

#include "Ques7.h"

void playGame(Board board, Player startingPlayer){
    
    int statusGame = isGameOver(board);
    int player;
    printBoard(board);
    
    if(startingPlayer == 'T')
        player = 1;
    else
        player = 0;
    
    while(statusGame == 0){
        
        if(player == 1){
            puts("player TOP_DOWN'S turn");
            Turn(board, 'T');
            player = 0;
        }
        else{
            puts("player BOTTOM_UP'S turn");
            Turn(board, 'B');
            player = 1;
        }
        
        statusGame = isGameOver(board);
    }
    
    if (statusGame == 1)
        puts("player BOTTOM_UP'S win\n");
    else
        puts("player TOP_DOWN'S win\n");
    
}

int isGameOver(Board board){
    
    int bWin=1,tWin=2,tie=0;
    int tCoun=0, bCount=0;
    
    for(int i=0;i<SIZE;i++){
        for(int j=i%2+1; j<SIZE ;j+=2){
            if(i == 0){
                if(board[i][j] == 'B')
                    return bWin;
            }
            if(i == 7){
                if(board[i][j] == 'T')
                    return tWin;
            }
            if(board[i][j] == 'T')
                tCoun++;
            if(board[i][j] == 'B')
                bCount++;
        }
    }
    if(bCount == 0)
        return tWin;
    if(tCoun == 0)
        return bWin;
    return tie;
    
}
