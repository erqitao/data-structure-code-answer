#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define ARRAY_SIZE 8 
#define MAX_NUM 100
#define random(x) (rand() %x)

typedef struct linkNode {
	int data;
	struct linkNode *next;
}linkNode, *linkList;

linkList createLinkList(int size) {
	linkList head = malloc(sizeof(linkNode));
	linkList tmp, tail = head;
	int i;

	srand(time(NULL) + random(MAX_NUM));
	for (i = 0; i < size; i++) {
		tmp = malloc(sizeof(linkNode));
		tmp->data = random(MAX_NUM);
		tail->next = tmp;
		tail = tmp;
	}
	tail->next = NULL;

	return head;
}

void insertSort(linkList head) {
	linkList pre, p, currentNode, nextNode;
	currentNode = head->next;
	head->next = NULL;

	while (currentNode != NULL) {
		nextNode = currentNode->next;

		pre = head;
		p = head->next;

		while (p != NULL && p->data <= currentNode->data) {
			pre = pre->next;
			p = p->next;
		}

		currentNode->next = p;
		pre->next = currentNode;

		currentNode = nextNode;
	}
}

linkList join(linkList la, linkList lb) {
	linkList lc = malloc(sizeof(linkNode));
	linkList pa, pb, tmp, tail = lc;
	pa = la->next;
	pb = lb->next;

	while (pa != NULL && pb != NULL) {
		if (pa->data < pb->data) {
			pa = pa->next;
		} else if (pa->data == pb->data) {
			tmp = malloc(sizeof(linkNode));
			tmp->data = pa->data;

			tail->next = tmp;
			tail = tmp;

			pa = pa->next;
			pb = pb->next;
		} else {
			pb = pb->next;
		}
	}
	tail->next = NULL;

	return lc;
}

linkList merge(linkList la, linkList lb) {
	linkList lc = malloc(sizeof(linkNode));
	linkList pa, pb, tmp, tail = lc;

	pa = la->next;
	pb = lb->next;

	while (pa != NULL && pb != NULL) {
		if (pa->data < pb->data) {
			tmp = malloc(sizeof(linkNode));
			tmp->data = pa->data;

			tail->next = tmp;
			tail = tmp;

			pa = pa->next;
		} else if (pa->data == pb->data) {
			tmp = malloc(sizeof(linkNode));
			tmp->data = pa->data;

			tail->next = tmp;
			tail = tmp;

			pa = pa->next;
			pb = pb->next;
		} else {
			tmp = malloc(sizeof(linkNode));
			tmp->data = pb->data;

			tail->next = tmp;
			tail = tmp;

			pb = pb->next;
		}
	}

	while (pa != NULL) {
		tmp = malloc(sizeof(linkNode));
		tmp->data = pa->data;

		tail->next = tmp;
		tail = tmp;

		pa = pa->next;
	}

	while (pb != NULL) {
		tmp = malloc(sizeof(linkNode));
		tmp->data = pb->data;
		
		tail->next = tmp;
		tail = tmp;

		pb = pb->next;
	}

	tail->next = NULL;

	return lc;
}

void printLinkList(linkList head) {
	head = head->next;
	while (head != NULL) {
		printf("%d\t", head->data);
		head = head->next;
	}
	putchar('\n');
}

int main() {
	linkList lista = createLinkList(ARRAY_SIZE);

	/*
	printf("\nLinkList A:\n");
	printLinkList(lista);
	*/
	printf("\nLinkList A Sorted:\n");
	insertSort(lista);
	printLinkList(lista);

	linkList listb = createLinkList(ARRAY_SIZE);
	/*
	printf("\nLinkList B:\n");
	printLinkList(listb);
	*/

	printf("\nLinkList B Sorted:\n");
	insertSort(listb);
	printLinkList(listb);

	printf("\n\n**********************************\n\n");

	printf("LinkList A join LinkList B:\n");
	linkList listc = join(lista, listb);
	printLinkList(listc);

	printf("\nLinkList A merge LinkList B:\n");
	linkList listd = merge(lista, listb);
	printLinkList(listd);

	return 0;
}
