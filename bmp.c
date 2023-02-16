#include <stdio.h>
#include "include/bmp.h"

#define BMP_TYPE 0x4d42
#define BYTE_SIZE_OF_PIXEL 3
#define SIZE_OF_HEADER 54
#define BMP_BIT_COUNT 24

struct bmp_header bmp_header_create(struct image *img) {
    return (struct bmp_header) {
            .bfType = BMP_TYPE,
            .bfileSize = SIZE_OF_HEADER + (img->width * 3 + img->width % 4) * img->height,
            .bfReserved = 0,
            .bOffBits = SIZE_OF_HEADER,
            .biSize = 40,
            .biWidth = img->width,
            .biHeight = img->height,
            .biPlanes = 1,
            .biBitCount = BMP_BIT_COUNT,
            .biCompression = 0,
            .biSizeImage = (img->width * 3 + img->width % 4) * img->height,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0
    };
}

static enum bmp_parsing_result read_bmp_header(struct bmp_header *header, struct byte_array *byteArray) {
    header->bfType = *(uint16_t *) &byteArray->next[0];
    if (header->bfType != BMP_TYPE) return WRONG_TYPE;
    header->bfileSize = *(uint32_t *) &byteArray->next[2];
    if (header->bfileSize <= 0) return WRONG_SIZE;
    header->bfReserved = *(uint32_t *) &byteArray->next[6];
    if (header->bfReserved != 0) return WRONG_RESERVED;
    header->bOffBits = *(uint32_t *) &byteArray->next[10];
    if (header->bfileSize <= 0) return WRONG_SIZE;
    header->biSize = *(uint32_t *) &byteArray->next[14];
    if (header->bfileSize <= 0) return WRONG_SIZE;
    header->biWidth = *(uint32_t *) &byteArray->next[18];
    if (header->biWidth <= 0) return WRONG_WIDTH;
    header->biHeight = *(uint32_t *) &byteArray->next[22];
    if (header->biHeight <= 0) return WRONG_HEIGHT;
    header->biPlanes = *(uint16_t *) &byteArray->next[26];
    if (header->biPlanes != 1) return WRONG_PLANES;
    header->biBitCount = *(uint16_t *) &byteArray->next[28];
    if (header->biBitCount != 24) return WRONG_BIT_COUNT;
    header->biCompression = *(uint32_t *) &byteArray->next[30];
    if (header->biCompression != 0) return WRONG_COMPRESSION;
    header->biSizeImage = *(uint32_t *) &byteArray->next[34];
    header->biXPelsPerMeter = *(uint32_t *) &byteArray->next[38];
    if (header->biXPelsPerMeter < 0) return WRONG_X_PELS_PER_METER;
    header->biYPelsPerMeter = *(uint32_t *) &byteArray->next[42];
    if (header->biYPelsPerMeter < 0) return WRONG_Y_PELS_PER_METER;
    header->biClrUsed = *(uint32_t *) &byteArray->next[46];
    header->biClrImportant = *(uint32_t *) &byteArray->next[50];
    if (header->biClrImportant < 0) return WRONG_CLR_IMPORTANT;

    return PARSING_OK;
}

static enum bmp_parsing_result
read_bmp_pixels(struct image *img, struct byte_array *byteArray, struct bmp_header *header) {
    size_t len_with_padding = header->biWidth * BYTE_SIZE_OF_PIXEL + header->biWidth % 4;
    if (byteArray->capacity < len_with_padding * header->biHeight + header->bOffBits) return NOT_ENOUGH_BYTES_FOR_IMAGE;
    if (image_allocate(img, header->biWidth, header->biHeight) != 0) return NOT_ENOUGH_MEMORY_FOR_IMAGE;

    size_t pointer;

    for (size_t i = 0; i < img->height; i++) {
        pointer = len_with_padding * i + SIZE_OF_HEADER;
        for (size_t j = 0; j < img->width; j++) {
            img->data[i * img->width + j].b = byteArray->next[pointer + 3 * j];
            img->data[i * img->width + j].g = byteArray->next[pointer + 3 * j + 1];
            img->data[i * img->width + j].r = byteArray->next[pointer + 3 * j + 2];
        }
    }

    return PARSING_OK;
}

