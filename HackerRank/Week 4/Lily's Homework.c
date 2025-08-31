#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);
typedef struct {
    int value;
    int index;
} Element;


int compare_asc(const void* a, const void* b) {
    return ((Element*)a)->value - ((Element*)b)->value;
}

int compare_desc(const void* a, const void* b) {
    return ((Element*)b)->value - ((Element*)a)->value;
}
int count_swaps(int* arr, int n, int ascending) {
    Element* elements = malloc(n * sizeof(Element));
    for (int i = 0; i < n; i++) {
        elements[i].value = arr[i];
        elements[i].index = i;
    }
    if (ascending)
        qsort(elements, n, sizeof(Element), compare_asc);
    else
        qsort(elements, n, sizeof(Element), compare_desc);

    bool* visited = calloc(n, sizeof(bool));
    int swaps = 0;

    for (int i = 0; i < n; i++) {
        if (visited[i] || elements[i].index == i)
            continue;

        int cycle_size = 0;
        int j = i;
        while (!visited[j]) {
            visited[j] = true;
            j = elements[j].index;
            cycle_size++;
        }

        if (cycle_size > 1)
            swaps += (cycle_size - 1);
    }

    free(elements);
    free(visited);
    return swaps;
}

int lilysHomework(int arr_count, int* arr) {
    int* arr_copy = malloc(arr_count * sizeof(int));
    memcpy(arr_copy, arr, arr_count * sizeof(int));
    int asc_swaps = count_swaps(arr_copy, arr_count, 1);

    memcpy(arr_copy, arr, arr_count * sizeof(int));
    int desc_swaps = count_swaps(arr_copy, arr_count, 0);

    free(arr_copy);
    return asc_swaps < desc_swaps ? asc_swaps : desc_swaps;
}


int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));

        *(arr + i) = arr_item;
    }

    int result = lilysHomework(n, arr);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
