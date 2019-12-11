/* FileName: quickSort.c
 * Function: quick sort algorithm
 * Author: erqitao
 * Date: 2019-12-02
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 16 
#define MAX_NUM 100
#define random(x) (rand() % x)

void initArray(int ary[], int size) {
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		ary[i] = random(MAX_NUM);
	}
}

void printArray(int ary[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d\t", ary[i]);
	}
	putchar('\n');
}

int partition(int ary[], int low, int high) {
	int pi, pj, pivot;
	pi = low;
	pj = high;
	pivot = ary[low];

	while (pi < pj) {
		while (pi < pj && ary[pj] >= pivot)
				pj--;
		if (pi < pj) {
			ary[pi] = ary[pj];
			pi++;
		}

		while (pi < pj && ary[pi] <= pivot) {
				pi++;
		}
		if (pi < pj) {
			ary[pj] = ary[pi];
			pj--;
		}
	}
	ary[pi] = pivot;

	return pi;
}

void quickSort(int ary[], int low, int high) {
	if (low >= high)
		return;
	int mid =  partition(ary, low, high);
	quickSort(ary, low, mid - 1);
	quickSort(ary, mid + 1, high);
}

int main() {
	int ary[ARRAY_SIZE];
	initArray(ary, ARRAY_SIZE);

	puts("To be sorted...");
	printArray(ary, ARRAY_SIZE);

	puts("Sorted...");
	quickSort(ary, 0, ARRAY_SIZE - 1);
	printArray(ary, ARRAY_SIZE);

	return 0;
}
