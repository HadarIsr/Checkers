//
//  Ques1.c
//  FinalProj
//
//  Created by Hadar Israeli on 22/05/2019.
//  Copyright © 2019 Hadar Israeli. All rights reserved.
//

#include "Ques1.h"


SingelSourceMovesTreeNode* createNewSingelSourceMovesTreeNode(Board board,checkersPos pos,unsigned short total_captures_so_far,SingelSourceMovesTreeNode* leftNode, SingelSourceMovesTreeNode* rightNode){//create new node
    
    SingelSourceMovesTreeNode *res=(SingelSourceMovesTreeNode *)malloc(sizeof(SingelSourceMovesTreeNode));
    checkMemoryAllocation(res);
    
    copyBoard(res->board, board);
    
    res->pos=(checkersPos *)malloc(sizeof(checkersPos));
    checkMemoryAllocation(res->pos);
    *res->pos=pos;
    
    res->total_captures_so_far=total_captures_so_far;
    
    res->next_move[LEFT]=leftNode;
    res->next_move[RIGHT]=rightNode;
    
    return res;
}

void copyBoard (Board board,Board boardcopy){
    
    for(int i=0;i<BOARD_SIZE;i++)//set the board
        for(int j=0;j<BOARD_SIZE;j++)
            board[i][j]=boardcopy[i][j];
}

int boardInRange(checkersPos pos){//check the range
    
    if (pos.row <= 'H' && pos.row >= 'A')
        if (pos.col <= '8' &&pos.col >= '1')
            return 1;
    return 0;
}

void updateBoard(Board board, checkersPos Pos, Player player){
    
    int row,col;
    
    row=Pos.row-'A';
    col=Pos.col-'1';
    
    board[row][col]=player;
}


checkersPos advancedCheckerPos(char player, int side, checkersPos pos){
    
    checkersPos newPos;
    
    if(player == 'T'){
        if(side == LEFT){
            newPos.col = pos.col-1;
            newPos.row = pos.row+1;
            return newPos;
        }
        newPos.col = pos.col+1;
        newPos.row = pos.row+1;
        return newPos;
    }
    
    if(side == LEFT){
        newPos.col = pos.col-1;
        newPos.row = pos.row -1;
        return newPos;
    }
    
    newPos.col = pos.col+1;
    newPos.row = pos.row-1;
    return newPos;
    
}

BOOL canEat(Board board, char player, checkersPos pos, int side){
    
    checkersPos newPos;
    int row, col;
    
    newPos = advancedCheckerPos(player, side, pos);
    row = newPos.row - 'A';
    col = newPos.col - '1';
    
    if (!boardInRange(newPos))
        return FALSE;
    if(board[row][col] != ' ')
        return FALSE;
    
    return TRUE;
    
    
}

SingelSourceMovesTree *FindSingelSourceMoves(Board board,checkersPos *src){
    
    SingelSourceMovesTree *tr = NULL;
    int row,col;
    checkersPos newPosLeft, newPosRight;
    Player player;
    
    row = src->row-'A';
    col = src->col-'1';
    player = board[row][col];
    
    if (player == ' ')
        return tr;
    
    tr=(SingelSourceMovesTree*)malloc(sizeof(SingelSourceMovesTree));
    checkMemoryAllocation(tr);
    tr->source=createNewSingelSourceMovesTreeNode(board, *src, 0, NULL, NULL);
    tr->source->board[row][col] = ' ';
    
    if (player == 'T'){//we have 'T' player there
        newPosLeft=advancedCheckerPos('T', LEFT, *src);
        newPosRight=advancedCheckerPos('T', RIGHT, *src);
        tr->source->next_move[LEFT]=FindSingelSourceMovesLeftRec(tr->source->board, newPosLeft, 'T', 0);
        tr->source->next_move[RIGHT]=FindSingelSourceMovesRightRec(tr->source->board, newPosRight, 'T', 0);
    }
    if (player == 'B'){//we have 'B' player there
        newPosLeft=advancedCheckerPos('B', LEFT, *src);
        newPosRight=advancedCheckerPos('B', RIGHT, *src);
        tr->source->next_move[LEFT]=FindSingelSourceMovesLeftRec(tr->source->board, newPosLeft, 'B', 0);
        tr->source->next_move[RIGHT]=FindSingelSourceMovesRightRec(tr->source->board, newPosRight, 'B', 0);
    }
    
    tr->source->board[row][col] = player;
    return tr;
}

