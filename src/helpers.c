#include "compaction/helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

#define NUL '\0'

void print_usage(const char* executable_name) {
    printf("Usage: %s [command] [input?]\n\n", executable_name);
    printf("Commands:\n");
    printf("prog: compacts sequences of repeated chars\n");
    printf("prog2: compacts sequences of repeated patterns\n");
    printf("desprog: uncompacts any of the above compaction\n");
    printf("help: shows this message\n");
}

const char* not_found(const char* executable_name) {
    const char* format = "Command not found, try using '%s help'";

    // -1 is because we subtract '%s' (-2) and add \0 (+1)
    int alloc_length = strlen(format) + strlen(executable_name) - 1;

    char* result = malloc(sizeof(char) * alloc_length);

    sprintf(result, format, executable_name);

    return result;
}

unsigned int str_eq(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}

unsigned int str_ne(const char* a, const char* b) {
    return !str_eq(a, b);
}

unsigned int substr_eq(const char* a,
                       const char* b,
                       int start_at_a,
                       int start_at_b,
                       int length) {
    if (a[start_at_a] == NUL && b[start_at_b] == NUL)
        return 1;  // if both strings end at same time, true

    if (a[start_at_a] == NUL || b[start_at_b] == NUL)
        return 0;  // if only one of them ends, false

    return a[start_at_a] == b[start_at_b] &&
           (!(length > 1) ||
            substr_eq(a, b, start_at_a + 1, start_at_b + 1, length - 1));
}

int str_slice(const char* value, int pos, int length, char* target) {
    int i = 0;
    while (i < length) {
        target[i] = value[pos + i];
        i++;
    }
    target[i++] = NUL;
    return i;
}

unsigned int is_number(char character) {
    // given that a char in C is represented by ASCII codes
    // if it's between 48 and 57 (inclusive), then it's a number
    return character >= '0' && character <= '9';
}

int scan_number(const char* word, int cursor, int* number) {
    char buffer[BUFFER_SIZE];
    int i = 0;

    // while we don't reach end of string
    while (word[cursor] != NUL) {
        if (!is_number(word[cursor]))
            break;                     // and don't reach something non-number
        buffer[i++] = word[cursor++];  // keep throwing digits into buffer
    }

    // if anything was read
    if (i) {
        buffer[i++] = NUL;
        *number = atoi(buffer);  // parses it to int into *number
    } else {
        *number = -1;  // otherwise populates *number with -1
    }

    // return last position of cursor
    return cursor;
}

int scan_string(const char* word, int cursor, char* string) {
    char buffer[BUFFER_SIZE];
    int i = 0;

    // while we don't reach end of string
    while (word[cursor] != NUL && !is_number(word[cursor])) {
        if (word[cursor] != '-')         // ignore hyphens
            buffer[i++] = word[cursor];  // keep throwing letters into buffer
        cursor++;
    }

    // if anything was read
    if (i) {
        buffer[i++] = NUL;
        strcpy(string, buffer);  // copies it into *string
    }

    // return last position of cursor
    return cursor;
}
