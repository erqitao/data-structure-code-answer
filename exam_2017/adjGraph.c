#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NUM_VERTEX 20

typedef struct adjGraph {
	char vertices[MAX_NUM_VERTEX];
	char edges[MAX_NUM_VERTEX][MAX_NUM_VERTEX];
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
	g->numVertex = g->numEdge = 0;
	int i, j;
	for (i = 0; i < MAX_NUM_VERTEX; i++) {
		for (j = 0; j < MAX_NUM_VERTEX; j++) {
			g->edges[i][j] = 0;
		}
	}

	return g;
}

int getVertexIndex(graph g, char val) {
	int i;
	for (i = 0; i < g->numVertex; i++) {
		if (g->vertices[i] == val)
			return i;
	}
	return -1;
}

int getVertexValue(graph g, int index) {
	return g->vertices[index];
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
	g->numVertex = numVertex;
	g->numEdge = numEdge;
	int i, v1, v2;

	for (i = 0; i < numVertex; i++) {
		g->vertices[i] = vertices[i];
	}

	for (i = 0; i < numEdge; i++) {
		v1 = getVertexIndex(g, edges[i][0]);
		v2 = getVertexIndex(g, edges[i][1]);
		g->edges[v1][v2] = 1;
		g->edges[v2][v1] = 1; // undirected graph
	}
}

void printGraph(graph g) {
	int i, j, numVertex = g->numVertex;

	printf("Number of vertex: %d\n", g->numVertex);
	printf("Number of edge: %d\n", g->numEdge);

	for (i = 0; i < numVertex; i++) {
		for (j = 0; j < numVertex; j++) {
			if (g->edges[i][j] == 1) {
				printf("(%c, %c)\t", getVertexValue(g, i), getVertexValue(g, j));
			}
		}
		putchar('\n');
	}
}

void DFS(graph g, int v, bool visited[]) {
	printf("%c\t", getVertexValue(g, v));
	visited[v] = true;

	int i;
	for (i = firstNeighbor(g, v); i != -1; i = nextNeighbor(g, v, i)) {
		if (!visited[i]) {
			DFS(g, i, visited);
		}
	}
}

void BFS(graph g, int v, bool visited[]) {
	queue q = initQueue();
	int i, w;

	visited[v] = true;
	printf("%c\t", getVertexValue(g, v));

	q->data[q->rear] = v;
	q->rear += 1;

	while (q->front != q->rear) {
		w = q->data[q->front];
		q->front += 1;

		for (i = firstNeighbor(g, w); i != -1; i = nextNeighbor(g, w, i)) {
			if (!visited[i]) {
				visited[i] = true;
				printf("%c\t", getVertexValue(g, i));
				q->data[q->rear] = i;
				q->rear += 1;
			}
		}
	}
}

/************************ (START) core code (START) ***********************************/
void ifExistPath(graph g, int v, int w, bool visited[], bool *existFlag) {
	visited[v] = true;
	printf("%c\t", getVertexValue(g, v));

	if (v == w) {
		*existFlag = true;
		return;
	}

	int i;
	for (i = firstNeighbor(g, v); i != -1; i = nextNeighbor(g, v, i)) {
		if (*existFlag == true)
			return;

		if (!visited[i]) {
			ifExistPath(g, i, w, visited, existFlag);
		}
	}
}
/************************ (END) core code (END) ***********************************/

void resetFlagArray(bool visited[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		visited[i] = false;
	}
}

int main() {
	/*
	char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	int numVertex = 8;
	char edges[][2] = {
		{'A', 'B'},
		{'A', 'C'},
		{'A', 'D'},
		{'C', 'E'},
		{'C', 'F'},
		{'C', 'G'},
		{'D', 'H'}
	};
	int numEdge = 7;
	*/

	char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};
	int numVertex = 6;
	char edges[][2] = {
		{'A', 'B'},
		{'A', 'D'},
		{'B', 'C'},
		{'B', 'E'},
		{'C', 'D'},
		{'C', 'E'},
		{'D', 'F'},
		{'E', 'F'}
	};
	int numEdge = 8;

	graph g = initGraph();
	createGraph(g, vertices, numVertex, edges, numEdge);
	printGraph(g);
	
	bool visited[MAX_NUM_VERTEX];

	resetFlagArray(visited, MAX_NUM_VERTEX);
	printf("\nDFS...\n");
	DFS(g, 0, visited);

	resetFlagArray(visited, MAX_NUM_VERTEX);
	printf("\nBFS...\n");
	BFS(g, 0, visited);

	resetFlagArray(visited, MAX_NUM_VERTEX);
	char startVertex, endVertex;
	int startVertexIndex, endVertexIndex;
	bool existFlag = false;
	printf("\nTest connectivity...\nInput the start vertex and end vertex -> ");
	scanf("%c %c", &startVertex, &endVertex);
	startVertexIndex = getVertexIndex(g, startVertex);
	endVertexIndex = getVertexIndex(g, endVertex);
	ifExistPath(g, startVertexIndex, endVertexIndex, visited, &existFlag);

	if (existFlag) {
		printf("\n%c --> %c path exists!\n", startVertex, endVertex);
	} else {
		printf("\n%c --> %c path *not* exists!\n", startVertex, endVertex);
	}

	return 0;
}
