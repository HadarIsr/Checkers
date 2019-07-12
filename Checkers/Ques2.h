//
//  Ques2.h
//  FinalProj
//
//  Created by Hadar Israeli on 29/06/2019.
//  Copyright © 2019 Hadar Israeli. All rights reserved.
//

#ifndef Ques2_h
#define Ques2_h

#include "Ques1.h"
#include <time.h>


//Ques 2 structs
typedef struct _SingleSourceMovesListCell{
    checkersPos *position;
    unsigned short captures;
    struct _SingleSourceMovesListCell *next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMoveList{
    SingleSourceMovesListCell *head;
    SingleSourceMovesListCell *tail;
}SingleSourceMoveList;

//function
SingleSourceMoveList *FindSingleSourceOptimalMove(SingelSourceMovesTree *moves_tree);
void builedListrec(SingelSourceMovesTreeNode *trNode, int maxCaptures, int depth, int curDepth, int *flag, SingleSourceMoveList* lst);
SingleSourceMovesListCell *createNewListNode(checkersPos *position,unsigned short captures, SingleSourceMovesListCell *next);
int maxDepth(SingelSourceMovesTreeNode *node, int *maxCaptures);
void insertDataToHeadList(checkersPos *position,unsigned short captures,SingleSourceMoveList *lst);
void insertNodeToHeadList(SingleSourceMoveList *lst , SingleSourceMovesListCell *head);
BOOL isEmptyList(SingleSourceMoveList *lst);
void makeEmptyList(SingleSourceMoveList *lst);

#endif /* Ques2_h */
