#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_HEAP_SIZE 100000

int heap[MAX_HEAP_SIZE];
int heap_size = 0;
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
void heapify_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] > heap[index]) {
            swap(&heap[parent], &heap[index]);
            index = parent;
        } else {
            break;
        }
    }
}
void heapify_down(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap_size && heap[left] < heap[smallest])
        smallest = left;
    if (right < heap_size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&heap[smallest], &heap[index]);
        heapify_down(smallest);
    }
}
void insert(int val) {
    heap[heap_size++] = val;
    heapify_up(heap_size - 1);
}
int find(int val) {
    for (int i = 0; i < heap_size; i++) {
        if (heap[i] == val)
            return i;
    }
    return -1;
}
void delete(int val) {
    int index = find(val);
    if (index == -1)
        return;

    heap[index] = heap[--heap_size];  
    heapify_down(index);
}
    int get_min() {
    return heap[0]; 
}
int main() {
    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int type, value;
        scanf("%d", &type);

        if (type == 1) {
            scanf("%d", &value);
            insert(value);
        } else if (type == 2) {
            scanf("%d", &value);
            delete(value);
        } else if (type == 3) {
            printf("%d\n", get_min());
        }
    }
    
    return 0;
}
