#include "game_00.h"

/* The cross product of (first. */
MATCH s16 func_801AFF90(Point2D* origin, Point2D* first_point, Point2D* second_point) {
    s16 first_x;
    s16 first_y;

    first_x = first_point->x;
    first_y = first_point->y;
    return (((first_x - origin->x) * (second_point->y - first_y)) -
            ((first_y - origin->y) * (second_point->x - first_x)));
}
