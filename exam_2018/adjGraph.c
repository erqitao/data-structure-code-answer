#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NUM_VERTEX 20
#define ERROR_VERTEX '#'

typedef struct adjGraph {
	char vertices[MAX_NUM_VERTEX];
	int edges[MAX_NUM_VERTEX][MAX_NUM_VERTEX];
	int numVertex, numEdge;
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

graph initGraph() {
	graph g = malloc(sizeof(adjGraph));
	int i, j;

	for (i = 0; i < MAX_NUM_VERTEX; i++) {
		for (j = 0; j < MAX_NUM_VERTEX; j++) {
			g->edges[i][j] = 0;
		}
	}
	g->numVertex = g->numEdge = 0;
	
	return g;
}

int getVertexIndex(graph g, char v) {
	int i, n = g->numVertex;
	for (i = 0; i < n; i++) {
		if (g->vertices[i] == v) {
			return i;
		}
	}

	return -1;
}

char getVertexValue(graph g, int i) {
	if (i == -1) {
		return ERROR_VERTEX;
	}
	return g->vertices[i];
}

int firstNeighbor(graph g, int v) {
	int i, n = g->numVertex;
	for (i = 0; i < n; i++) {
		if (g->edges[v][i] == 1) {
			return i;
		}
	}

	return -1;
}

int nextNeighbor(graph g, int v, int w) {
	int i, n = g->numVertex;

	for (i = w + 1; i < n; i++) {
		if (g->edges[v][i] == 1) {
			return i;
		}
	}

	return -1;
}

void createGraph(graph g, char vertices[], int numVertex, char edges[][2], int numEdge) {
	int i, v1, v2;
	g->numVertex = numVertex;
	g->numEdge = numEdge;

	for (i = 0; i < numVertex; i++) {
		g->vertices[i] = vertices[i];
	}

	for (i = 0; i < numEdge; i++) {
		v1 = getVertexIndex(g, edges[i][0]);
		v2 = getVertexIndex(g, edges[i][1]);

		g->edges[v1][v2] = 1;
		g->edges[v2][v1] = 1;
	}
}

void printGraph(graph g) {
	int i, j, n = g->numVertex;
	bool edgeExistsFlag;

	printf("Number of vertex: %d\n", g->numVertex);
	printf("Number of edge: %d\n", g->numEdge);

	for (i = 0; i < n; i++) {
		edgeExistsFlag = false;
		for (j = 0; j < n; j++) {
			if (g->edges[i][j] == 1) {
				printf("(%c, %c)\t", getVertexValue(g, i), getVertexValue(g, j));
				edgeExistsFlag = true;
			}
		}
		if (edgeExistsFlag) {
			putchar('\n');
		}
	}
}

void resetFlagArray(bool visited[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		visited[i] = false;
	}
}

void ordinaryDFS(graph g, int v, bool visited[]) {
	int i;

	visited[v] = true;
	printf("%c\t", getVertexValue(g, v));

	for (i = firstNeighbor(g, v); i >= 0; i = nextNeighbor(g, v, i)) {
		if (!visited[i]) {
			ordinaryDFS(g, i, visited);
		}
	}
}

void ordinaryBFS(graph g, int v, bool visited[]) {
	queue q = initQueue();
	int topVertex, w;

	visited[v] = true;
	printf("%c\t", getVertexValue(g, v));

	q->data[q->rear++] = v;
	while (q->front != q->rear) { // while the queue is not empty
		topVertex = q->data[q->front++]; // deQueue
		for (w = firstNeighbor(g, topVertex); w >= 0; w = nextNeighbor(g, topVertex, w)) {
			if (!visited[w]) {
				visited[w] = true;
				printf("%c\t", getVertexValue(g, w));
				q->data[q->rear++] = w; //enQueue
			}
		}
	}
}

//ReWrite the DFS function to test whether a graph is connected or not
void DFS(graph g, int v, bool visited[], int *numVisitedVertex) {
	visited[v] = true;
	printf("%c\t", getVertexValue(g, v));
	*numVisitedVertex += 1;

	int i;
	for (i = firstNeighbor(g, v); i >= 0; i = nextNeighbor(g, v, i)) {
		if (!visited[i]) {
			DFS(g, i, visited, numVisitedVertex);
		}
	}
}

bool isConnected(graph g, int startVertex, bool visited[]) {
	int numVisitedVertex = 0;
	DFS(g, startVertex, visited, &numVisitedVertex);
	
	return numVisitedVertex == g->numVertex;
}

int main() {
	/*
	char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	int numVertex = 7;

	char edges[][2] = {
			{'A', 'B'},
			{'A', 'C'},
			{'A', 'D'},
			{'B', 'E'},
			{'C', 'E'},
			{'D', 'E'},
			{'D', 'F'},
			{'D', 'G'}
		};
	int numEdge = 8;
	*/

	char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	int numVertex = 7;

	char edges[][2] = {
			{'A', 'B'},
			{'A', 'C'},
			{'A', 'D'},
			{'B', 'C'},
			{'B', 'E'},
			{'C', 'E'},
			{'D', 'E'},
			{'F', 'G'}
		};
	int numEdge = 8;


	
	bool visited[MAX_NUM_VERTEX];

	graph g = initGraph();
	createGraph(g, vertices, numVertex, edges, numEdge);
	printGraph(g);

	printf("\nDFS Traversal...\n");
	resetFlagArray(visited, MAX_NUM_VERTEX);
	ordinaryDFS(g, 0, visited);

	printf("\nBFS Traversal...\n");
	resetFlagArray(visited, MAX_NUM_VERTEX);
	ordinaryBFS(g, 0, visited);

	printf("\n\nTest Connectivity...\n\n");
	resetFlagArray(visited, MAX_NUM_VERTEX);
	bool conFlag = isConnected(g, 0, visited);

	if (conFlag) {
		printf("\nThis graph is connected.\n");
	} else {
		printf("\nThis graph is *not* connected.\n");
	}

	return 0;
}
