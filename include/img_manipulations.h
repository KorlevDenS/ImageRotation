#ifndef MAIN_C_IMG_MANIPULATIONS_H
#define MAIN_C_IMG_MANIPULATIONS_H

#include "base_image.h"

enum image_manipulations {
    SWAB_COLUMN_ROW_POSITIONS = 0,
    INVERSE_ROW_ELEMENT,
    INVERSE_COLUMN_ELEMENT
};

void image_manipulate(struct image *img, enum image_manipulations action);

void image_swab_width_height(struct image *img);

#endif //MAIN_C_IMG_MANIPULATIONS_H
