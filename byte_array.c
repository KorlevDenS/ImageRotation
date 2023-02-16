#include "include/byte_array.h"

void byte_array_init(struct byte_array *array) {
    array->capacity = 0;
    array->next = NULL;
}

void byte_array_free(struct byte_array *array) {
    array->capacity = 0;
    free(array->next);
}

int byte_array_put_bytes(struct byte_array *array, const uint8_t *bytes, size_t position, size_t amount) {
    if (array->capacity < position + amount - 1) return 1;
    for (size_t i = 0; i < amount; i++) {
        array->next[position + i] = bytes[i];
    }
    return 0;
}

void byte_array_print(struct byte_array *array) {
    for (size_t i = 0; i < array->capacity; i++) {
        printf("%c", array->next[i]);
    }
}

int byte_array_put_string(struct byte_array *array, const char *string) {
    if (array->capacity < strlen(string)) return 1;
    else {
        for (size_t i = 0; i < strlen(string); i++) {
            array->next[i] = string[i];
        }
        return 0;
    }
}

int byte_array_allocate(struct byte_array *array, size_t capacity) {
    if (array->next == NULL && array->capacity == 0) {
        array->capacity = capacity;
        array->next = malloc(capacity);
    } else {
        array->capacity = capacity;
        array->next = realloc(array->next, capacity);
    }

    if (array->next == NULL) {
        array->capacity = 0;
        return 1;
    } else return 0;
}