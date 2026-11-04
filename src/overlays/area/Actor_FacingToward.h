/* Returns the eight-way facing code (a g_FacingSteps row) that points from the
 * actor row toward the position (x, y): the signs of dx and dy against the row's
 * x and y pick 0 to 7, and equal positions give 1. One definition shared by the
 * world area overlays. Every change here must verify every member address. */
/* func_801F4A34 (area104/14), func_801F4F78 (area121/14) */
MATCH s32 Actor_FacingToward(s32 x, s32 y, u8 row) {
    s32 dx = x - g_Actors[row].x.fixed;
    s32 dy = y - g_Actors[row].y.fixed;

    if (dx < 0 && dy < 0) {
        return 0;
    }
    if (dx > 0 && dy > 0) {
        return 4;
    }
    if (dx < 0 && dy > 0) {
        return 6;
    }
    if (dx > 0 && dy < 0) {
        return 2;
    }
    if (dx > 0 && dy == 0) {
        return 3;
    }
    if (dx < 0 && dy == 0) {
        return 7;
    }
    if (dx == 0 && dy > 0) {
        return 5;
    }
    return 1;
}
