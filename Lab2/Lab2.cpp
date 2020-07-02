#include <cstdio>
#include <iostream>
using namespace std;

#define nl printf("\n")

bool printFlag;

struct stack {
	int info;
	stack* next;
} *tos;
void loop(stack* current) {
	if (current == NULL)
		return;
	printf("%d ", current->info);
	if (current->next != NULL)
		loop(current->next);
}
void push(int x) {
	stack* newStack = new stack;
	newStack->info = x;
	newStack->next = tos;
	tos = newStack;

	if (printFlag) {
		printf("push %d\n", x);
		loop(tos);
		nl;
	}
}
int pop() {
	int value = -1;
	stack* auxStack = tos;
	if (tos != NULL) {
		tos = tos->next;
		value = auxStack->info;
		delete auxStack;
	}

	if (printFlag) {
		printf("pop %d\n", value);
		loop(tos);
		nl;
	}
	return value;
}

void ex1() {
	printf("Ex1\n");
	printFlag = 1;
	push(1);
	pop();
	push(2);
	push(3);
	nl;
	printFlag = 0;
}
void ex3() {
	printf("Ex3\n");
	int v[8] = { 1, 2, 2, 1, 3, 3, 4, 4 };
	for (int i = 0; i < 8; i++) {
		if (tos == NULL or tos->info != v[i])
			push(v[i]);
		else
			pop();
	}
	if (tos == NULL)
		printf("Configuratie valida");
	else
		printf("Configuratie invalida");
	nl;
}

struct deq {
	int info;
	deq* prev, * next;
} *first, * last;
void loop(deq* current) {
	if (current == NULL)
		return;
	printf("%d ", current->info);
	if (current->next != NULL)
		loop(current->next);
}
void push_left(int x) {
	deq* newDeq = new deq;
	newDeq->info = x;
	newDeq->next = first;
	newDeq->prev = NULL;
	if (first != NULL)
		first->prev = newDeq;
	first = newDeq;
	if (last == NULL)
		last = first;
	if (printFlag) { printf("push_left %d\n", x); loop(first); nl; }
}
void push_right(int x) {
	deq* newDeq = new deq;
	newDeq->info = x;
	newDeq->prev = last;
	newDeq->next = NULL;
	if (last != NULL)
		last->next = newDeq;
	last = newDeq;
	if (first == NULL)
		first = last;
	if (printFlag) { printf("push_right %d\n", x); loop(first); nl; }
}
int pop_left() {
	int value = -1;
	deq* auxDeq = first;
	if (first != NULL) {
		value = first->info;
		if (first->next == NULL) {
			first = NULL;
			last = NULL;
		} else {
			first = first->next;
			first->prev = NULL;
		}
	}
	delete auxDeq;
	if (printFlag) { printf("pop_left %d\n", value); loop(first); nl; }
	return value;
}
int pop_right() {
	int value = -1;
	deq* auxDeq = last;
	if (first != NULL) {
		value = last->info;
		if (last->prev == NULL) {
			first = NULL;
			last = NULL;
		} else {
			last = last->prev;
			last->next = NULL;
		}
	}
	delete auxDeq;
	if (printFlag) { printf("pop_right %d\n", value); loop(first); nl; }
	return value;
}

void ex2() {
	printf("Ex2\n");
	printFlag = 1;
	push_left(1);
	push_right(2);
	pop_right();
	pop_left();
	push_right(3);
	pop_left();
	nl;
	printFlag = 0;
}
void ex4() {
	printf("Ex4\n");
	int image[7][7] = {
		{0, 0, 1, 0, 0, 0, 0},
		{0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 1, 1, 0, 0},
		{0, 1, 0, 0, 1, 0, 1},
		{1, 1, 1, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 1, 1}
	}, counter = 2;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (image[i][j] == 1) {
				push_right(i);
				push_right(j);
				while (first != NULL) {
					int x = first->info;
					int y = first->next->info;
					image[x][y] = counter;

					if (x > 0 and image[x - 1][y] == 1) {
						push_right(x - 1); push_right(y);
					}
					if (y > 0 and image[x][y - 1] == 1) {
						push_right(x); push_right(y - 1);
					}
					if (x < 7 - 1 and image[x + 1][y] == 1) {
						push_right(x + 1); push_right(y);
					}
					if (y < 7 - 1 and image[x][y + 1] == 1) {
						push_right(x); push_right(y + 1);
					}
					pop_left();
					pop_left();
				}
				counter++;
			}
			printf("%d ", image[i][j]);
		}
		nl;
	}
}

void ex5() {
	int v[5] = { 1, 4, 3, 1, 1 }, n = 5;
	int element, counter = 0;
	for (int i = 0; i < n; i++) {
		if (counter == 0) {
			element = v[i], counter = 1;
		} else {
			counter += (element == v[i] ? 1 : -1);
		}
	}
	if (counter != 0) {
		counter = 0;
		for (int i = 0; i < n; i++) {
			if (v[i] == element) {
				counter++;
			}
		}
		if (counter * 2 > n) {
			printf("%d este element majoritar\n", element);
			return;
		}
	}
	printf("Nu exista element majoritar\n");
}

struct point {
	int rank = 0, x = 0, y = 0;
	point* parent = NULL;
} image2[7][7] = { NULL };
void makeSet(int i, int j) {
	image2[i][j].parent = &(image2[i][j]);
	image2[i][j].rank = 0, image2[i][j].x = i, image2[i][j].y = j;
}
point* findSet(point* x) {
	if (x != x->parent) {
		x->parent = findSet(x->parent);
	}
	return x->parent;
}
void link(point* x, point* y) {
	if (x->rank > y->rank) {
		y->parent = x;
	} else {
		x->parent = y;
		if (x->rank == y->rank) {
			y->rank++;
		}
	}
}
void union1(point* x, point* y) {
	link(findSet(x), findSet(y));
}
void ex4bonus() {
	printf("Ex4bonus\n");
	int image[7][7] = {
		{0, 0, 1, 0, 0, 0, 0},
		{0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 1, 1, 0, 0},
		{0, 1, 0, 0, 1, 0, 1},
		{1, 1, 1, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 1, 1}
	};
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (image[i][j] == 1) {
				makeSet(i, j);
				if (i > 0 and image[i - 1][j] == 1) {
					point* root1 = findSet(&image2[i][j]);
					point* root2 = findSet(&image2[i - 1][j]);
					union1(root1, root2);
				}
				if (j > 0 and image[i][j - 1] == 1) {
					point* root1 = findSet(&image2[i][j]);
					point* root2 = findSet(&image2[i][j - 1]);
					union1(root1, root2);
				}
			}
		}
	}
	int counter = 2;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (image[i][j] == 1 and image2[i][j].parent->x == i and image2[i][j].parent->y == j) {
				image[i][j] = counter++;
			}
		}
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (image[i][j] == 1) {
				image[i][j] = image[image2[i][j].parent->x][image2[i][j].parent->y];
			}
			printf("%d ", image[i][j]);
		}
		nl;
	}
}

int main() {
	ex1();
	ex3();
	ex2();
	ex4();
	ex5();
	ex4bonus();

	return 0;
}
