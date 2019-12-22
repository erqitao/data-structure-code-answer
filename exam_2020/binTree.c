#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct binNode {
	int data;
	struct binNode *lchild, *rchild;
}binNode, *binTree;

/***************** (START) core code (START) ******************/
bool flagOfBST = true;
bool solved = false;
binTree pre = NULL;

void preOrderTest(binTree p) {
	if (!solved && p != NULL) {
		preOrderTest(p->lchild);

		if (pre != NULL && pre->data > p->data) {
			flagOfBST = false;
			solved = true;
			return;
		}
		pre = p;

		preOrderTest(p->rchild);
	}
}

bool isBST(binTree p) {
	preOrderTest(p);

	return flagOfBST;
}
/***************** (END) core code (END) ******************/

void createTree(binTree *p, int data[], int *index) {
	int val = data[*index];
	*index += 1;

	if (val == 0) {
		*p = NULL;
		return;
	}

	binNode *newNode = malloc(sizeof(binNode));
	newNode->data = val;
	*p = newNode;

	createTree(&(newNode->lchild), data, index);
	createTree(&(newNode->rchild), data, index);
}

void preOrder(binTree p) {
	if (p != NULL) {
		preOrder(p->lchild);
		printf("%d\t", p->data);
		preOrder(p->rchild);
	}
}

int main() {
	/*
	int data[] = {8, 3, 1, 0, 0, 5, 0, 0, 27, 15, 0, 0, 66, 0, 0};
	*/
	int data[] = {8, 3, 1, 0, 0, 5, 0, 0, 12, 15, 0, 0, 66, 0, 0};
	int index = 0;
	binTree root = NULL;
	createTree(&root, data, &index);
	preOrder(root);

	if(isBST(root)) {
		puts("\nYes!");
	} else {
		puts("\nNo!");
	}

	return 0;
}
