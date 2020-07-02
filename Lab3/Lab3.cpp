#include <cstdio>
#include <iostream>
using namespace std;

int heap[101];
unsigned sizeH;
unsigned parent(unsigned x) { return (x - 1) / 2; }
unsigned left(unsigned x) { return 2 * x + 1; }
unsigned right(unsigned x) { return 2 * x + 2; }
void print() {
    for (unsigned i = 0; i < sizeH; i++) {
        printf("%d ", heap[i]);
    }
}
void insert(int x) {
    if (sizeH < 100) {
        unsigned pos = sizeH++;
        heap[pos] = x;
        while (pos > 0 and heap[parent(pos)] > heap[pos]) {
            swap(heap[parent(pos)], heap[pos]);
            pos = parent(pos);
        }
    }
}
int extract() {
    int min = heap[0];
    heap[0] = heap[--sizeH];
    heap[sizeH] = 0;
    unsigned pos = 0;
    while (1) {
        unsigned smaller = pos;
        if (left(pos) < sizeH and heap[left(pos)] < heap[smaller]) {
            smaller = left(pos);
        }
        if (right(pos) < sizeH and heap[right(pos)] < heap[smaller]) {
            smaller = right(pos);
        }
        if (heap[pos] > heap[smaller]) {
            swap(heap[pos], heap[smaller]);
            pos = smaller;
        } else {
            break;
        }
    }
    return min;
}
void ex12(){
    int list[10] = { 93, 95, 65, 41, 97, 4, 83, 89, 18, 41 };
    for (int i = 0; i < 10; i++) {
        insert(list[i]);
    }
    for (int i = 0; i < 10; i++) {
        list[i] = extract();
        printf("%d ", list[i]);
    }
}

void csort(unsigned* list, unsigned n) {
    unsigned range = 0;
    for (unsigned i = 0; i < n; i++) {
        if (list[i] > range) {
            range = list[i];
        }
    } range++;
    unsigned* index = new unsigned[range];
    for (unsigned i = 0; i < range; i++) {
        index[i] = 0;
    }
    for (unsigned i = 0; i < n; i++) {
        index[list[i]]++;
    }
    for (unsigned i = 1; i < range; i++) {
        index[i] += index[i - 1];
    }
    unsigned* newList = new unsigned[n];
    for (unsigned i = 0; i < n; i++) {
        newList[index[list[i]] - 1] = list[i];
        index[list[i]]--;
    }
    for (unsigned i = 0; i < n; i++) {
        list[i] = newList[i];
    }
    delete[] newList;
    delete[] index;
}


void csort(unsigned* list, unsigned n, unsigned mask, unsigned group = 0);
void ex3() {
    unsigned list[10] = { 3, 5, 6, 1, 2, 0, 2, 4, 8, 4 };
    unsigned max = 0;
    for (unsigned i = 0; i < 10; i++) {
        if (list[i] > max) {
            max = list[i];
        }
    }
    csort(list, 10, ++max);
    for (unsigned i = 0; i < 10; i++) {
        printf("%d ", list[i]);
    }
}

void csort(unsigned* list, unsigned n, unsigned mask, unsigned group) {
    unsigned trunc = 1;
    while (group--) {
        trunc *= mask;
    }
    unsigned range = mask;
    unsigned* index = new unsigned[range];
    for (unsigned i = 0; i < range; i++) {
        index[i] = 0;
    }
    for (unsigned i = 0; i < n; i++) {
        index[list[i] / trunc % mask]++;
    }
    for (unsigned i = 1; i < range; i++) {
        index[i] += index[i - 1];
    }
    unsigned* newList = new unsigned[n];
    for (unsigned j = 0; j < n; j++) {
        unsigned i = n - j - 1;
        newList[index[list[i] / trunc % mask] - 1] = list[i];
        index[list[i] / trunc % mask]--;
    }
    for (unsigned i = 0; i < n; i++) {
        list[i] = newList[i];
    }
    delete[] newList;
    delete[] index;
}
void rsort(unsigned* list, unsigned n, unsigned mask) {
    unsigned groups = 0; // of log10(mask)digits or log2(mask)bits
    {
        unsigned max = 0;
        for (unsigned i = 0; i < n; i++) {
            if (list[i] > max) {
                max = list[i];
            }
        }
        while (max) {
            groups++;
            max /= mask;
        }
    }
    for (unsigned group = 0; group < groups; group++) {
        csort(list, n, mask, group);
    }
}
void ex44bonus() {
    unsigned list[10] = { 200, 618, 569, 760, 498, 422, 158, 452, 868, 75 };
    rsort(list, 10, 10);
    for (unsigned i = 0; i < 10; i++) {
        printf("%d ", list[i]);
    } printf("\n\n");
    unsigned list2[10] = { 1692177, 5273733, 3059225, 8408277, 4685159, 8859053, 12244935, 1003842, 13650309, 2490938 };
    rsort(list2, 10, 1 << 8);
    for (unsigned i = 0; i < 10; i++) {
        printf("%d ", list2[i]);
    } printf("\n\n");
}


int main()
{
    ex12();
    ex3();
    ex44bonus();

    return 0;
}
