#include <stdio.h>
#include <stdlib.h>

#define MAX 100000  


typedef struct Stack {
    int data[MAX];
    int top;
} Stack;


void push(Stack* s, int val) {
    s->data[++(s->top)] = val;
}


int pop(Stack* s) {
    if (s->top == -1) return -1; 
    return s->data[(s->top)--];
}


int peek(Stack* s) {
    if (s->top == -1) return -1; 
    return s->data[s->top];
}


int isEmpty(Stack* s) {
    return s->top == -1;
}

int main() {
    Stack s1, s2;
    s1.top = -1;
    s2.top = -1;

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int type, x;
        scanf("%d", &type);

        if (type == 1) {
            scanf("%d", &x);
            push(&s1, x);
        } else if (type == 2) {
            if (isEmpty(&s2)) {
                while (!isEmpty(&s1)) {
                    push(&s2, pop(&s1));
                }
            }
            pop(&s2);
        } else if (type == 3) {
            if (isEmpty(&s2)) {
                while (!isEmpty(&s1)) {
                    push(&s2, pop(&s1));
                }
            }
            printf("%d\n", peek(&s2));
        }
    }

    return 0;
}
