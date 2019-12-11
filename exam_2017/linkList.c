#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define random(x) (rand() % x)
#define ARRAY_SIZE 10
#define MAX_NUM 100

typedef struct linkNode {
	int data;
	struct linkNode *next;
}linkNode, *linkList;

linkNode* createLinkList(int size) {
	linkNode *head = malloc(sizeof(linkNode));
	linkNode *tail = head;
	int i;

	srand(time(NULL));
	for (i  = 0; i < size; i++) {
		linkNode *newNode = malloc(sizeof(linkNode));
		newNode->data = random(MAX_NUM);
		tail->next = newNode;
		tail = newNode;
	}
	tail->next = NULL;
	
	return head;
}

/********************** (START) core code (START) *************************/
void reverseLinkList(linkNode *head) {
	linkNode *p, *nextNode;
	p = head->next;
	head->next = NULL;

	while (p != NULL) {
		nextNode = p->next;
		p->next = head->next;
		head->next = p;
		p = nextNode;
	}
}
/********************** (END) core code (END) *************************/

void printLinkList(linkNode *head) {
	head = head->next;
	while (head != NULL) {
		printf("%d\t", head->data);
		head = head->next;
	}
	putchar('\n');
}

int main() {
	linkNode * l = createLinkList(ARRAY_SIZE);
	printLinkList(l);

	printf("Reverse the linkList...\n");
	reverseLinkList(l);
	printLinkList(l);

	return 0;
}
