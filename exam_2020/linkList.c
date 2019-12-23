#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define random(x) (rand() % x)
#define MAX_NUM 10

typedef struct linkNode {
	int data;
	struct linkNode *next;
}linkNode, *linkList;

linkList createLinkList(int size) {
	linkNode *tmp, *head = malloc(sizeof(linkNode));
	head->next = NULL; // empty list

	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		tmp = malloc(sizeof(linkNode));
		tmp->data = random(MAX_NUM);
		// tail insert
		tmp->next = head->next;
		head->next = tmp; 
	}

	return head;
}

void printLinkList(linkList head) {
	head = head->next;
	while (head != NULL) {
		printf("%d\t", head->data);
		head = head->next;
	}
	putchar('\n');
}

void insertSort(linkList head) {
	linkNode *pre, *p, *currentNode, *nextNode;

	currentNode = head->next;
	head->next = NULL;

	while (currentNode != NULL) {
		nextNode = currentNode->next;

		pre = head;
		p = head->next;

		while (p != NULL && p->data <= currentNode->data) {
			pre = p;
			p = p->next;
		}

		currentNode->next = p;
		pre->next = currentNode;

		currentNode = nextNode;
	}
}

/******************* (START) core code (START) *********************/
void deleteRedundancy(linkList head) {
	if (head == NULL || head->next == NULL || head->next->next == NULL)
		return;
	linkNode *pre, *p, *nextNode;
	pre = head->next;
	p = head->next->next;

	while (p != NULL) {
		if (p->data == pre->data) {
			nextNode = p->next;
			free(p);
			pre->next = nextNode;
			p = nextNode;
		} else {
			pre = p;
			p = p->next;
		}
	}
}
/******************* (END) core code (END) *********************/

int main() {
	linkList list = createLinkList(10);
	printLinkList(list);

	puts("Sorted:");
	insertSort(list);
	printLinkList(list);

	puts("Deleting Redundancy elements...");
	deleteRedundancy(list);
	printLinkList(list);

	return 0;
}
