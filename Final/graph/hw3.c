#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define HEAP_EMPTY(n) (!n)

typedef struct node {
    int vertex;
    int weight;
    struct node *link;
} *nodePointer;

typedef struct {
    int lend;
    int rend;
    int weight;
} edge;

/* number of vertices and edges of input graph */
int numVertices, numEdges;

/* min heap */
edge *heap;

/* min heap operations */
void insert(edge, int *);
edge delete(int *);

/* Prim's algorithm */
void Prim(nodePointer *, int);

/* free graph */
void freeGraph(nodePointer *);

void main(int argc, char *argv[]) {
    nodePointer *graph;
    int v;
    int lend, rend, weight;
    FILE *inputFile = fopen(argv[1], "r");

    fscanf(inputFile, "%d", &numVertices);
    fscanf(inputFile, "%d", &numEdges);

    /* allocate and initialize graph G, G={V,empty} */
    graph = (nodePointer *)malloc(numVertices * sizeof(nodePointer));
    for (v = 0; v < numVertices; v++)
        graph[v] = NULL;

    /* allocated array for min heap: max # of elements = 2 * num of edges + 1 */
    heap = (edge *)malloc((2*numEdges+1) * sizeof(edge));

    for (v = 0; v < numEdges; v++) {
        fscanf(inputFile, "%d %d %d", lend, rend, weight);
        int discardFlag = 0;
        /* add an edge to graph */
        for(nodePointer np = graph[lend]; np; np = np->link){
            if(np->vertex == rend) {
                discardFlag = 1;
                break;
            };
        }
        if(!discardFlag){
            nodePointer new_node = (nodePointer)malloc(sizeof(struct node));
            new_node->vertex = rend;
            new_node->weight = weight;
            new_node->link = graph[lend];
            graph[lend] = new_node;

            // nodePointer new_node2 = (nodePointer)malloc(sizeof(struct node));
            // new_node2->vertex = lend;
            // new_node2->weight = weight;
            // new_node2->link = graph[rend];
            // graph[rend] = new_node2;
        }
    }

    fclose(inputFile);

    Prim(graph, 0);

    freeGraph(graph);
    free(heap);
}

void Prim(nodePointer *G, int start) {
    int sum = 0;  /* sum of edge's weight in MST */
    int count = 0;  /* total count of edges in MST */
    int *visited;  /* visited flag array */
    FILE *outputFile = fopen("result.txt", "w");  

    int heap_size = 0;
    /* alloacated and initialize visited[] */
    visited = (int*) malloc(sizeof(int)*numVertices);
    for(int i = 0; i < numVertices; i++)
    {
        visited[i] = 0;
    }

    /* find and print safe edges */
    visited[start] = 1;
    while(!HEAP_EMPTY(heap) && count < numVertices-1)
    {
        edge tmp_edge;
        for(nodePointer data = G[start]; data; data = data->link)
        {
            tmp_edge.lend = 0; tmp_edge.rend = data->vertex ; tmp_edge.weight = data->vertex;
            insert(tmp_edge, &heap_size);
        }
        edge pop_edge = delete(&heap_size);
        if(!visited[pop_edge.rend]){
            visited[pop_edge.rend] = 1;
            count++; 
            sum += pop_edge.weight;
        }
    }
    
    fprintf(outputFile, "%d\n", sum);  /* sum of weight */
    if(count == numVertices-1)  /* a minimum spanning tree found */
        fprintf(outputFile, "CONNECTED\n");
    else 
        fprintf(outputFile, "DISCONNECTED\n");
    
    fclose(outputFile);
    free(visited);
}


void freeGraph(nodePointer *G)
{
    nodePointer del;
    for (int i = 0; i < numVertices; i++)
    {
        while(G[i])
        {
            del = G[i];
            G[i] = G[i]->link;
            free(del);
        }
    }
    free(G);
}


void insert(edge new, int *size)
{
    (*size)++;
}
edge delete(int *size)
{
    (*size)--;
}