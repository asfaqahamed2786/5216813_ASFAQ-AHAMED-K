#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000000
typedef struct {
    char *data;
    int type; 
} Operation;

char text[MAX_LEN + 1] = "";  
Operation history[MAX_LEN];
int history_top = -1;

// Push to history
void push_history(char *data, int type) {
    history_top++;
    history[history_top].data = strdup(data);
    history[history_top].type = type;
}
Operation pop_history() {
    return history[history_top--];
}

int main() {
    int Q;
    scanf("%d", &Q);
    char command[10];

    while (Q--) {
        scanf("%s", command);

        if (strcmp(command, "1") == 0) {
            char w[MAX_LEN + 1];
            scanf("%s", w);
            push_history(text, 1);
            strcat(text, w);

        } else if (strcmp(command, "2") == 0) {
            int k;
            scanf("%d", &k);
            int len = strlen(text);
            push_history(text, 2);
            text[len - k] = '\0'; // delete last k characters

        } else if (strcmp(command, "3") == 0) {
            int k;
            scanf("%d", &k);
            printf("%c\n", text[k - 1]);

        } else if (strcmp(command, "4") == 0) {
            if (history_top >= 0) {
                Operation op = pop_history();
                strcpy(text, op.data);
                free(op.data);
            }
        }
    }

    return 0;
}
