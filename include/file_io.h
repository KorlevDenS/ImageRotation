#ifndef UNTITLED_FILE_IO_H
#define UNTITLED_FILE_IO_H

#include "byte_array.h"
#include <stdio.h>

enum read_status {
    READ_OK = 0,
    READ_NOT_OPENED,
    SEEK_FAULT,
    ALLOC_FAULT,
    READ_FAULT
};

enum read_status read_to_byte_array(FILE *input_file, struct byte_array *array);


enum write_status {
    WRITE_OK = 0,
    WRITE_NOT_OPENED,
    WRITE_FAULT
};

enum write_status write_from_byte_array(FILE **output_file, struct byte_array *array);

enum open_status {
    OPEN_OK = 0,
    OPEN_ERROR
};

enum open_status open_file(FILE **file, const char *file_path, const char *mode);

enum close_status {
    CLOSE_OK = 0,
    CLOSE_ERROR
};

enum close_status close_file(FILE *file);

#endif //UNTITLED_FILE_IO_H
