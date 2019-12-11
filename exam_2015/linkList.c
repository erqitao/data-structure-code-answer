/* FileName: linkList.c
 * Funtion: A <- (A join B) (A and B are sorted linkLists)
 * Author: erqitao (erqitao@qq.com)
 * Date: 2019-12-01
 * */
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
	linkList tmp, head = malloc(sizeof(linkNode));
	head->next = NULL;
	srand(time(NULL) + random(MAX_NUM));

	for (int i = 0; i < size; i++) {
		tmp = malloc(sizeof(linkNode));
		tmp->data = random(MAX_NUM);
		//tail insertion
		tmp->next = head->next;
		head->next = tmp;
	}

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

		currentNode->next = pre->next;
		pre->next = currentNode;

		currentNode = nextNode;
	}
}

/************************ (START) core code (START) *******************************/
// A <- A join B
void join(linkList la, linkList lb) {
	linkList pa, pb, taila, nextNode;
	pa = la->next;
	pb = lb->next;
	taila = la;
	la->next = NULL;

	while (pa != NULL && pb != NULL) {
		if (pa->data < pb->data) {
			nextNode = pa->next;
			free(pa);
			pa = nextNode;
		} else if (pa->data == pb->data) {
			taila->next = pa;
			taila = pa;

			pa = pa->next;
			pb = pb->next;
		} else {
			pb = pb->next;
		}
	}

	while (pa != NULL) {
		nextNode = pa->next;
		free(pa);
		pa = nextNode;
	}

	taila->next = NULL;
}
/************************ (END) core code (END) *******************************/

void printLinkList(linkList head) {
	head = head->next;

	while (head != NULL) {
		printf("%d\t", head->data);
		head = head->next;
	}
	putchar('\n');
}

int main() {
	linkList la = createLinkList(ARRAY_SIZE);
	puts("LinkList A:");
	//printLinkList(la);
	insertSort(la);
	printLinkList(la);

	linkList lb = createLinkList(ARRAY_SIZE);
	puts("LinkList B:");
	//printLinkList(lb);
	insertSort(lb);
	printLinkList(lb);

	join(la, lb);
	puts("A join B:");
	printLinkList(la);

	return 0;
}
