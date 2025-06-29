#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 100
#define EXIT_ROW 50
#define EXIT_COL 50 

#define ROW 11
#define COL 15
#define MAX_ROW (ROW+2)
#define MAX_COL (COL+2)

typedef struct {
    short int vert;
    short int horiz;
} offsets;
offsets move[8];

typedef struct {
    short int row;
    short int col;
    short int dir;
}element;

element stack[MAX_STACK_SIZE];
int top = -1;

bool mark[MAX_ROW][MAX_COL];
int maze[MAX_ROW][MAX_COL] = 
{
    /*  0 */ {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    /*  1 */ {1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    /*  2 */ {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1},
    /*  3 */ {1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1},
    /*  4 */ {1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1},
    /*  5 */ {1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    /*  6 */ {1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1},
    /*  7 */ {1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    /*  8 */ {1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    /*  9 */ {1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
    /* 10 */ {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    /* 11 */ {1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    /* 12 */ {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void init (){
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            mark[i][j] = false;   
        }
    }
    
}

element stackEmpty(){
    element e;
    e.row = e.col = e.dir = -1;
    return e;
}
element stackFull(){
    fprintf(stderr, "no more space in the stack\n");
    exit(1);
}

element pop() {
     /* return the top element from the stack */
    if(top == -1)
        return stackEmpty(); /* error handler */
    return stack[top--];
}
element push(element item){
    /* add an item to the global stack */
    if(top >= MAX_STACK_SIZE - 1)
        stackFull(); /* error handler */
    stack[++top] = item;
}





/* output a path through the maze if such a path exists */
void path(void) {
    int i, row, col, nextRow, nextCol, dir;
    bool found = false;
    element position;
    // mark the start position as visited
    mark[1][1] = 1; 
    // push the start position and direction
    top = 0;
    stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1; 

    while(top > -1 && !found) {
        position = pop();
        row = position.row; col = position.col; dir = position.dir;
        while(dir < 8 && !found) {
            /* move in direction dir */
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if(nextRow == EXIT_ROW && nextCol == EXIT_COL)
                found = true;
            else if(!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
                mark[nextRow][nextCol] = 1;
                position.row = row; position.col = col;
                position.dir = ++dir;
                push(position);
                row = nextRow; col = nextCol; dir = 0;
                }
            else ++dir;
            }
        }
        if(found) {
            printf("The path is: \n");
            printf("row col\n");
            for(i = 0; i <= top; i++)
                printf("%2d%5d\n", stack[i].row, stack[i].col);
            printf("%2d%5d\n", row, col);
            printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
        }    
        else printf("The maze does not have a path.\n");
}


int main(void)
{
    
}