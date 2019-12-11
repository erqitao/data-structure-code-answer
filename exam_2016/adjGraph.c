#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NUM_VERTEX 20

typedef struct adjGraph {
	char vertices[MAX_NUM_VERTEX];
	char edges[MAX_NUM_VERTEX][MAX_NUM_VERTEX];
	int numVertex, numEdge;
}adjGraph, *graph;

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
	int i, j, n = g->numVertex;
	printf("The number of vertex: %d\n", n);
	printf("The number of edge: %d\n", g->numEdge);

	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (g->edges[i][j] == 1) {
				printf("(%c, %c)\t", getVertexValue(g, i), getVertexValue(g, j));
			}
		}
		putchar('\n');
	}
}

void resetFlagArray(bool visited[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		visited[i] = false;
	}
}


void OrdinaryDFS(graph g, int v, bool visited[]) {
	printf("%c\t", getVertexValue(g, v));
	visited[v] = true;
	int i;
	for (i = firstNeighbor(g, v); i != -1; i = nextNeighbor(g, v, i)) {
		if (!visited[i]) {
			OrdinaryDFS(g, i, visited);
		}
	}
}

/************************ (START) core code (START) ********************************/
void DFS(graph g, int v, bool visited[], int *numVisitedVertex, int *numVisitedEdge) {
	printf("%c\t", getVertexValue(g, v));
	visited[v] = true;
	*numVisitedVertex += 1;

	int i;
	for (i = firstNeighbor(g, v); i != -1; i = nextNeighbor(g, v, i)) {
		*numVisitedEdge += 1;
		if (!visited[i]) {
			DFS(g, i, visited, numVisitedVertex, numVisitedEdge);		
		}
	}
}

bool isTree(graph g, bool visited[]) {
	int numVisitedVertex, numVisitedEdge;
	numVisitedVertex = numVisitedEdge = 0;

	DFS(g, 0, visited, &numVisitedVertex, &numVisitedEdge);

	/*
	printf("\nthe number of visited vertex: %d", numVisitedVertex);
	printf("\nthe number of visited edge: %d\n", numVisitedEdge);
	*/

	if (numVisitedVertex == g->numVertex && numVisitedEdge == 2 * (g->numVertex - 1))
		return true;
	else
		return false;
}
/************************ (END) core code (END) ********************************/

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
	OrdinaryDFS(g, 0, visited);
	putchar('\n');

	resetFlagArray(visited, MAX_NUM_VERTEX);
	bool flag = isTree(g, visited);
	if (flag) {
		printf("\nThis graph is a tree.\n");
	} else {
		printf("\nThis graph is *not* a tree.\n");
	}

	return 0;
}
