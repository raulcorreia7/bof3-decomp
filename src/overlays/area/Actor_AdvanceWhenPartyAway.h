/* Advance the work state when the party position is outside the work cell:
 * the first axis alone, or both checks of the second axis. One definition
 * shared by the world area overlays; the cell is whole-cell fixed point in the
 * scratch work and the party position is g_Game.members[0].pos.x.fixed/g_Game.members[0].pos.y.fixed. Each overlay
 * includes this file where the function sits.
 */
/* func_801F2F54 (area158), func_801F2F54 (area160), func_801F2F54 (area161), func_801F2F54 (area162), func_801F2F54
   (area163), func_801F2F54 (area164), func_801F2F54 (area165), func_801F2F54 (area166), func_801F2F68 (area169),
   func_801F2F88 (area157), func_801F303C (area167), func_801F3794 (area168), func_801F37D8 (area174), func_801F3E04
   (area139) */
MATCH void Actor_AdvanceWhenPartyAway(void) {
    Actor* work;

    work = g_Task;
    if (work->direction_08 != 0) {
        if (abs(g_Game.members[0].pos.y.fixed - ((((s32)COORD_INT(work->pos.y) + 1) << 16) | 0x8000)) > TO_COORD(2)) {
            goto advance;
        }
        if (abs(g_Game.members[0].pos.x.fixed - ((s32)COORD_INT(work->pos.x) << 16)) <= TO_COORD(2)) {
            goto call;
        }
        if (abs(g_Game.members[0].pos.x.fixed - (((s32)COORD_INT(work->pos.x) + 1) << 16)) <= TO_COORD(2)) {
            goto call;
        }
    } else {
        if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(work->pos.x) + 1) << 16) | 0x8000)) > TO_COORD(2)) {
            goto advance;
        }
        if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(work->pos.y) << 16)) <= TO_COORD(2)) {
            goto call;
        }
        if (abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(work->pos.y) + 1) << 16)) <= TO_COORD(2)) {
            goto call;
        }
    }
advance:
    work->header.step++;
call:
    Area_Update();
}
