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


void generate_primes(int* primes, int count) {
    int num = 2, found = 0;
    while (found < count) {
        bool is_prime = true;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            primes[found++] = num;
        }
        num++;
    }
}


int* waiter(int number_count, int* number, int q, int* result_count) {
    int* primes = malloc(q * sizeof(int));
    generate_primes(primes, q);

    int** A = malloc((q + 1) * sizeof(int*));
    int* A_size = calloc(q + 1, sizeof(int));
    int** B = malloc(q * sizeof(int*));
    int* B_size = calloc(q, sizeof(int));

    A[0] = malloc(number_count * sizeof(int));
    for (int i = 0; i < number_count; i++) {
        A[0][i] = number[i];
    }
    A_size[0] = number_count;

    for (int i = 0; i < q; i++) {
        B[i] = malloc(A_size[i] * sizeof(int));
        A[i + 1] = malloc(A_size[i] * sizeof(int));

        int b_top = 0;
        int a_top = 0;

        for (int j = A_size[i] - 1; j >= 0; j--) {
            if (A[i][j] % primes[i] == 0) {
                B[i][b_top++] = A[i][j];
            } else {
                A[i + 1][a_top++] = A[i][j];
            }
        }

        B_size[i] = b_top;
        A_size[i + 1] = a_top;
    }

    int* result = malloc(number_count * sizeof(int));
    int r_index = 0;

    for (int i = 0; i < q; i++) {
        for (int j = B_size[i] - 1; j >= 0; j--) {
            result[r_index++] = B[i][j];
        }
    }

    for (int j = A_size[q] - 1; j >= 0; j--) {
        result[r_index++] = A[q][j];
    }

    *result_count = r_index;

    
    for (int i = 0; i <= q; i++) free(A[i]);
    for (int i = 0; i < q; i++) free(B[i]);
    free(A);
    free(B);
    free(A_size);
    free(B_size);
    free(primes);

    return result;
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

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));
    int n = parse_int(*(first_multiple_input + 0));
    int q = parse_int(*(first_multiple_input + 1));

    char** number_temp = split_string(rtrim(readline()));
    int* number = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int number_item = parse_int(*(number_temp + i));
        *(number + i) = number_item;
    }

    int result_count;
    int* result = waiter(n, number, q, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));
        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");
    fclose(fptr);

    return 0;
}
