/* FileName: adjGraph.c
 * Function: testing the connectivity of two vertices in an undirected graph
 * Author: erqitao (erqitao@qq.com)
 * Date: 2019-12-01
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NUM_VERTEX 16
#define IMPOSSIBLE_VERTEX '#'

typedef struct adjGraph {
	char vertices[MAX_NUM_VERTEX];
	int edges[MAX_NUM_VERTEX][MAX_NUM_VERTEX];
	int numVertex, numEdge;
}adjGraph, *graph;

graph initGraph() {
	graph g = malloc(sizeof(adjGraph));
	g->numVertex = g->numEdge = 0;
	
	for (int i = 0; i < MAX_NUM_VERTEX; i++) {
		g->vertices[i] = IMPOSSIBLE_VERTEX;
	}

	for (int i = 0; i < MAX_NUM_VERTEX; i++) {
		for (int j = 0; j < MAX_NUM_VERTEX; j++) {
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

int getVertexValue(graph g, int v) {
	if (v < 0 ||  v >= g->numVertex)
		return IMPOSSIBLE_VERTEX;
	
	return g->vertices[v];
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
	printf("Number of Edge: %d\n", g->numEdge);

	puts("Vertices:");
	for(i = 0; i < g->numVertex; i++) {
		printf("%c\t", g->vertices[i]);
	}

	puts("\nEdges:");
	for (i = 0; i < g->numVertex; i++) {
		hasEdgeFlag = false;
		for (j = i + 1; j <  g->numVertex; j++) {
			if (g->edges[i][j] == 1) {
				printf("(%c, %c)\t", getVertexValue(g, i), getVertexValue(g, j));
				hasEdgeFlag = true;
			}
		}
		if (hasEdgeFlag) {
			putchar('\n');
		}
	}
}

void resetFlagArray(bool visited[], int n) {
	for (int i = 0; i < n; i++)
			visited[i] = false;
}

/**************************** (START) core code (START) **********************************/
void DFS(graph g, int vi, int vj, bool visited[], bool *hasPathFlag) {
	visited[vi] = true;
	printf("%c\t", getVertexValue(g, vi));

	if (vi == vj) {
		*hasPathFlag = true;
		return;
	}

	for (int i = firstNeighbor(g, vi); i >= 0; i = nextNeighbor(g, vi, i)) {
		if (!(*hasPathFlag) && !visited[i]) {
			DFS(g, i, vj, visited, hasPathFlag);
		}
	}
}
/**************************** (END) core code (END) **********************************/

int main() {
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
	bool hasPathFlag = false;
	char startVertex, endVertex;
	int startIndex, endIndex;

	graph g = initGraph();
	createGraph(g, vertices, numVertex, edges, numEdge);
	printGraph(g);

	resetFlagArray(visited, MAX_NUM_VERTEX);
	
	printf("Please input the source vertex(Eg. A): ");	
	scanf("%c", &startVertex);
	getchar();
	printf("Please input the target vertex(Eg. B): ");	
	scanf("%c", &endVertex);

	printf("start vertex = %c, end vertex = %c\n", startVertex, endVertex);

	startIndex = getVertexIndex(g, startVertex);
	endIndex = getVertexIndex(g, endVertex);

	if (startIndex < 0) {
		printf("Source vertex - %c is out of range.\n", startVertex);
		exit(-1);
	}

	if (endIndex < 0 ) {
		printf("Target vertex - %c is out out range.\n", endVertex);
		exit(-2);
	}

	printf("\nSearching Path...\n");
	DFS(g, startIndex, endIndex, visited, &hasPathFlag);
	if (hasPathFlag) {
		printf("\n%c -> %c : path exists!\n", startVertex, endVertex);
	} else {
		printf("\n%c -> %c : path *not* exists!\n", startVertex, endVertex);
	}

	return 0;
}
