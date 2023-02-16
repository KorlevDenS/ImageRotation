
#include "include/image_rotation.h"

void rotate_left_90(struct image *image) {
    image_manipulate(image, SWAB_COLUMN_ROW_POSITIONS);
    image_manipulate(image, INVERSE_COLUMN_ELEMENT);
}