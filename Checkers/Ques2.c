//
//  Ques2.c
//  FinalProj
//
//  Created by Hadar Israeli on 29/06/2019.
//  Copyright © 2019 Hadar Israeli. All rights reserved.
//

#include "Ques2.h"

int maxDepth(SingelSourceMovesTreeNode *node, int *maxCaptures){
    if (node == NULL)
        return -1;
    else
    {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->next_move[LEFT], maxCaptures);
        int rDepth = maxDepth(node->next_move[RIGHT], maxCaptures);
        
        if(*maxCaptures < node->total_captures_so_far)
            *maxCaptures = node->total_captures_so_far;
        
        /* use the larger one */
        if (lDepth > rDepth){
            return(lDepth + 1);
        }
        
        return(rDepth + 1);
    }
}

BOOL isEmptyList(SingleSourceMoveList *lst){
    
    if(lst->head == NULL)
        return TRUE;
    
    return FALSE;
}

void makeEmptyList(SingleSourceMoveList *lst){
    lst->head = lst->tail = NULL;
}

SingleSourceMovesListCell *createNewListNode(checkersPos *position,unsigned short captures, SingleSourceMovesListCell *next){
    SingleSourceMovesListCell *node;
    node = (SingleSourceMovesListCell *)malloc(sizeof(SingleSourceMovesListCell));
    checkMemoryAllocation(node);
    node->position = (checkersPos*)malloc(sizeof(checkersPos));
    checkMemoryAllocation(node->position);
    node->captures = captures;
    node->position->col = position->col;
    node->position->row = position->row;
    node->next = next;
    return node;
}

void insertDataToHeadList(checkersPos *position,unsigned short captures,SingleSourceMoveList *lst){
    SingleSourceMovesListCell *head;
    head = createNewListNode(position,captures,NULL);
    insertNodeToHeadList(lst, head);
}

void insertNodeToHeadList(SingleSourceMoveList *lst , SingleSourceMovesListCell *head){
    if (isEmptyList(lst) == TRUE)
        lst->head = lst->tail = head;
    else{
        head->next = lst->head; // point the new node to the head list ls->head = new head;
        lst->head = head; // update the list's head
    }
}


SingleSourceMoveList *FindSingleSourceOptimalMove(SingelSourceMovesTree *moves_tree){
    
    SingleSourceMoveList *list;
    int flag=0;
    int maxCaptures=0;
    list=(SingleSourceMoveList*)malloc(sizeof(SingleSourceMoveList));
    checkMemoryAllocation(list);
    makeEmptyList(list);
    
    int depth = maxDepth(moves_tree->source, &maxCaptures);
        
    builedListrec(moves_tree->source, maxCaptures, depth, 0, &flag, list);
    return list;
    
}

void builedListrec(SingelSourceMovesTreeNode *trNode, int maxCaptures, int depth, int curDepth, int *flag, SingleSourceMoveList* lst){
    

    int random = (rand()%2);
    
    if(trNode == NULL)
        return;
    
    if(curDepth  == depth){
        if(trNode->total_captures_so_far == maxCaptures){
            insertDataToHeadList(trNode->pos, trNode->total_captures_so_far, lst);
            *flag = 1;
        }
        return;
    }
    
    if(*flag == 0)
        builedListrec(trNode->next_move[random], maxCaptures, depth, curDepth+1, flag, lst);
    if (*flag == 0)
        builedListrec(trNode->next_move[(random+1)%2], maxCaptures, depth, curDepth+1, flag, lst);
    if(*flag == 1)
        insertDataToHeadList(trNode->pos, trNode->total_captures_so_far, lst);
}


