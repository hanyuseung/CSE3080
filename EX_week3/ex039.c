#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

struct node {
    element data;
    struct node *leftChild;
    struct node *rightChild;
};
typedef struct node* treePointer;

void inorder(treePointer ptr) {
    if(ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->data.key);
        inorder(ptr->rightChild);
    }
}

treePointer modifiedSearch(treePointer node, int k) {
    
    treePointer parent = NULL;
    while(node) {
        // if we found a node with key k, we return NULL
        if(k == node->data.key) return NULL;
        parent = node;
        if(k < node->data.key) node = node->leftChild;
        else node = node->rightChild;
    }
    return parent;
}

void insertNode(treePointer *node, int k) {
    treePointer ptr;
    treePointer temp = modifiedSearch(*node, k);
    if(temp || !(*node)) {
        // k is not in the tree
        ptr = (treePointer)malloc(sizeof(*ptr));
        ptr->data.key = k;
        ptr->leftChild = NULL;
        ptr->rightChild = NULL;
        if(*node) {
            if(k < temp->data.key) temp->leftChild = ptr;
            else temp->rightChild = ptr;
        }
        else *node = ptr;
        //printf("node with key %d inserted.\n", k);
    }
    else {
        printf("key %d is already in the tree.\n", k);
    }
}

void deleteNode(treePointer *node, int k) {
    /* complete this function! */
    
    if((*node) && (*node)->data.key > k){
        deleteNode(&((*node)->leftChild), k);
    } else if((*node) && (*node)->data.key < k){
        deleteNode(&((*node)->rightChild), k);
    }
    else{
        treePointer target = (*node);
        treePointer temp = target;
        if(!(*node)){
            printf("key %d is not in tree.\n",k);
            return;
        }
        else{
            if(!(target->leftChild) && !(target->rightChild)){ // 자식이 없다
                (*node) = NULL;
            } else if(target->leftChild && !(target->rightChild)){ //left만 있다.
                (*node) = target->leftChild;
            } else if(target->rightChild && !(target->leftChild)){ // right 만 있다
                (*node) = target->rightChild;
            } else{ 
                treePointer *succ = &target->leftChild;
                // 둘다 있으니 leftChild의 subtree의 최대값으로 대체해야한다.
                while((*succ)->rightChild){
                    succ = &(*succ)->rightChild;
                }
                temp = *succ;
                (*node)->data = (*succ)->data;
                (*succ) = (*succ)->leftChild;
            }
            free(temp);
        }
    }
}

void main() {

    treePointer tree = NULL;
    // insertNode(&tree, 30);
    // insertNode(&tree, 40);
    // insertNode(&tree, 20);
    // insertNode(&tree, 50);
    // insertNode(&tree, 10);
    // inorder(tree); printf("\n");

    treePointer tree2 = NULL;
    insertNode(&tree2, 30);
    insertNode(&tree2, 80);
    insertNode(&tree2,  5);
    insertNode(&tree2,  2);
    printf("Tree Before delete\n");
    inorder(tree2); printf("\n");

    // case 1 : invalid value
    printf("Case 1: If the node does not exist.\n");
    deleteNode(&tree2, -1);
    inorder(tree2); printf("\n\n");


    printf("Tree Before delete\n");
    inorder(tree2); printf("\n");
    //case 2 : delete 80
    printf("Case 2: If the node is a leaf node\n");
    deleteNode(&tree2, 80);
    inorder(tree2); printf("\n\n");


    insertNode(&tree2, 80);
    printf("Tree Before delete\n");
    inorder(tree2); printf("\n");
    
    // case3 : delete 5
    
    printf("Case 3: If the deleted node is a nonleaf node with a single child.\n");
    deleteNode(&tree2, 5);
    inorder(tree2); printf("\n\n");


    
    treePointer tree3 = NULL;
    insertNode(&tree3, 40);
    insertNode(&tree3, 60);
    insertNode(&tree3, 70);
    insertNode(&tree3, 50);
    insertNode(&tree3, 45);
    insertNode(&tree3, 55);
    insertNode(&tree3, 52);
    insertNode(&tree3, 20);
    insertNode(&tree3, 30);
    insertNode(&tree3, 10);
    
    printf("Tree Before delete\n");
    inorder(tree3); printf("\n");
    //case4: delete 60 in new tree.
    printf("Case 4: If the deleted node is a nonleaf node with two children.\n");
    deleteNode(&tree3, 60);
    inorder(tree3); printf("\n");


}
