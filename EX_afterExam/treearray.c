#include <stdio.h>
#define MAX_TREE 15

// make complete binary tree in Array

int depth(int i) {
    return i >> 1;
}
int parent(int i) {
    return i/2;
}
int lchild(int i) {
    return 2*i;
}
int rchild(int i){
    return 2*i + 1;
}
int main(void) 
{
    int arr[MAX_TREE + 1] = {-1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int i = 5;
    printf("depth: %d, parent: %d, lchild: %d, rchild: %d\n",depth(i),parent(arr[i]),lchild(arr[i]),rchild(arr[i]));
}