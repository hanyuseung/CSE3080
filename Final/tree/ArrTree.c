#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ARRAY_MAX 100

int size;

bool isEmpty(int *bt)
{
    if(!bt)
        return false;
    return true;
}

void binTreeCreate(int * arr)
{
    arr = (int*)malloc(sizeof(int)*(size+1));
}

bool insertLeft(int* bt, int parent, int data)
{
    if(parent*2 > size)
    {
        printf("Range Out!\n");
        return false;
    }
    bt[parent*2] = data;
    return true;
}
bool insertRight(int* bt, int parent, int data)
{
    if(parent*2 + 1 > size)
    {
        printf("Range Out!\n");
        return false;
    }
    bt[parent*2+1] = data;
    return true;
}

bool insert(int*bt, int parent, int lc, int rc, int data)
{
    bt[parent] = data;
    if(!insertLeft(bt, parent, lc))
        return false;
    if(!insertRight(bt, parent, rc))
        return false;
    return true;
    
}

int getParent(int* bt, int child)
{
    if(child <= 1){
        printf("Parent condition out\n");
        return -1;
    }
    return child/2;
}


int main(void)
{
    int*bt;
    size = 16;
    binTreeCreate(bt);
    insert(bt, 1, 2,3,1);   
}