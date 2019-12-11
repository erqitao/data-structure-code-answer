/* FileName: binTree.c 
 * Function: PreOrder Traversal With Layor of a binTree
 * Author: erqitao
 * Date: 2019-12-01
 * */
#include <stdio.h>
#include <stdlib.h>

typedef struct binNode {
	char data;
	struct binNode *lchild, *rchild;
}binNode, *binTree;

void createBinTree(binTree *root, char vertices[], int *index) {
	char val = vertices[*index];
	*index += 1;

	if (val == '#') {
		*root = NULL;
		return;
	}

	binNode *newNode = malloc(sizeof(binNode));
	newNode->data = val;
	*root = newNode;

	createBinTree(&(newNode->lchild), vertices, index);
	createBinTree(&(newNode->rchild), vertices, index);
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

/*********************** (START) core code (START) ******************************/
void preOrderWithLayor(binTree root, int layor) {
	if (root != NULL) {
		printf("(%c, %d)\t", root->data, layor);
		preOrderWithLayor(root->lchild, layor + 1);
		preOrderWithLayor(root->rchild, layor + 1);
	}
}
/*********************** (END) core code (END) ******************************/

int main() {
	char vertices[] = {'A', 'B', 'D', '#', '#', 'E', 'H', '#', '#', '#', 'C', 'F', '#', 'I', '#', '#', 'G', '#', '#'};
	int index = 0;
	binTree root = NULL;
	createBinTree(&root, vertices, &index);

	printf("PreOrder Traversal:\n");
	preOrder(root);

	printf("\nInOrder Traversal:\n");
	inOrder(root);

	printf("\nPreOrder Traversal With Layor:\n");
	preOrderWithLayor(root, 1);
	putchar('\n');

	return 0;
}
