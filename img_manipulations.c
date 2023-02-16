#include "include/img_manipulations.h"

typedef void (*action)(struct image *old_img, struct image *new_img, size_t i, size_t j);

static void swab_column_row_positions(struct image *old_img, struct image *new_img, size_t i, size_t j) {
    struct pixel pixel;
    get_pixel(old_img, &pixel, i, j);
    set_pixel(new_img, pixel, j, i);
}

static void inverse_row_element(struct image *old_img, struct image *new_img, size_t i, size_t j) {
    struct pixel pixel;
    get_pixel(old_img, &pixel, i, j);
    set_pixel(new_img, pixel, old_img->height - i - 1, j);
}

static void inverse_column_element(struct image *old_img, struct image *new_img, size_t i, size_t j) {
    struct pixel pixel;
    get_pixel(old_img, &pixel, i, j);
    set_pixel(new_img, pixel, i, old_img->width - j - 1);
}

static void do_nothing(struct image *old_img, struct image *new_img, size_t i, size_t j) {
    struct pixel pixel;
    get_pixel(old_img, &pixel, i, j);
    set_pixel(new_img, pixel, i, j);
}

action choose_action(enum image_manipulations act) {
    switch (act) {
        case SWAB_COLUMN_ROW_POSITIONS:
            return swab_column_row_positions;
        case INVERSE_COLUMN_ELEMENT:
            return inverse_column_element;
        case INVERSE_ROW_ELEMENT:
            return inverse_row_element;
        default:
            return do_nothing;
    }
}

void image_manipulate(struct image *img, enum image_manipulations act) {
    struct image new_image;
    image_init(&new_image);
    action manipulate = choose_action(act);
    if (!act) image_allocate(&new_image, img->height, img->width);
    else image_allocate(&new_image, img->width, img->height);
    for (size_t i = 0; i < img->height; i++) {
        for (size_t j = 0; j < img->width; j++) {
            manipulate(img, &new_image, i, j);
        }
    }
    image_free(img);
    *img = new_image;
}

