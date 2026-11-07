/* Advances the work state when the party position is outside the work cell:
 * the first axis alone decides, and the second axis keeps the work in place
 * when the party stands in either half-cell of it. Unlike
 * Actor_AdvanceWhenPartyAway this member returns without the area update. One
 * definition shared by the world area overlays; the cell is whole-cell fixed
 * point in the scratch work and the party position is D_80145EC4/D_80145EC8.
 * Every change here must verify every member address.
 */
/* func_801F2FB0 (area147/13), func_801F3020 (area148/13), func_801F3F84 (area170/13) */
MATCH void Actor_AdvanceOutsidePartyCell(void) {
    Actor* work;

    work = g_Task;
    if (work->direction_08 != 0) {
        if (abs(D_80145EC8 - ((((s32)COORD_INT(work->pos.y) + 1) << 16) | 0x8000)) > TO_COORD(2)) {
            goto advance;
        }
        if (abs(D_80145EC4 - ((s32)COORD_INT(work->pos.x) << 16)) <= TO_COORD(2)) {
            return;
        }
        if (abs(D_80145EC4 - (((s32)COORD_INT(work->pos.x) + 1) << 16)) <= TO_COORD(2)) {
            return;
        }
    } else {
        if (abs(D_80145EC4 - ((((s32)COORD_INT(work->pos.x) + 1) << 16) | 0x8000)) > TO_COORD(2)) {
            goto advance;
        }
        if (abs(D_80145EC8 - ((s32)COORD_INT(work->pos.y) << 16)) <= TO_COORD(2)) {
            return;
        }
        if (abs(D_80145EC8 - (((s32)COORD_INT(work->pos.y) + 1) << 16)) <= TO_COORD(2)) {
            return;
        }
    }
advance:
    work->header.step++;
}
