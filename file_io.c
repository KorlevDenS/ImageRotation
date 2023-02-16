#define ONE_BYTE 1

#include "include/file_io.h"

enum open_status open_file(FILE **file, const char *file_path, const char *mode) {
    *file = fopen(file_path, mode);
    if (*file == NULL) return OPEN_ERROR;
    else return OPEN_OK;
}

enum close_status close_file(FILE *file) {
    if (fclose(file) != 0) return CLOSE_ERROR;
    else return CLOSE_OK;
}

static int mv_pointer_to_file_end(FILE *file) {
    return fseek(file, 0, SEEK_END);
}

static int mv_pointer_to_file_start(FILE *file) {
    return fseek(file, 0, SEEK_SET);
}

static int extend_memory_for_file_in_array(FILE *input_file, struct byte_array *array) {
    if (byte_array_allocate(array, ftell(input_file))) {
        fclose(input_file);
        return 1;
    } else return 0;
}

enum read_status read_to_byte_array(FILE *input_file, struct byte_array *array) {

    if (input_file == NULL) return READ_NOT_OPENED;
    if (mv_pointer_to_file_end(input_file)) return SEEK_FAULT;
    if (extend_memory_for_file_in_array(input_file, array)) return ALLOC_FAULT;
    if (mv_pointer_to_file_start(input_file)) return SEEK_FAULT;

    if (fread(array->next, ONE_BYTE, array->capacity, input_file) != array->capacity) {
        fclose(input_file);
        return READ_FAULT;
    }

    return READ_OK;
}

enum write_status write_from_byte_array(FILE **output_file, struct byte_array *array) {
    if (*output_file == NULL) return WRITE_NOT_OPENED;
    if (fwrite(array->next, ONE_BYTE, array->capacity, *output_file) < array->capacity) return WRITE_FAULT;
    return WRITE_OK;
}

