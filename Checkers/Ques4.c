//
//  Ques4.c
//  FinalProj
//
//  Created by Hadar Israeli on 27/06/2019.
//  Copyright © 2019 Hadar Israeli. All rights reserved.
//

#include "Ques4.h"



void Turn(Board board,Player player){
    
    MultipleSourceMovesList *lst;
    lst=findAllPossiblePlayerMoves(board, player);
    int bestMove;
    MultipleSourceMovesListCell *mulCell=lst->head;
    SingleSourceMovesListCell *bestSingleCell = lst->head->single_source_moves_list->head;
    SingleSourceMovesListCell *bestSingleCellEnd = lst->head->single_source_moves_list->tail;
    SingleSourceMovesListCell *cur = lst->head->single_source_moves_list->tail;
    bestMove = cur->captures;
    
    while(cur != NULL){
        if(bestMove < cur->captures){
            bestMove = cur->captures;
            bestSingleCell = mulCell->single_source_moves_list->head;
            bestSingleCellEnd = cur;
        }
            
        mulCell = mulCell->next;
        if(mulCell == NULL)
            break;
        cur = mulCell->single_source_moves_list->tail;
    }
    printTurn(bestSingleCell, player);
    updateBoardForTurn(bestSingleCell, board, player);
//    printBoard(board);
    freeList(lst);
    puts("\n");
}

void checkPosition(SingleSourceMovesListCell *bestSingleCell, SingleSourceMovesListCell *bestSingleCellEnd, SingleSourceMovesListCell *cur, MultipleSourceMovesListCell *mulCell, Player player){
    
    int bestRow,curRow;
    bestRow = bestSingleCellEnd->position->row - 'A';
    curRow = cur->position->row - 'A';
    
    
    if(player == 'T'){
        if(curRow > bestRow){
            bestSingleCell=mulCell->single_source_moves_list->head;
            bestSingleCellEnd = cur;
        }
        return;
    }
    
    if(bestRow > curRow){
        bestSingleCell=mulCell->single_source_moves_list->head;
        bestSingleCellEnd = cur;
    }
    
}

void updateTheBoard(Board board, Player player, checkersPos curPos, checkersPos nextPos, checkersPos oppPos){
    
        updateBoard(board, curPos, ' ');//erase the player
        updateBoard(board, oppPos, ' ');//erase the opp player
        updateBoard(board, nextPos, player);//add the player to board
}

void calculateOppPos(checkersPos *curPos, checkersPos *nextPos, checkersPos *oppPos){
    
    oppPos->col = (curPos->col + nextPos->col)/2;
    oppPos->row = (curPos->row + nextPos->row)/2;
}


void updateBoardForTurn(SingleSourceMovesListCell *bestSingleCell, Board board, Player player){
    
    checkersPos *curPos, *nextPos, *oppPos;
    oppPos=(checkersPos*)malloc(sizeof(checkersPos));
    checkMemoryAllocation(oppPos);
    SingleSourceMovesListCell *curCell = bestSingleCell;
    
    while(curCell->next != NULL){
        curPos=curCell->position;
        nextPos=curCell->next->position;
        calculateOppPos(curPos, nextPos, oppPos);
        updateTheBoard(board, player, *curPos, *nextPos, *oppPos);
        curCell=curCell->next;
    }
}

void printTurn(SingleSourceMovesListCell *bestSingleCell, Player player){
    
    SingleSourceMovesListCell *temp = bestSingleCell;
    
    printf("%c%c",temp->position->row,temp->position->col);
    while(temp->next != NULL){
        printf("->%c%c",temp->next->position->row,temp->next->position->col);
        temp = temp->next;
    }
}

void freeList(MultipleSourceMovesList *lst){
    
    MultipleSourceMovesListCell *mulCell, *prevMulCell;
    SingleSourceMovesListCell *singleCell, *prevSingleCell;
    SingleSourceMoveList *singleLst;
    mulCell= lst->head;
    
    while(mulCell != NULL){
        singleLst=mulCell->single_source_moves_list;
        singleCell = singleLst->head;
        
        while(singleCell != NULL){
            free(singleCell->position);
            prevSingleCell=singleCell;
            singleCell=singleCell->next;
            free(prevSingleCell);
        }
        free(singleLst);
        prevMulCell=mulCell;
        mulCell=mulCell->next;
        free(prevMulCell);
        
    }
    
    free(lst);
}


void TurnEx(Board board,Player player){
    
    MultipleSourceMovesList *lst;
    lst=findAllPossiblePlayerMoves(board, player);
    int bestMove, counterBestMoves=0, random;
    MultipleSourceMovesListCell *mulCell=lst->head;
    SingleSourceMovesListCell **bestSingleCell ;
    SingleSourceMovesListCell *cur = lst->head->single_source_moves_list->tail;
    bestMove = cur->captures;
    
    while(cur != NULL){
        if(bestMove < cur->captures){
            counterBestMoves = 1;
            bestMove = cur->captures;
        }
        if(bestMove == cur->captures)
            counterBestMoves++;
        mulCell = mulCell->next;
        if(mulCell == NULL)
            break;
        
        cur = mulCell->single_source_moves_list->tail;
    }
    
    bestSingleCell=(SingleSourceMovesListCell **)malloc(sizeof(SingleSourceMovesListCell *)*counterBestMoves);
    cur=lst->head->single_source_moves_list->tail;
    mulCell=lst->head;
    for(int i=0;i<counterBestMoves; cur = mulCell->single_source_moves_list->tail){
        if(bestMove == cur->captures){
            bestSingleCell[i]=mulCell->single_source_moves_list->head;
            i++;
        }
        mulCell = mulCell->next;
        if(mulCell == NULL)
            break;
    }
    random=(rand()%counterBestMoves);
    printTurn(bestSingleCell[random], player);
    updateBoardForTurn(bestSingleCell[random], board, player);
    printBoard(board);
    freeList(lst);
    puts("\n");
}