SingelSourceMovesTreeNode* FindSingelSourceMovesRightRec(Board board,checkersPos src,Player player, short counterEats){
    
    SingelSourceMovesTreeNode *resNode;
    int row,col;
    checkersPos rightPos, leftPos, newPos;
    row = src.row-'A';
    col = src.col-'1';
    
    if(!boardInRange(src))
        return NULL;
    
    if(board[row][col] == player)
        return NULL;
    
    if(board[row][col] == ' '){
        if(counterEats == 0){
            resNode=createNewSingelSourceMovesTreeNode(board, src, 0, NULL, NULL);
            updateBoard(resNode->board, src, player);
            return resNode;
        }
        return NULL;
    }
    
    if(canEat(board, player, src, RIGHT)){
        newPos=advancedCheckerPos(player, RIGHT, src);
        resNode=createNewSingelSourceMovesTreeNode(board, newPos, counterEats+1, NULL, NULL);
        erasePlayer(resNode->board, src, player, RIGHT);
        updateBoard(resNode->board, newPos, player);
        rightPos=advancedCheckerPos(player, RIGHT, newPos);
        resNode->next_move[RIGHT]=FindSingelSourceMovesRightRec(resNode->board, rightPos, player, counterEats+1);
        leftPos=advancedCheckerPos(player, LEFT, newPos);
        resNode->next_move[LEFT]=FindSingelSourceMovesLeftRec(resNode->board, leftPos, player, counterEats+1);
        return resNode;
    }
    
    return NULL;
}

SingelSourceMovesTreeNode* FindSingelSourceMovesLeftRec(Board board,checkersPos src,Player player, short counterEats){
    
    SingelSourceMovesTreeNode *resNode;
    int row,col;
    checkersPos rightPos, leftPos, newPos;
    
    row = src.row-'A';
    col = src.col-'1';
    
    if(!boardInRange(src))
        return NULL;
    
    if(board[row][col] == player)
        return NULL;
    
    if(board[row][col] == ' '){
        if(counterEats == 0){
            resNode=createNewSingelSourceMovesTreeNode(board, src, 0, NULL, NULL);
            updateBoard(resNode->board, src, player);
            return resNode;
        }
        return NULL;
    }
    
    if(canEat(board, player, src, LEFT)){
        newPos=advancedCheckerPos(player, LEFT, src);
        resNode=createNewSingelSourceMovesTreeNode(board, newPos, counterEats+1, NULL, NULL);
        erasePlayer(resNode->board, src, player, LEFT);
        updateBoard(resNode->board, newPos, player);
        rightPos=advancedCheckerPos(player, RIGHT, newPos);
        resNode->next_move[RIGHT]=FindSingelSourceMovesRightRec(resNode->board, rightPos, player, counterEats+1);
        leftPos=advancedCheckerPos(player, LEFT, newPos);
        resNode->next_move[LEFT]=FindSingelSourceMovesLeftRec(resNode->board, leftPos, player, counterEats+1);
        return resNode;
    }
    
    return NULL;
}

void erasePlayer(Board board,checkersPos oppPlayer, Player player, int side){
    
    int row, col;
    row = oppPlayer.row-'A';
    col = oppPlayer.col-'1';
    board[row][col]=' ';
    
    if(player == 'T'){
        if(side == LEFT)
            oppPlayer=advancedCheckerPos('B', RIGHT, oppPlayer);
        else
            oppPlayer=advancedCheckerPos('B', LEFT, oppPlayer);
    }
    else{
        if(side == LEFT)
            oppPlayer=advancedCheckerPos('T', RIGHT, oppPlayer);
        else
            oppPlayer=advancedCheckerPos('T', LEFT, oppPlayer);
    }
    
    row = oppPlayer.row-'A';
    col = oppPlayer.col-'1';
    board[row][col]=' ';
}

void printBoard(Board board){
    
    char ch = 'A'-1;
    puts(" 1 2 3 4 5 6 7 8");
    for(int i=0;i<BOARD_SIZE;i++){//set the board
        for(int j=0;j<BOARD_SIZE;j++)
            printf("|%c",board[i][j]);
        ch++;
        printf("| %c\n_________________\n",ch);
    }
    printf("\n");
}

void freeTree(SingelSourceMovesTree *tree){
    
    freeTreeRec(tree->source);
    free(tree);
}

void freeTreeRec(SingelSourceMovesTreeNode *tn){
    
    if(tn == NULL)
        return;
    freeTreeRec(tn->next_move[LEFT]);
    freeTreeRec(tn->next_move[RIGHT]);
    free(tn->pos);
    free(tn);
}

void checkMemoryAllocation(void *ptr){
    
    if (ptr == NULL){
        puts("Memory allocation error");
        exit(1);
    }
}
