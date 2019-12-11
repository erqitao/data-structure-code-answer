#include <stdio.h>
#include <stdlib.h>


typedef struct threadTreeNode {
	char data;
	struct threadTreeNode *lchild, *rchild;
	int ltag, rtag;
}threadTreeNode, *threadTree;

void createThreadTree(threadTree *root, char data[], int *index) {
	char val = data[*index];
	*index += 1;

	if (val == '#') {
		*root = NULL;
		return;
	}

	threadTreeNode *newNode = malloc(sizeof(threadTreeNode));
	newNode->data = val;
	newNode->ltag = newNode->rtag = 0;
	*root = newNode;

	createThreadTree(&(newNode->lchild), data, index);
	createThreadTree(&(newNode->rchild), data, index);
}

void preOrder(threadTree root) {
	if (root != NULL) {
		printf("%c\t", root->data);
		preOrder(root->lchild);
		preOrder(root->rchild);
	}
}

void inOrder(threadTree root) {
	if (root != NULL) {
		inOrder(root->lchild);
		printf("%c\t", root->data);
		inOrder(root->rchild);
	}
}

void threadPreOrder(threadTree currentNode, threadTree *pre) {
	if (currentNode != NULL) {
		if (currentNode->lchild == NULL) {
			currentNode->lchild = *pre;
			currentNode->ltag = 1;
		}

		if (*pre != NULL && (*pre)->rchild == NULL) {
			(*pre)->rchild = currentNode;
			(*pre)->rtag = 1;
		}

		*pre = currentNode;

		if (currentNode->ltag == 0)
			threadPreOrder(currentNode->lchild, pre);

		if (currentNode->rtag == 0)
			threadPreOrder(currentNode->rchild, pre);
	}
}

void thread(threadTree root) {
	threadTree pre = NULL;
	threadPreOrder(root, &pre);
	pre->rchild = NULL;
	pre->rtag = 1;
}

threadTree getLastNode(threadTree root) {
	if (root == NULL)
		return NULL;

	while (1) {
		while (root->rtag == 0) {
			root = root->rchild;
		}

		if (root->ltag == 1)
			break;
		root = root->lchild;
	}

	return root;
}

threadTree getFirstNode(threadTree root) {
	return root;
}

threadTree getNextNode(threadTree root) {
	if (root->ltag == 0)
		return root->lchild;
	return root->rchild;
}

/******************* (START) core code (START) *************************/
void preOrderNoRecursive(threadTree root) {
	threadTree p = getFirstNode(root); //  p = root
	while (p != NULL) {
		printf("%c\t", p->data);
		p = getNextNode(p);
	}
	putchar('\n');
}
/******************* (END) core code (END) *************************/

int main() {
	char pre[] = {'A', 'B', 'D', '#', '#', 'E', 'H', '#', '#', '#', 'C', 'F', '#', 'I', '#', '#', '#'};
	int index = 0;
	threadTree root = NULL;

	createThreadTree(&root, pre, &index);
	puts("PreOrder:");
	preOrder(root);

	puts("\nInOrder:");
	inOrder(root);

	thread(root);
	puts("\nPreOrder - No Recursive:");
	preOrderNoRecursive(root);

	threadTree last = getLastNode(root);
	printf("Last Node: %c\n", last->data);


	return 0;
}
