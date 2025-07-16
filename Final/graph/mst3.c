#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
int parent[MAX_SIZE];


/* disjoint set */
int simpleFind(int i) {
    for( ; parent[i] >= 0; i = parent[i])
        ;
    return i;
}

void weightedUnion(int i, int j) {
    int temp = parent[i] + parent[j];
    if(parent[i] > parent[j]) {
        parent[i] = j;
        parent[j] = temp;
    } else {
        parent[j] = i;
        parent[i] = temp;
    }
}