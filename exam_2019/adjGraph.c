#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NUM_VERTEX 16

typedef struct adjGrap {
	int vertices[NUM_VERTEX];
	int edges[NUM_VERTEX][NUM_VERTEX];
	int numVertex, numEdge;
}adjGraph, *graph;

graph createGraph() {
	graph g = malloc(sizeof(adjGraph));
	g->numVertex = g->numEdge = 0;
	int i, j;

	for (i = 0; i < NUM_VERTEX; i++) {
		g->vertices[i] = '\0';
	}

	for (i = 0; i < NUM_VERTEX; i++) {
		for (j = 0; j < NUM_VERTEX; j++) {
			g->edges[i][j] = 0;
		}
	}

	return g;
}

int getVertexIndex(graph g, char v) {
	for (int i = 0; i < g->numVertex; i++) {
		if (g->vertices[i] == v)
			return i;
	}

	return -1;
}

char getVertexValue(graph g, int index) {
	return g->vertices[index];
}

void initGraph(graph g, char vertices[], int numVertex, char edges[][2], int numEdge) {
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
	}
}

void printGraph(graph g) {
	int i, j;
	printf("Vertexes: \n");
	for(i = 0; i < g->numVertex; i++)
		printf("%c\t", g->vertices[i]);

	printf("\nEdges: \n");
	for(i = 0; i < g->numVertex; i++) {
		for(j = 0; j < g->numVertex; j++)
			if (g->edges[i][j] == 1)
				printf("(%c, %c)\t", getVertexValue(g, i), getVertexValue(g, j));
		putchar('\n');
	}
}

int firstNeighbor(graph g, int v) {
	for (int i = 0; i < g->numVertex; i++) {
		if (g->edges[v][i] == 1)
			return i;
	}

	return -1;
}

int nextNeighbor(graph g, int v, int w) {
	for (int i = w + 1; i < g->numVertex; i++) {
		if (g->edges[v][i] == 1)
			return i;
	}

	return -1;
}

void DFS(graph g, int v, bool visited[], int *numVisitedVertex) {
	printf("%c\t", getVertexValue(g, v));
	visited[v] = true;
	*numVisitedVertex += 1;

	for (int i = firstNeighbor(g, v); i >= 0; i = nextNeighbor(g, v, i)) {
		if (!visited[i])
			DFS(g, i, visited, numVisitedVertex);
	}
}

bool isConnected(graph g, int v) {
	int numVisitedVertex = 0;
	bool visited[NUM_VERTEX];
	for (int i = 0; i < NUM_VERTEX; i++)
		visited[i] = false;

	DFS(g, v, visited, &numVisitedVertex);
	return numVisitedVertex == g->numVertex; 
}

int main() {
	char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	int numVertex = 7;
	char edges[][2] = {{'A', 'B'}, {'A', 'F'}, {'B', 'C'}, {'B', 'D'}, {'C', 'D'}, {'E', 'D'}, {'F', 'E'}, {'F', 'G'}, {'G', 'E'}};
	int numEdge = 9;

	graph g = createGraph();
	initGraph(g, vertices, numVertex, edges, numEdge);
	printGraph(g);
	bool visited[NUM_VERTEX];
	int startVertex = 0;

	if (isConnected(g, startVertex)) {
		printf("\nThere exist paths from vertex %c to all other vertices. !YES!", getVertexValue(g, startVertex));
	} else {
		printf("\nThere exist paths from vertex %c to all other vertices. !NO!", getVertexValue(g, startVertex));
	}

	return 0;
}
