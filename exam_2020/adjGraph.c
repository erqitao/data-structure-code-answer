#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NUM_VERTEX 20

/*********** global variables *************/
int maxDepth = 1;
int distance[MAX_NUM_VERTEX];
bool visited[MAX_NUM_VERTEX];
/*********** global variables *************/

typedef struct adjGraph {
	char vertices[MAX_NUM_VERTEX];
	bool edges[MAX_NUM_VERTEX][MAX_NUM_VERTEX];
	int numOfVertex, numOfEdge;
}adjGraph, *graph;

typedef struct seqQueue {
	int data[MAX_NUM_VERTEX];
	int front, rear;
}seqQueue, *queue;

queue initQueue() {
	queue q = malloc(sizeof(seqQueue));
	q->front = q->rear = 0;

	return q;
}

bool isQueueEmpty(queue q) {
	return q->front == q->rear;
}

bool isQueueFull(queue q) {
	return (q->rear + 1) % MAX_NUM_VERTEX == q->front;
}

bool enQueue(queue q, int v) {
	if (isQueueFull(q)) {
		puts("The queue is full. EnQueue failed.");
		return false;
	}

	q->data[q->rear] = v;
	q->rear = (q->rear + 1) % MAX_NUM_VERTEX;
	
	return true;
}

bool deQueue(queue q, int *v) {
	if (isQueueEmpty(q)) {
		puts("The queue is empty. DeQueue failed.");
		return false;
	}

	*v = q->data[q->front];
	q->front = (q->front + 1) % MAX_NUM_VERTEX;

	return true;
}

graph initGraph() {
	graph g = malloc(sizeof(adjGraph));
	g->numOfVertex = g->numOfEdge = 0;
	int i, j;
	for (i = 0; i < MAX_NUM_VERTEX; i++) {
		g->vertices[i] = '#';
	}

	for (i = 0; i < MAX_NUM_VERTEX; i++) {
		for (j  = 0; j < MAX_NUM_VERTEX; j++) {
			g->edges[i][j] = false;
		}
	}

	return g;
}

int getVertexIndex(graph g, char v) {
	int i;
	for (i = 0; i < g->numOfVertex; i++) {
		if (g->vertices[i] == v)
			return i;
	}

	return -1;
}

char getVertexValue(graph g, int i) {
	return g->vertices[i];
}

int firstNeighbor(graph g, int v) {
	int i;
	for (i = 0; i < g->numOfVertex; i++) {
		if (g->edges[v][i])
			return i;
	}

	return -1;
}

int nextNeighbor(graph g, int v, int w) {
	int i;
	for (i = w + 1; i < g->numOfVertex; i++) {
		if (g->edges[v][i])
			return i;
	}

	return -1;
}

void createGraph(graph g, char vertices[], int numOfVertex, char edges[][2], int numOfEdge) {
	g->numOfVertex = numOfVertex;
	g->numOfEdge = numOfEdge;

	int i, v1, v2;
	for (i = 0; i < numOfVertex; i++) {
		g->vertices[i] = vertices[i];
	}

	for (i = 0; i < numOfEdge; i++) {
		v1 = getVertexIndex(g, edges[i][0]);
		v2 = getVertexIndex(g, edges[i][1]);

		// undirected graph
		g->edges[v1][v2] = true;
		g->edges[v2][v1] = true;
	}
}

void printGraph(graph g) {
	printf("Number of vertices: %d\n", g->numOfVertex);
	printf("Number of edges: %d\n", g->numOfEdge);

	puts("Vertices:");
	int i, j;
	for (i = 0; i < g->numOfVertex; i++) {
		printf("%c\t", g->vertices[i]);
	}
	putchar('\n');
	
	puts("Edges:");
	for (i = 0; i < g->numOfVertex; i++) {
		for (j = i + 1; j < g->numOfVertex; j++) {
			if (g->edges[i][j]) {
				printf("(%c, %c)\t", getVertexValue(g, i), getVertexValue(g, j));
			}
		}
	}
	putchar('\n');
}

/**************** (START) core code (START) ******************/
void BFS(graph g, int w) {
	queue q = initQueue();
	printf("%c\t", getVertexValue(g, w));
	visited[w] = true;
	distance[w] = 1;
	enQueue(q, w);
	
	int i, v;
	while (!isQueueEmpty(q)) {
		deQueue(q, &v);
		for (i = firstNeighbor(g, v); i >= 0; i = nextNeighbor(g, v, i)) {
			if (!visited[i]) {
				printf("%c\t", getVertexValue(g, i));
				visited[i] = true;
				distance[i] = distance[v] + 1;
				
				if (distance[i] > maxDepth)
					maxDepth = distance[i];

				enQueue(q, i);
			}
		}
	}
}
/**************** (END) core code (END) ******************/

int main() {
	char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
	int numOfVertex = 9;
	char edges[][2] = {
						{'A', 'B'},
						{'A', 'C'},
						{'B', 'D'},
						{'B', 'E'},
						{'C', 'E'},
						{'C', 'F'},
						{'D', 'G'},
						{'E', 'H'},
						{'F', 'H'},
						{'G', 'H'},
						{'G', 'I'},
					};

	int numOfEdge = 11;

	graph g = initGraph();
	printGraph(g);
	createGraph(g, vertices, numOfVertex, edges, numOfEdge);
	printGraph(g);

	int i;
	for (i  = 0; i < g->numOfVertex; i++) {
		visited[i] = false;
		distance[i] = 0;
	}

	BFS(g, 0);
	printf("\n\n\nMax Depth: %d\n", maxDepth);

	printf("MAX Depth  - Vertices: ");
	for (i = 0; i < g->numOfVertex; i++) {
		if (distance[i] == maxDepth) {
			printf("%c\t", getVertexValue(g, i));
		}
	}

	return 0;
}
