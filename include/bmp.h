#ifndef MAIN_C_BMP_H
#define MAIN_C_BMP_H

#include <stdint.h>
#include "base_image.h"
#include "byte_array.h"

struct bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

enum bmp_parsing_result {
    PARSING_OK = 0,
    NOT_ENOUGH_BYTES_FOR_HEADER,
    NOT_ENOUGH_BYTES_FOR_IMAGE,
    NOT_ENOUGH_MEMORY_FOR_IMAGE,
    WRONG_TYPE,
    WRONG_RESERVED,
    WRONG_SIZE,
    WRONG_WIDTH,
    WRONG_HEIGHT,
    WRONG_PLANES,
    WRONG_BIT_COUNT,
    WRONG_COMPRESSION,
    WRONG_CLR_IMPORTANT,
    WRONG_X_PELS_PER_METER,
    WRONG_Y_PELS_PER_METER
};

struct bmp_header bmp_header_create(struct image *img);

enum bmp_parsing_result from_bmp(struct image *img, struct byte_array *byteArray);

int to_bmp(struct image *img, struct byte_array *byteArray);

#endif //MAIN_C_BMP_H
