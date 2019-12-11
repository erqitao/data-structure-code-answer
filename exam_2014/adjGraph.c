#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NUM_VERTEX 20
#define IMPOSSIBLE_VERTEX '#'

typedef struct adjGraph {
	char vertices[MAX_NUM_VERTEX];
	int edges[MAX_NUM_VERTEX][MAX_NUM_VERTEX];
	int numVertex, numEdge;
}adjGraph, *graph;

graph initGraph() {
	int i, j;

	graph g = malloc(sizeof(adjGraph));
	g->numVertex = g->numEdge = 0;

	for (i = 0; i < MAX_NUM_VERTEX; i++) {
		g->vertices[i] = IMPOSSIBLE_VERTEX;
	}
	
	for (i = 0; i < MAX_NUM_VERTEX; i++) {
		for (j = 0; j < MAX_NUM_VERTEX; j++) {
			g->edges[i][j] = 0;
		}
	}

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
	if (i < 0 || i >= g->numVertex) {
		return IMPOSSIBLE_VERTEX;
	}

	return g->vertices[i];
}

int firstNeighbor(graph g, int v) {
	int i;
	for (i = 0; i < g->numVertex; i++) {
		if (g->edges[v][i] == 1) {
			return i;
		}
	}
	return -1;
}

int nextNeighbor(graph g, int v, int w) {
	int i;
	for (i = w + 1; i < g->numVertex; i++) {
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
			g->edges[v1][v2] = g->edges[v2][v1] = 1; // undirected graph 
	}
}

void printGraph(graph g) {
	int i, j;
	bool hasEdgeFlag;

	printf("Number of vertex: %d\n", g->numVertex);
	printf("Number of edge: %d\n", g->numEdge);

	printf("Vertices:\n");
	
	for (i = 0; i < g->numVertex; i++) {
		printf("%c\t", g->vertices[i]);
	}

	printf("\nEdges:\n");
	
	for (i = 0; i < g->numVertex; i++) {
		hasEdgeFlag = false;
		for (j = 0; j < g->numVertex; j++) {
			if (g->edges[i][j] == 1) {
				printf("(%c, %c)\t", getVertexValue(g, i), getVertexValue(g, j));
				hasEdgeFlag = true;
			}
		}
		if (hasEdgeFlag) {
			putchar('\n');
		}
	}

	putchar('\n');
}

void resetFlagArray(bool visited[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		visited[i] = false;
	}
}


/**************************** (START) core code (START) *********************************/
void DFS(graph g, int v, bool visited[], bool *isFirstVertex) {
	visited[v] = true;
	if (*isFirstVertex) {
		printf("%c", getVertexValue(g, v));
		*isFirstVertex = false;
	} else {
		printf(",%c", getVertexValue(g, v));
	}

	for (int i = firstNeighbor(g, v); i >= 0; i = nextNeighbor(g, v, i)) {
		if (!visited[i]) {
			DFS(g, i, visited, isFirstVertex);
		}
	}
}

void componentTraversal(graph g, bool visited[], bool *isFirstVertex) {
	int i;
	for (i = 0; i < g->numVertex; i++) {
		if (!visited[i]) {
			*isFirstVertex = true;
			putchar('(');
			DFS(g, i, visited, isFirstVertex);
			putchar(')');
			putchar('\n');
		}
	}
}
/**************************** (END) core code (END) *********************************/

int main() {
	/*
	char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
	int numVertex = 10;
	char edges[][2] = {
			{'A', 'B'},
			{'C', 'F'},
			{'C', 'G'},
			{'D', 'G'},
			{'E', 'G'},
			{'E', 'H'},
			{'I', 'J'},
	};
	int numEdge = 7;
	*/

	char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
	int numVertex = 12;
	char edges[][2] = {
			{'A', 'D'},
			{'B', 'C'},
			{'B', 'D'},
			{'C', 'D'},
			{'E', 'G'},
			{'F', 'H'},
			{'G', 'H'},
			{'I', 'K'},
			{'J', 'K'},
	};
	int numEdge = 9;


	bool visited[MAX_NUM_VERTEX];
	bool isFirstFlag;
	
	graph g = initGraph();

	createGraph(g, vertices, numVertex, edges, numEdge);
	printGraph(g);

	puts("**************** Components Display *********************");
	resetFlagArray(visited, MAX_NUM_VERTEX);
	componentTraversal(g, visited, &isFirstFlag);

	return 0;
}

