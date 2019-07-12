//
//  Ques3.h
//  FinalProj
//
//  Created by Hadar Israeli on 23/05/2019.
//  Copyright © 2019 Hadar Israeli. All rights reserved.
//

#ifndef Ques3_h
#define Ques3_h
#include "Ques2.h"

//Ques 3 Structs
typedef struct _multipleSourceMovesListCell{
    SingleSourceMoveList *single_source_moves_list;
    struct _multipleSourceMovesListCell *next;
}MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList{
    MultipleSourceMovesListCell *head;
    MultipleSourceMovesListCell *tail;
}MultipleSourceMovesList;


//Ques 3 function
MultipleSourceMovesList *findAllPossiblePlayerMoves(Board board, Player player);
void insertDataToEndMultipleSourceMovesList(MultipleSourceMovesList *lst, SingleSourceMoveList *singelList);
void insertNodeToTailMultipleSourceMovesListNode(MultipleSourceMovesList *lst , MultipleSourceMovesListCell *tail);
MultipleSourceMovesListCell *createNewMultipleSourceMovesListNode(SingleSourceMoveList *lst, MultipleSourceMovesListCell *next);
BOOL isEmptyMultipleSourceMovesList(MultipleSourceMovesList *lst);
void makeEmptyMultipleSourceMovesList(MultipleSourceMovesList *lst);
BOOL checkMove(SingelSourceMovesTreeNode *tr);


#endif /* Ques3_h */
