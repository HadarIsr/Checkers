//
//  Ques1.h
//  FinalProj
//
//  Created by Hadar Israeli on 22/05/2019.
//  Copyright © 2019 Hadar Israeli. All rights reserved.
//

#ifndef Ques1_h
#define Ques1_h



#include <stdio.h>
#include <stdlib.h>


#define BOARD_SIZE 8
#define LEFT 0
#define RIGHT 1

#define TRUE 1
#define FALSE 0

#define SIZE 8

typedef int BOOL;
/* false 0
 true 1 */

typedef struct _checkerPos{//ייצוג משבצת
    char row ,col;
}checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];//ייצוג לוח

typedef unsigned char Player;//ייצוג שחקן

typedef struct _SingelSourceMovesTreeNode{
    Board board;
    checkersPos *pos;
    unsigned short total_captures_so_far;//דילוגים עד כה
    struct _SingelSourceMovesTreeNode *next_move[2];// יעדי התנועה
}SingelSourceMovesTreeNode;
 
typedef struct _SingelSourceMovesTree{
    SingelSourceMovesTreeNode *source;
}SingelSourceMovesTree;


// function declere
void checkMemoryAllocation(void *ptr);
SingelSourceMovesTreeNode* createNewSingelSourceMovesTreeNode(Board board,checkersPos pos,unsigned short total_captures_so_far,SingelSourceMovesTreeNode* leftNode, SingelSourceMovesTreeNode* rightNode);
void copyBoard (Board board,Board boardcopy);
void updateBoard(Board board, checkersPos Pos, Player player);
int boardInRange(checkersPos pos);
checkersPos advancedCheckerPos(char player, int side, checkersPos pos);
int canEat(Board board, char player, checkersPos pos, int side);
//int checkFirstTime(Board board, checkersPos pos, Player player);
void erasePlayer(Board board,checkersPos oppPlayer, Player player, int side);
void printBoard(Board board);
void freeTree(SingelSourceMovesTree *tree);
void freeTreeRec(SingelSourceMovesTreeNode *tn);

//QuesA
SingelSourceMovesTree *FindSingelSourceMoves(Board board,checkersPos *src);
SingelSourceMovesTreeNode* FindSingelSourceMovesRightRec(Board board,checkersPos currentPos,Player player, short counterEats);
SingelSourceMovesTreeNode* FindSingelSourceMovesLeftRec(Board board,checkersPos currentPos,Player player, short counterEats);

#endif /* Ques1_h */
