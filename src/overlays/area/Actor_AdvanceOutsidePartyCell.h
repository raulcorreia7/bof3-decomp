/* Advances the work state when the party position is outside the work cell. */
/* func_801F2FB0 (area147/13), func_801F3020 (area148/13), func_801F3F84 (area170/13) */
MATCH void Actor_AdvanceOutsidePartyCell(void) {
    Actor* work;

    work = g_Task;
    if (work->direction_08 != 0) {
        if (abs(g_Game.members[0].pos.y.fixed - ((((s32)COORD_INT(work->pos.y) + 1) << 16) | 0x8000)) > TO_COORD(2)) {
            goto advance;
        }
        if (abs(g_Game.members[0].pos.x.fixed - ((s32)COORD_INT(work->pos.x) << 16)) <= TO_COORD(2)) {
            return;
        }
        if (abs(g_Game.members[0].pos.x.fixed - (((s32)COORD_INT(work->pos.x) + 1) << 16)) <= TO_COORD(2)) {
            return;
        }
    } else {
        if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(work->pos.x) + 1) << 16) | 0x8000)) > TO_COORD(2)) {
            goto advance;
        }
        if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(work->pos.y) << 16)) <= TO_COORD(2)) {
            return;
        }
        if (abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(work->pos.y) + 1) << 16)) <= TO_COORD(2)) {
            return;
        }
    }
advance:
    work->header.step++;
}
