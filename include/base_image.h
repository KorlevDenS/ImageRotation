#ifndef UNTITLED_BASE_IMAGE_H
#define UNTITLED_BASE_IMAGE_H

#include <stdint.h>
#include <stdlib.h>

struct image {
    size_t width, height;
    struct pixel *data;
};

struct pixel {
    uint8_t b;
    uint8_t g;
    uint8_t r;
};

void image_init(struct image *img);

void image_free(struct image *img);

int image_allocate(struct image *img, size_t width_in_pixels, size_t height_in_pixels);

int get_pixel(struct image *img, struct pixel *pixel, size_t row_position, size_t column_position);

int set_pixel(struct image *img, struct pixel pixel, size_t row_position, size_t column_position);


#endif //UNTITLED_BASE_IMAGE_H
