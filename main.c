#include <stdio.h>
#include "include/file_io.h"
#include "include/bmp.h"
#include "include/image_rotation.h"

void print_error_message(const char *message) {
    fprintf(stderr, "%s\n", message);
}

void print_message(const char *message) {
    fprintf(stdin, "%s\n", message);
}

//int argc, char **argv
int main() {

    struct byte_array old_array;
    struct byte_array new_array;

    FILE *from;
    FILE *to;

    struct image image;

    /*if (argc != 3 ){
        print_error_message( "Exactly two file paths expected\n");
        return 1;
    }*/

    byte_array_init(&old_array);

    switch (open_file(&from, "C:\\Users\\mvideo\\CLionProjects\\untitled\\resources\\copy1.bmp", "rb")) {
        case OPEN_OK:
            print_message("File was opened successfully");
            break;
        case OPEN_ERROR:
            print_error_message("Couldn't open the file.");
            return 1;
    }
    switch (read_to_byte_array(from, &old_array)) {
        case READ_OK:
            print_message("File was read to byte array");
            break;
        case READ_NOT_OPENED:
            byte_array_free(&old_array);
            print_error_message("File is not opened");
            return 1;
        case SEEK_FAULT:
            byte_array_free(&old_array);
            print_error_message("Unable to move move the pointer to the position in file");
            return 1;
        case ALLOC_FAULT:
            byte_array_free(&old_array);
            print_error_message("Unable to allocate memory for byte array");
            return 1;
        case READ_FAULT:
            byte_array_free(&old_array);
            print_error_message("Could not read the file");
            return 1;
    }
    switch (close_file(from)) {
        case CLOSE_OK:
            print_message("File was closed successfully");
            break;
        case CLOSE_ERROR:
            print_error_message("Couldn't close the file.");
            return 1;
    }

    image_init(&image);

    switch (from_bmp(&image, &old_array)) {
        case PARSING_OK:
            print_message("Successfully parsed bmp to base image");
            break;
        case NOT_ENOUGH_BYTES_FOR_HEADER:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Not enough bytes for bmp header");
            return 1;
        case NOT_ENOUGH_BYTES_FOR_IMAGE:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Not enough bytes for bmp image");
            return 1;
        case NOT_ENOUGH_MEMORY_FOR_IMAGE:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Not enough memory for bmp header");
            return 1;
        case WRONG_TYPE:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Type of loaded image file is not valid");
            return 1;
        case WRONG_RESERVED:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Reserved data of loaded image file is not valid");
            return 1;
        case WRONG_SIZE:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Expected size of loaded image file is not valid");
            return 1;
        case WRONG_WIDTH:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Width of loaded image file is not valid");
            return 1;
        case WRONG_HEIGHT:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Height of loaded image file is not valid");
            return 1;
        case WRONG_PLANES:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Pales of loaded image file is not valid");
            return 1;
        case WRONG_BIT_COUNT:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Bit count of loaded image file is not valid");
            return 1;
        case WRONG_COMPRESSION:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Compression of loaded image file is not valid");
            return 1;
        case WRONG_CLR_IMPORTANT:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Color count of loaded image file is not valid");
            return 1;
        case WRONG_X_PELS_PER_METER:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("X pixels per meter of loaded image file is not valid");
            return 1;
        case WRONG_Y_PELS_PER_METER:
            byte_array_free(&old_array);
            image_free(&image);
            print_error_message("Y pixels per meter of loaded image file is not valid");
            return 1;
    }
    byte_array_free(&old_array);

    rotate_left_90(&image);

    byte_array_init(&new_array);
    if (to_bmp(&image, &new_array)) {
        byte_array_free(&new_array);
        image_free(&image);
        print_error_message("Unable to create new bmp inside the byte array");
        return 1;
    }

    image_free(&image);

    switch (open_file(&to, "C:\\Users\\mvideo\\CLionProjects\\untitled\\resources\\input.bmp", "wb")) {
        case OPEN_OK:
            print_message("File was opened successfully");
            break;
        case OPEN_ERROR:
            print_error_message("Couldn't open the file.");
            return 1;
    }
    switch (write_from_byte_array(&to, &new_array)) {
        case WRITE_OK:
            print_message("Byte array was written to file successfully");
            break;
        case WRITE_NOT_OPENED:
            byte_array_free(&new_array);
            print_error_message("File is not opened");
            return 1;
        case WRITE_FAULT:
            byte_array_free(&new_array);
            print_error_message("Could not write byte array to the file");
            return 1;
    }
    byte_array_free(&new_array);
    switch (close_file(to)) {
        case CLOSE_OK:
            print_message("File was closed successfully");
            break;
        case CLOSE_ERROR:
            print_error_message("Couldn't close the file.");
            return 1;
    }

    return 0;

}