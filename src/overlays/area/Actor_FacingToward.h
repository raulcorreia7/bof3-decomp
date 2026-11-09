/* Returns the eight-way facing code (a g_FacingSteps row) that points from the actor row toward the position (x, y). */
/* func_801F4A34 (area104/14), func_801F4F78 (area121/14) */
MATCH s32 Actor_FacingToward(s32 x, s32 y, u8 row) {
    s32 dx = x - g_Actors[row].pos.x.fixed;
    s32 dy = y - g_Actors[row].pos.y.fixed;

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
