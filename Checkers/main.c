//
//  main.c
//  FinalProj
//
//  Created by Hadar Israeli on 20/05/2019.
//  Copyright © 2019 Hadar Israeli. All rights reserved.
//




#include <stdio.h>
#include <stdlib.h>
#include "Ques7.h"
#include "Ques4.h"

void printTreeBoardRec(SingelSourceMovesTreeNode *tn);


void main() {
    srand(time(NULL));
    Board board ={
        {' ','T',' ', 'T' ,' ','T',' ','T'},
        {'T',' ','T',' ','T',' ','T',' '},
        {' ','T',' ','T',' ','T',' ','T'},
        {' ',' ',' ',' ',' ',' ',' ',' '} ,
        { ' ',' ',' ',' ',' ',' ',' ',' '} ,
        {'B',' ','B',' ','B',' ','B',' '},
        { ' ','B',' ','B',' ','B',' ','B'},
        {'B',' ','B',' ','B',' ','B',' '}
        };
    
//    Board board ={
//        {' ',' ',' ',' ',' ','T',' ',' '},
//        {' ',' ',' ',' ',' ',' ','B',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '}
//    };

    
    Board board1 ={
        {' ',' ',' ',' ',' ','T',' ',' '},
        {' ',' ',' ',' ','T',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ','T',' ','T',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ','T',' ',' ',' '},
        {' ',' ',' ',' ',' ','B',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '}
    };
    
    checkersPos pos;
    pos.col='6';
    pos.row='A';
    
    playGame(board, 'B');
//    SingelSourceMovesTree *tr;
//    tr.source=createNewSingelSourceMovesTreeNode(board, pos, 0, NULL, NULL);
//    printBoard(tr.source->board);
//    printBoard(board);
//    storeBoard(board, "LironHamfager");
//    loadBoard("LironHamfager", board1);
//    tr=FindSingelSourceMoves(board, &pos);
//    printTreeBoardRec(tr->source);
//    FindSingleSourceOptimalMove(tr);
//    printBoard(board1);
//
//    for(int i = 0; i<10;i++){
//        Turn(board, 'T');
//        Turn(board, 'B');
//
//    }
//
//
////    printBoard(tr->source->next_move[LEFT]->board);
    puts("exit");
}

void printTreeBoardRec(SingelSourceMovesTreeNode *tn){
    
    if(tn==NULL)
        return;
    
    printBoard(tn->board);
    printTreeBoardRec(tn->next_move[0]);
    printTreeBoardRec(tn->next_move[1]);
}
