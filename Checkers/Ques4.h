//
//  Ques4.h
//  FinalProj
//
//  Created by Hadar Israeli on 27/06/2019.
//  Copyright © 2019 Hadar Israeli. All rights reserved.
//

#ifndef Ques4_h
#define Ques4_h

#include "Ques3.h"

void Turn(Board board,Player player);
void updateBoardForTurn(SingleSourceMovesListCell *bestSingleCell, Board board, Player player);
void updateTheBoard(Board board, Player player, checkersPos curPos, checkersPos nextPos, checkersPos oppPos);
void calculateOppPos(checkersPos *curPos, checkersPos *nextPos, checkersPos *oppPos);
void freeList(MultipleSourceMovesList *lst);
void checkPosition(SingleSourceMovesListCell *bestSingleCell, SingleSourceMovesListCell *bestSingleCellEnd, SingleSourceMovesListCell *cur, MultipleSourceMovesListCell *mulCell, Player player);
void printTurn(SingleSourceMovesListCell *bestSingleCell, Player player);

void TurnEx(Board board,Player player);
#endif /* Ques4_h */
