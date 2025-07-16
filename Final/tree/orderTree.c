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
void recursive_preorder(tree_pointer ptr);
void recursive_postorder(tree_pointer ptr);
void iter_inorder(tree_pointer ptr);
void iter_postorder(tree_pointer ptr);
void iter_preorder(tree_pointer ptr);
void level_order(tree_pointer ptr);

/* TODO: add function prototype if necessary */

/* if stack full, output error and exit */
void add(int *top, tree_pointer ptr);

/* if stack empty, return NULL */
tree_pointer delete(int *top);

/* if queue full, output error and exit */
void addq(int *rear, tree_pointer ptr, int *size);

/* if queue empty, return NULL */
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


// Test code for balanced polynomial tree
void test(){
  tree_pointer a,b,c,d,mul,sub,plus,root;
  a = create_tree_node('A');
  b = create_tree_node('B');
  c = create_tree_node('C');
  d = create_tree_node('D');
  mul = create_tree_node('*');
  sub = create_tree_node('-');
  root = create_tree_node('+');

  mul->left_child = a; mul->right_child = b;
  sub->left_child = c; sub->right_child = d;

  root->left_child = mul; root->right_child = sub;
  printf("Balanced polynomial tree\n");
  recursive_inorder(root); printf("\n");
  iter_inorder(root); printf("\n");
  iter_preorder(root); printf("\n");
  iter_postorder(root); printf("\n");
  level_order(root); printf("\n");
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

  //test();
}
  
tree_pointer create_tree_node(char data) {
  tree_pointer ptr = (tree_pointer)malloc(sizeof(struct node));
  ptr->data = data;
  ptr->left_child = NULL;
  ptr->right_child = NULL;
  return ptr;
}

void recursive_inorder(tree_pointer ptr) {
  if(!ptr) return;
  recursive_inorder(ptr->left_child);
  printf("%d",ptr->data);
  recursive_inorder(ptr->right_child);
}

void recursive_preorder(tree_pointer ptr ) {
    if(!ptr) return;
    printf("%d", ptr->data);
    recursive_preorder(ptr->left_child);
    recursive_preorder(ptr->right_child);
}

void recursive_postorder(tree_pointer ptr){
    if(!ptr) return;
    recursive_postorder(ptr->left_child);
    recursive_postorder(ptr->right_child);
    printf("%d", ptr->data);
}

// lvr - infix
void iter_inorder(tree_pointer ptr) {
  int top = -1;
}

// vlr - prefix
void iter_preorder(tree_pointer ptr) {
  /* TODO: you must complete this function */
  
}

// lrv - postfix
void iter_postorder(tree_pointer ptr) {
  /* TODO: you must complete this function */
  
}

// Code from Lecture note p33.
void level_order(tree_pointer ptr) {
  /* TODO: you must complete this function */
  
}

/* TODO: add function implementations here */
