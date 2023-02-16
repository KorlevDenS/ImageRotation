#ifndef UNTITLED_BYTE_ARRAY_H
#define UNTITLED_BYTE_ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

struct byte_array {
    size_t capacity;
    uint8_t *next;
};

void byte_array_print(struct byte_array *array);

int byte_array_put_string(struct byte_array *array, const char *string);

int byte_array_put_bytes(struct byte_array *array, const uint8_t *bytes, size_t position, size_t amount);

int byte_array_allocate(struct byte_array *array, size_t capacity);

void byte_array_init(struct byte_array *array);

void byte_array_free(struct byte_array *array);

#endif //UNTITLED_BYTE_ARRAY_H