enum bmp_parsing_result from_bmp(struct image *img, struct byte_array *byteArray) {
    if (byteArray->capacity < SIZE_OF_HEADER) return NOT_ENOUGH_BYTES_FOR_HEADER;
    struct bmp_header header;
    enum bmp_parsing_result header_result = read_bmp_header(&header, byteArray);
    if (header_result) return header_result;
    return read_bmp_pixels(img, byteArray, &header);
}

static int write_bmp_header(struct bmp_header *header, struct byte_array *array) {
    if (byte_array_allocate(array, header->bfileSize)) return 1;
    if (array->capacity < 54) return 1;
    byte_array_put_bytes(array, (uint8_t *) &header->bfType, 0, sizeof(uint16_t));
    byte_array_put_bytes(array, (uint8_t *) &header->bfileSize, 2, sizeof(uint32_t));
    byte_array_put_bytes(array, (uint8_t *) &header->bfReserved, 6, sizeof(uint32_t));
    byte_array_put_bytes(array, (uint8_t *) &header->bOffBits, 10, sizeof(uint32_t));
    byte_array_put_bytes(array, (uint8_t *) &header->biSize, 14, sizeof(uint32_t));
    byte_array_put_bytes(array, (uint8_t *) &header->biWidth, 18, sizeof(uint32_t));
    byte_array_put_bytes(array, (uint8_t *) &header->biHeight, 22, sizeof(uint32_t));
    byte_array_put_bytes(array, (uint8_t *) &header->biPlanes, 26, sizeof(uint16_t));
    byte_array_put_bytes(array, (uint8_t *) &header->biBitCount, 28, sizeof(uint16_t));
    byte_array_put_bytes(array, (uint8_t *) &header->biCompression, 30, sizeof(uint32_t));
    byte_array_put_bytes(array, (uint8_t *) &header->biSizeImage, 34, sizeof(uint32_t));
    byte_array_put_bytes(array, (uint8_t *) &header->biXPelsPerMeter, 38, sizeof(uint32_t));
    byte_array_put_bytes(array, (uint8_t *) &header->biYPelsPerMeter, 42, sizeof(uint32_t));
    byte_array_put_bytes(array, (uint8_t *) &header->biClrUsed, 46, sizeof(uint32_t));
    byte_array_put_bytes(array, (uint8_t *) &header->biClrImportant, 50, sizeof(uint32_t));
    return 0;
}

static int write_bmp_pixels(struct image *img, struct byte_array *array, uint32_t biWidth) {
    if (img->width * img->height * 3 + SIZE_OF_HEADER > array->capacity) return 1;
    size_t len_with_padding = biWidth * BYTE_SIZE_OF_PIXEL + biWidth % 4;
    size_t pointer;
    static const struct padding_t {
        unsigned char bytes[3];
    } padding = {{0, 0, 0}};
    (void) padding.bytes;

    for (size_t y = 0; y < img->height; y++) {
        pointer = SIZE_OF_HEADER + len_with_padding * y;
        *((struct padding_t *) &(array->next[pointer + len_with_padding - sizeof(struct padding_t)])) = padding;
        for (size_t x = 0; x < img->width; x++) {
            array->next[pointer + 3 * x] = img->data[y * img->width + x].b;
            array->next[pointer + 3 * x + 1] = img->data[y * img->width + x].g;
            array->next[pointer + 3 * x + 2] = img->data[y * img->width + x].r;
        }
    }
    return 0;
}

int to_bmp(struct image *img, struct byte_array *byteArray) {
    struct bmp_header header = bmp_header_create(img);
    if (write_bmp_header(&header, byteArray)) return 1;
    if (write_bmp_pixels(img, byteArray, header.biWidth)) return 1;
    return 0;
}