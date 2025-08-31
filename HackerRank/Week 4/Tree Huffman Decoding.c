#include <stdio.h>
#include <stdlib.h>
struct node {
    int freq;
    char data;
    struct node* left;
    struct node* right;
};
void decode_huff(struct node* root, char* s) {
    struct node* current = root;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        // If it's a leaf node
        if (current->left == NULL && current->right == NULL) {
            printf("%c", current->data);
            current = root;
        }
    }
}
