#include "include/base_image.h"

void image_init(struct image *img) {
    img->height = 0;
    img->width = 0;
    img->data = NULL;
}

void image_free(struct image *img) {
    img->height = 0;
    img->width = 0;
    free(img->data);
}

int image_allocate(struct image *img, size_t width_in_pixels, size_t height_in_pixels) {
    if (img->data == NULL) {
        img->width = width_in_pixels;
        img->height = height_in_pixels;
        img->data = malloc((sizeof(struct pixel) * width_in_pixels * height_in_pixels));
    } else {
        img->width = width_in_pixels;
        img->height = height_in_pixels;
        img->data = realloc(img->data, (sizeof(struct pixel) * width_in_pixels * height_in_pixels));
    }
    if (img->data == NULL) {
        img->width = 0;
        img->height = 0;
        return 1;
    } else return 0;
}

int get_pixel(struct image *img, struct pixel *pixel, size_t row_position, size_t column_position) {
    if (row_position >= img->height || column_position >= img->width) return 1;
    size_t position = row_position * img->width + column_position;
    *pixel = img->data[position];
    return 0;
}

int set_pixel(struct image *img, struct pixel pixel, size_t row_position, size_t column_position) {
    if (row_position >= img->height || column_position >= img->width) return 1;
    size_t position = row_position * img->width + column_position;
    img->data[position] = pixel;
    return 0;
}
