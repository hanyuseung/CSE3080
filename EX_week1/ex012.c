//============================================================================//
// ex012: a faster transpose function for sparse representation of a matrix   //
//============================================================================//
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
#define MAX_COL 10

typedef struct {
  int row;
  int col;
  int value;
} term;

void printMatrix(term*);
void fast_transpose(term*, term*);

void main() {
  
  term a[MAX_TERMS], b[MAX_TERMS];
  
  a[0].row = 6; a[0].col = 6; a[0].value = 8;  // # of rows, # or cols, # of terms
  a[1].row = 0; a[1].col = 0; a[1].value = 15;
  a[2].row = 0; a[2].col = 3; a[2].value = 22;
  a[3].row = 0; a[3].col = 5; a[3].value = -15;
  a[4].row = 1; a[4].col = 1; a[4].value = 11;
  a[5].row = 1; a[5].col = 2; a[5].value = 3;
  a[6].row = 2; a[6].col = 3; a[6].value = -6;
  a[7].row = 4; a[7].col = 0; a[7].value = 91;
  a[8].row = 5; a[8].col = 2; a[8].value = 28;

  b[0].row = 0; b[0].col = 0; b[0].value = 0;

  printMatrix(a);
  fast_transpose(a, b);
  printMatrix(b);
}

void printMatrix(term *m) {

  int iter = 1, i, j;
  int rows = m[0].row;
  int cols = m[0].col;
  int num_terms = m[0].value;

  for(i=0; i<rows; i++) {
    for(j=0; j<cols; j++) {
      if(iter <= num_terms && m[iter].row == i && m[iter].col == j) {
        printf("%3d ", m[iter].value);
        iter++;
      } else {
        printf("%3d ", 0);
      }
    }
    printf("\n");
  } 
  printf("\n");
}

void fast_transpose(term *a, term *b) {

  // b is set to the transpose of a
  int row_terms[MAX_COL], starting_pos[MAX_COL];
  int i, j;
  int num_cols = a[0].col;
  int num_terms = a[0].value;

  b[0].row = num_cols;
  b[0].col = a[0].row;
  b[0].value = num_terms;

  if(num_terms > 0) {
    for(i=0; i<num_cols; i++) row_terms[i] = 0; // init
    for(i=1; i<=num_terms; i++) row_terms[a[i].col]++; // terms
    starting_pos[0] = 1;
    for(i=1; i<num_cols; i++) { // cols => O(terms + col) = O(row*col +col)
      starting_pos[i] = starting_pos[i-1] + row_terms[i-1];
    }
    for(i=1; i<=num_terms; i++) {
      // why ++? --> col 5에 대해 row가 1,2,3,4.. 뭐 이렇게 있을 꺼니까 ++하는거임 ㅇㅇ. 차피 a가 row major order니까 row order는 확정. ++star~~ 이면 j값 올라가니까 이건 안되고 
      j = starting_pos[a[i].col]++; 
      b[j].row = a[i].col;
      b[j].col = a[i].row;
      b[j].value = a[i].value;
    }
  }
}



