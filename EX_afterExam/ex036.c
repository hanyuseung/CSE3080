#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100


/* 과제 요구사항을 잘 지킬것 
+ 여러가지 tree 형태에 대해 시험하되, 그것에 제출할때는 삭제.
 */

struct node {
  char data;
  struct node *left_child, *right_child;
};
typedef struct node *tree_pointer;

tree_pointer stack[MAX_STACK_SIZE];
tree_pointer queue[MAX_QUEUE_SIZE];

tree_pointer create_tree_node(char data);
void recursive_inorder(tree_pointer ptr);
void iter_inorder(tree_pointer ptr);
void iter_postorder(tree_pointer ptr);
void iter_preorder(tree_pointer ptr);
void level_order(tree_pointer ptr);

/* TODO: add function prototype if necessary */
void add(int *top, tree_pointer ptr);
tree_pointer delete(int *top);
void addq(int *rear, tree_pointer ptr, int *size);
tree_pointer deleteq(int *front, int *size);

/* TODO: stack, queue function */
void add(int *top, tree_pointer ptr){
  if((*top) == MAX_STACK_SIZE-1){
    printf("STACK FULL!\n");
    exit (1);
  }
  // Stack에 뭐집어넣야됨? - ptr.
  stack[++(*top)] = ptr;
}

tree_pointer delete(int *top){
  if((*top) == -1){
    //printf("STACK EMPTY!\n");
    return NULL;
  }
  tree_pointer rv = stack[(*top)--];
  return rv;
}

void addq(int *rear, tree_pointer ptr, int *size) {
  /* add an item to the queue */
  if((*size) == MAX_QUEUE_SIZE) {
    printf("QUEUE FULL!\n");
    exit (1);
  }
  (*rear) = ((*rear) + 1) % MAX_QUEUE_SIZE;
  queue[(*rear)] = ptr;
  (*size)++;
}

tree_pointer deleteq(int *front, int *size){
  if((*size) == 0){
    //printf("QUEUE EMPTY!\n");
    return NULL;
  }
  (*front) = ((*front) + 1) % MAX_QUEUE_SIZE;
  (*size)--;
  return queue[(*front)];
}



void main() {
  // Same tree in Lec 27p
  /* create a tree that represents an arithmetic expression */
  tree_pointer ptr, ptr1, ptr2;

  ptr1 = create_tree_node('A');
  ptr2 = create_tree_node('B');
  ptr = create_tree_node('/');
  ptr->left_child = ptr1;
  ptr->right_child = ptr2;

  ptr1 = ptr;
  ptr2 = create_tree_node('C');
  ptr = create_tree_node('*');
  ptr->left_child = ptr1;
  ptr->right_child = ptr2;

  ptr1 = ptr;
  ptr2 = create_tree_node('D');
  ptr = create_tree_node('*');
  ptr->left_child = ptr1;
  ptr->right_child = ptr2;

  ptr1 = ptr;
  ptr2 = create_tree_node('E');
  ptr = create_tree_node('+');
  ptr->left_child = ptr1;
  ptr->right_child = ptr2;

  /* call traversal functions */
  recursive_inorder(ptr);
  printf("\n");
  iter_inorder(ptr);
  printf("\n");
  iter_preorder(ptr);
  printf("\n");
  iter_postorder(ptr);
  printf("\n");
  level_order(ptr);
  printf("\n");
}
  
tree_pointer create_tree_node(char data) {
  tree_pointer ptr = (tree_pointer)malloc(sizeof(struct node));
  ptr->data = data;
  ptr->left_child = NULL;
  ptr->right_child = NULL;
  return ptr;
}

void recursive_inorder(tree_pointer ptr) {
  if(ptr) {
    recursive_inorder(ptr->left_child);
    printf("%c ", ptr->data);
    recursive_inorder(ptr->right_child);
  }
}

// lvr - infix
void iter_inorder(tree_pointer ptr) {
  int top = -1;  /* initialize stack */
  for(;;) {
    for(; ptr; ptr = ptr->left_child) // left child를 먼저 넣기
        add(&top, ptr);  /* add to stack */
      ptr = delete (&top);  /* delete from stack - print value*/
      if(!ptr) break;  /* empty stack */
      printf("%c ", ptr->data);
      ptr = ptr->right_child; // right child 넣기
  }
}

// vlr - prefix
void iter_preorder(tree_pointer ptr) {
  /* TODO: you must complete this function */
  int top = -1;
  add(&top, ptr);
  if(!ptr)return;
  while(top>=0){
    ptr = delete(&top);
    printf("%c ", ptr->data); // check value first.
    if(ptr->right_child) add(&top, ptr->right_child);
    if(ptr->left_child) add(&top, ptr->left_child); // stack is FIFO, so add left in last. 
  }
}
// lrv - postfix
void iter_postorder(tree_pointer ptr) {
  /* TODO: you must complete this function */
  int top = -1;
  tree_pointer curr = ptr; // current node.
  tree_pointer last = NULL; // check visited
  while(top>=0 || curr != NULL){
    if(curr){
      add(&top, curr); // l,r
      curr= curr->left_child;
    }
    else{
      if(stack[top]->right_child && (last != stack[top]->right_child)){
        curr = stack[top]->right_child; // shift to right if it dont check right_child yet.
      }
      else{
        last = delete(&top); // l,r done, so pop value in stack.
        printf("%c ", last->data);
      }
    }
  }
}

// Code from Lecture note p33.
void level_order(tree_pointer ptr) {
  /* TODO: you must complete this function */
  int front = 0, rear = 0, size = 0;  /* initialize queue */
  if(!ptr) return; /* empty tree */
  addq(&rear, ptr, &size);  /* add to queue */
  for(;;) {
    ptr = deleteq(&front, &size);  /* delete from queue */
    if(ptr) {
      printf("%c ", ptr->data);
      if(ptr->left_child) addq(&rear, ptr->left_child, &size);
      if(ptr->right_child) addq(&rear, ptr->right_child, &size);
    }
    else break;  /* empty queue */
  }
}

/* TODO: add function implementations here */
