#include <stdio.h>
#include <stdlib.h>


typedef struct linkNode {
	int data;
	struct linkNode *next;
}linkNode, *linkList;

/********************** (START) core code (START) *************************/
void insert(linkList l, int x) {
	linkNode *newNode, *pre, *p;
	newNode = malloc(sizeof(linkNode));
	newNode->data = x;

	pre = l;
	p = l->next;

	while (p != NULL && p->data <= x) {
		pre = pre->next;
		p = p->next;
	} 
	
	newNode->next = pre->next;
	pre->next = newNode;
}
/********************** (END) core code (END) *************************/

void printLinkList(linkList head) {
	head = head->next;
	while (head != NULL) {
		printf("%d\t", head->data);
		head = head->next;
	}
	putchar('\n');
}

int main() {
	linkList head = malloc(sizeof(linkNode));
	head->next = NULL;
	int val;

	while (1) {
		printf("Enter a number to insert into the sorted linkList(Exits with 0): ");
		scanf("%d", &val);
		if (val == 0)
			break;
		insert(head, val);
		printLinkList(head);
	}

	return 0;
}
