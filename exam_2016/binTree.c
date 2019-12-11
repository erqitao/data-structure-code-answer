#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 100
#define QUEUE_SIZE 16

typedef struct binNode {
	char data;
	struct binNode *lchild, *rchild;
}binNode, *binTree;

typedef struct seqQueue {
	binTree data[QUEUE_SIZE];
	int front, rear;
}seqQueue, *queue;

// create a binTree using preOrder traversal
void createBinTree(binTree *root, char nodes[], int *index) {
	char val = nodes[*index];
	*index += 1;

	if (val == '#') {
		*root = NULL;
		return;
	}

	binNode *newNode = malloc(sizeof(binNode));
	newNode->data = val;
	*root = newNode;

	createBinTree(&((*root)->lchild), nodes, index);
	createBinTree(&((*root)->rchild), nodes, index);
}

void preOrder(binTree root) {
	if (root != NULL) {
		printf("%c\t", root->data);
		preOrder(root->lchild);
		preOrder(root->rchild);
	}
}

void inOrder(binTree root) {
	if (root != NULL) {
		inOrder(root->lchild);
		printf("%c\t", root->data);
		inOrder(root->rchild);
	}
}

void postOrder(binTree root) {
	if (root != NULL) {
		postOrder(root->lchild);
		postOrder(root->rchild);
		printf("%c\t", root->data);
	}
}

void layorOrder(binTree root) {
	queue q = malloc(sizeof(seqQueue));
	q->front = q->rear = 0;

	q->data[q->rear] = root;
	q->rear += 1;

	while (q->front != q->rear) {
		binTree currentNode = q->data[q->front];
		q->front += 1;
		printf("%c\t", currentNode->data);

		if (currentNode->lchild != NULL) {
			q->data[q->rear] = currentNode->lchild;
			q->rear += 1;
		}

		if (currentNode->rchild != NULL) {
			q->data[q->rear] = currentNode->rchild;
			q->rear += 1;
		}
	}
}

// ****************** (START) core code (START) ********************
void binTree2Array(binTree root, char ary[], int index, int *maxIndex) {
	if (root != NULL) {
		ary[index] = root->data;
		if (index > *maxIndex) {
			*maxIndex = index;
		}
		binTree2Array(root->lchild, ary, 2 * index, maxIndex);
		binTree2Array(root->rchild, ary, 2 * index + 1, maxIndex);
	}
}
// ******************** (END) core code (END) **********************

int main() {
	char nodes[] = {'A', 'B',  'D', '#', '#', '#', 'C', 'F', '#', 'G', '#', '#', 'E', '#', '#'};
	int index = 0;

	binTree root = NULL;
	createBinTree(&root, nodes, &index);

	printf("\nPreOrder:\n");
	preOrder(root);
	
	printf("\nInOrder:\n");
	inOrder(root);

	printf("\nPostOrder:\n");
	postOrder(root);

	printf("\nLayorOrder:\n");
	layorOrder(root);

	char ary[ARRAY_SIZE];
	int i, maxIndex = 0;
	for (i = 0; i < ARRAY_SIZE; i++) {
		ary[i] = '\0';
	}

	printf("\n\n*************************************************\n");

	binTree2Array(root, ary, 1, &maxIndex);
	printf("Max Index = %d\n", maxIndex);

	for (i = 1; i <= maxIndex; i++) {
		if (ary[i] == '\0') {
			printf("NULL\t");
		} else {
			printf("%c\t", ary[i]);
		}
	}

	printf("\n\n*************************************************\n");

	return 0;
}
