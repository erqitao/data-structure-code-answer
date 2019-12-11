#include <stdio.h>
#include <stdlib.h>

typedef struct binNode {
	int data;
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

/************************ (START) core code (START) *****************************/
binTree preOrderLast(binTree root) {
	while (root) {
		while (root->rchild != NULL) {
			root = root->rchild;
		}

		if (root->lchild != NULL) {
			root = root->lchild;
		}else {
			break;	
		}
	}
	return root;
}
/************************ (END) core code (END) *****************************/

int main() {
	//char vertices[] = {'A', 'B', 'D', '#', '#', '#', 'C', 'E', '#', '#', 'F', 'G', 'H', '#', '#', 'I', '#', '#', '#'};
	char vertices[] = {'A', 'B', '#', '#', 'C', 'D', '#','#', 'E', 'F', 'G', '#', 'H', 'I', '#', 'J', '#', '#', '#', '#', '#'};
	binTree root = NULL;
	int index = 0;
	createBinTree(&root, vertices, &index);

	printf("PreOrder Traversal:\n");
	preOrder(root);

	printf("\nThe last node is:");
	binTree lastNodePtr = preOrderLast(root);
	if (lastNodePtr != NULL) {
		printf("%c\n", lastNodePtr->data);
	}

	return 0;
}
