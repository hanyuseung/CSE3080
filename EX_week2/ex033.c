#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
typedef enum {head, entry} tagfield;
struct entry_node {
  int row;
  int col;
  int value;
};
struct matrix_node {
  struct matrix_node *down;
  struct matrix_node *right;
  tagfield tag; // head element 구분 tag
  union {
    struct matrix_node *next; // head
    struct entry_node entry; // element
  } u;
};
typedef struct matrix_node *matrix_pointer;
matrix_pointer hdnode[MAX_SIZE];

matrix_pointer new_node();
matrix_pointer mread(); // input matrix 
void mwrite(matrix_pointer node); // print matrix
void merase(matrix_pointer *node); // Free matrix data

void main() {

  matrix_pointer m = mread();
  mwrite(m); 
  merase(&m);

}

matrix_pointer new_node() {
  matrix_pointer n = (matrix_pointer)malloc(sizeof(struct matrix_node));
  return n;
}

/* Head노드 - circular list 
 * row col 을 모두 포함한 1D 헤드노드.
 * row col 으로 down, right 링크 2개
 */

matrix_pointer mread() {
  
  int num_rows, num_cols, num_terms, num_heads, i;
  int row, col, value, current_row;
  matrix_pointer temp, last, node;

  printf("Enter the number of rows, columns and number of nonzero terms:\n");
  scanf("%d %d %d", &num_rows, &num_cols, &num_terms);

  num_heads = (num_cols > num_rows) ? num_cols : num_rows; // row, col중 더큰것만큼 헤더생성
  
  node = new_node(); 
  node->tag = entry; // Header of hdnode. element type으로 정보저장
  node->u.entry.row = num_rows;
  node->u.entry.col = num_cols;
  
  /* hdnode initialize*/
  // no term - h of h를 self linked로 circular 유지
  if(!num_heads) {node->right = node; return node;}
  // hdnode[] -> 헤더. right down있음 col, row가 분리되어있지 않음
  else { 
    for(i=0; i<num_heads; i++) { // O(MAX(col,row))
      temp = new_node();
      hdnode[i] = temp;
      hdnode[i]->tag = head;
      // Circular init - self reference
      hdnode[i]->right = temp;
      hdnode[i]->down = temp;
      hdnode[i]->u.next = temp;
    }
    current_row = 0; 
    last = hdnode[0];    // 처음 last는 당연히 head. element 가 없으니께

    /* Insert Matrix element */
    // 입력 규칙: lexicographically ordering 된 상태로 입력이 되어야함. 
    for(i=0; i<num_terms; i++) { // O(terms)
      printf("Enter row, column and value:\n");
      scanf("%d %d %d", &row, &col, &value);
      if(row > current_row) { // ordering
        last->right = hdnode[current_row]; // hdnode[row]- right 하면 해당 row의 element들을 확인가능
        current_row = row;
        last = hdnode[row];
      }
      /*새 노드 입력*/
      temp = new_node();
      temp->tag = entry;
      temp->u.entry.row = row;
      temp->u.entry.col = col;
      temp->u.entry.value = value;
      last->right = temp;
      last = temp; // last -- last row node 임
      
      // hdnode[col]- down 하면 해당 col의 element들을 확인가능
      // ** head를 linking하기 전에, hdnode[col]-> u.next를 last column node로 이용하고 있다. 코드 난독화냐 ㅅㅂ
      hdnode[col]->u.next->down = temp; 
      hdnode[col]->u.next = temp;
    }

    /* headnode들 이어주기 */
    // close last row
    last->right = hdnode[current_row];
    // close all column lists
    for(i=0; i<num_cols; i++)
      hdnode[i]->u.next->down = hdnode[i];
    // link all head nodes together
    for(i=0; i<num_heads-1; i++)
      hdnode[i]->u.next = hdnode[i+1];
    hdnode[num_heads-1]->u.next = node;
    node->right = hdnode[0];
  }
  return node;
}

/* Matrix 출력 */
void mwrite(matrix_pointer node) {
  int i;
  matrix_pointer temp;
  matrix_pointer head = node->right;

  printf("\nnumRows = %d, numCols = %d\n", node->u.entry.row, node->u.entry.col);
  printf("The matrix by row, column, and value:\n\n");
  for(i=0; i<node->u.entry.row; i++) {
    for(temp = head->right; temp != head; temp = temp->right)
      printf("%5d%5d%5d \n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
    head = head->u.next;
  }
}

/* Matrix 할당 해제 */
void merase(matrix_pointer *node) {
  int i, num_heads;
  matrix_pointer x, y, head = (*node)->right;

  for(i=0; i<(*node)->u.entry.row; i++) {
    y = head->right;
    /* element 날리기 */
    while(y != head) {
      x = y; y = y->right; free(x);
    }
    /* head 날리기 */
    x = head; head = head->u.next; free(x);
  }

  /* col 개수가 더 커서 헤더 남으면 그거 지움 */
  y = head;
  while(y != *node) {
    x = y; y = y->u.next; free(x);
  }
  free(*node); *node = NULL;
}
