#include "game_00.h"

/* The cross product of (first - origin) and (second - first): its sign tells which side of the
 * line origin-first the point second lies on. */
MATCH s16 func_801AFF90(Point2s* origin, Point2s* first_point, Point2s* second_point) {
    s16 first_x;
    s16 first_y;

    first_x = first_point->x;
    first_y = first_point->y;
    return (((first_x - origin->x) * (second_point->y - first_y)) - ((first_y - origin->y) * (second_point->x - first_x)));
}
