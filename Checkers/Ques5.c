//
//  Ques5.c
//  FinalProj
//
//  Created by Hadar Israeli on 01/07/2019.
//  Copyright © 2019 Hadar Israeli. All rights reserved.
//

#include "Ques5.h"

//Ques5
void storeBoard(Board board, char *fileName){
    
    unsigned short buffer = 0x00;
    unsigned short bufT = 0x01;
    unsigned short bufB = 0x02;
    FILE *fp = fopen(fileName,"wb+");
    checkMemoryAllocation(fp);
    if(!fp)
        perror("fopen");
    
    for(int i=0;i<SIZE;i++){
        
        for(int j=SIZE-1;j>=0;j--){
            if(board[i][j] == 'T')
                buffer = buffer | (bufT<<((7-j)*2));
            if(board[i][j] == 'B')
                buffer = buffer | (bufB<<((7-j)*2));
        }
        
        fwrite(&buffer, sizeof(short), 1, fp);
        buffer = 0x00;
    }
    
    fclose(fp);
    
}

//Ques6
void loadBoard(char *fileName, Board board){
    int i=0,j=0;
    long int file1Size;
    
    FILE *fp=fopen(fileName,"rb");
    checkMemoryAllocation(fp);
    unsigned short line;
    unsigned short buffer = 0x00;
    file1Size = fileSize(fp);
    
    while(ftell(fp)<file1Size){
        fread(&line, sizeof(short), 1, fp);
            for(j=0; j<8; j++){
                buffer = line<<(j*2);
                buffer >>= 14;
                
                if(buffer == 0)
                    board[i][j] = ' ';
                else{
                    if(buffer == 1)
                        board[i][j] = 'T';
                    else
                        board[i][j] = 'B';
                }
            }
        i++;
        buffer = 0x00;
    }
    
    fclose(fp);
}

long int fileSize(FILE* file){
    
    long int res;
    
    fseek(file, 0, SEEK_END);
    res = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    return res;
}

