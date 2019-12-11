#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 16 
#define MAX_NUM 100
#define random(x) (rand() % x)

typedef struct linkNode {
	int data;
	struct linkNode *next;
}linkNode, *linkList;

linkList createLinkList(int size) {
	linkList head = malloc(sizeof(linkNode));
	linkList tail = head;
	int i;

	srand(time(NULL));
	for (i = 0; i < size; i++) {
		linkNode * newNode = malloc(sizeof(linkNode));
		newNode->data = random(MAX_NUM);
		tail->next = newNode;
		tail = newNode;
	}

	tail->next = NULL;
	
	return head;
}

void display(linkList head) {
	head = head->next;

	while (head != NULL) {
		printf("%d\t", head->data);
		head = head->next;
	}

	putchar('\n');
}

// **************** (START) core code (START) ***********************
void insertSort(linkList head) {
	linkList p, pre, currentNode, nextNode;
	currentNode = head->next;
	head->next = NULL;

	while (currentNode != NULL) {
		pre = head;
		p = pre->next;
		nextNode = currentNode->next;

		while (p != NULL && p->data <= currentNode->data) {
			pre = p; // or: pre = pre->next;
			p = p->next;
		}

		currentNode->next = pre->next;
		pre->next = currentNode;
		
		currentNode = nextNode;
	}
}
// **************** (END) core code (END) ***************************

int main() {
	linkList l = createLinkList(ARRAY_SIZE);
	display(l);

	printf("Sorted...\n");

	insertSort(l);
	display(l);

	return 0;
}
