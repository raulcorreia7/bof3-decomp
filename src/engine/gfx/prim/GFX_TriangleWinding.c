#include "engine/game/00/game_00.h"

/* The cross product of (first - origin) and (second - first): its sign tells which side of the
 * line origin-first the point second lies on. */
/* func_801AFF90 */
MATCH s16 GFX_TriangleWinding(Pos2* origin, Pos2* first_point, Pos2* second_point) {
    s16 first_x;
    s16 first_y;

    first_x = first_point->vx;
    first_y = first_point->vy;
    return (((first_x - origin->vx) * (second_point->vy - first_y)) - ((first_y - origin->vy) * (second_point->vx - first_x)));
}
