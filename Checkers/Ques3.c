//
//  Ques3.c
//  FinalProj
//
//  Created by Hadar Israeli on 23/05/2019.
//  Copyright © 2019 Hadar Israeli. All rights reserved.
//

#include "Ques3.h"
//#include "Ques1.h"

MultipleSourceMovesList *findAllPossiblePlayerMoves(Board board, Player player){
    
    MultipleSourceMovesList *mulListToReturn = NULL;
    mulListToReturn=(MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
    checkMemoryAllocation(mulListToReturn);
    SingleSourceMoveList *curSingelList;
    SingelSourceMovesTree *tr;
    checkersPos curPos;
    makeEmptyMultipleSourceMovesList(mulListToReturn);
    
    int i,j;
    for(i=0; i<8; i++){
        
        for(j=i%2+1; j<8; j+=2){
            
            if(board[i][j] == player){
                curPos.col ='1'+j;
                curPos.row = 'A'+i;
                tr = FindSingelSourceMoves(board, &curPos);
                if(checkMove(tr->source)){
                    curSingelList = FindSingleSourceOptimalMove(tr);
                    insertDataToEndMultipleSourceMovesList(mulListToReturn, curSingelList);
                }
                freeTree(tr);
            }
        }
    }
    return mulListToReturn;
}

void insertDataToEndMultipleSourceMovesList(MultipleSourceMovesList *lst, SingleSourceMoveList *singelList){
    
    MultipleSourceMovesListCell *node=createNewMultipleSourceMovesListNode(singelList, NULL);
    insertNodeToTailMultipleSourceMovesListNode(lst, node);
    
}


void insertNodeToTailMultipleSourceMovesListNode(MultipleSourceMovesList *lst , MultipleSourceMovesListCell *tail){
    if(isEmptyMultipleSourceMovesList(lst)){
        lst->head = lst->tail = tail;
    }
    else{
        lst->tail->next = tail;
        lst->tail = tail;
    }
    
}
MultipleSourceMovesListCell *createNewMultipleSourceMovesListNode(SingleSourceMoveList *lst, MultipleSourceMovesListCell *next){
    MultipleSourceMovesListCell *node;
    node = (MultipleSourceMovesListCell *) malloc (sizeof(MultipleSourceMovesListCell));
    checkMemoryAllocation(node);
    node->single_source_moves_list = lst;
    node->next = next;
    
    return node;
}
BOOL isEmptyMultipleSourceMovesList(MultipleSourceMovesList *lst){
    
    if(lst->head == NULL)
        return TRUE;
    
    return FALSE;
    
}

void makeEmptyMultipleSourceMovesList(MultipleSourceMovesList *lst){
    lst->head = lst->tail = NULL;
}

BOOL checkMove(SingelSourceMovesTreeNode *tr){
    
    if(tr->next_move[LEFT] == NULL && tr->next_move[RIGHT] == NULL)
        return FALSE;
    return TRUE;
}
