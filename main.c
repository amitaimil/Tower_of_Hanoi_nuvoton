/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: amitai
 *
 * Created on 27 באוקטובר 2020, 15:34
 */

#include <stdio.h>
#include <stdlib.h>

void hanoi(int ,char ,char ,char );

int main() {
    int discs;
    printf("How many discs? ");
    scanf("%d",&discs);
    hanoi(discs,'A','B','C');
    return 0;
}

void hanoi(int n,char A,char B,char C)
{
    if(n==0)
    {
        return;
    }
      hanoi(n-1,A,C,B);
       printf("Move disc %d from %c to %c\n",n,A,B);
        hanoi(n-1,C,B,A);
    
    
}
