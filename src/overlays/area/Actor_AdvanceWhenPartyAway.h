/* Advance the work state when the party position is outside the work cell:
 * the first axis alone, or both checks of the second axis. One definition
 * shared by the world area overlays; the cell is whole-cell fixed point in the
 * scratch work and the party position is D_80145EC4/D_80145EC8. Each overlay
 * includes this file where the function sits.
 */
/* func_801F2F54 (area158), func_801F2F54 (area160), func_801F2F54 (area161), func_801F2F54 (area162), func_801F2F54
   (area163), func_801F2F54 (area164), func_801F2F54 (area165), func_801F2F54 (area166), func_801F2F68 (area169),
   func_801F2F88 (area157), func_801F303C (area167), func_801F3794 (area168), func_801F37D8 (area174), func_801F3E04
   (area139) */
MATCH void Actor_AdvanceWhenPartyAway(void) {
    u8* work;

    work = TASK_BYTES;
    if (FIELD(u8, work, 0x08) != 0) {
        if (abs(D_80145EC8 - ((((s32)FIELD(s16, work, 0x3A) + 1) << 16) | 0x8000)) > TO_COORD(2)) {
            goto advance;
        }
        if (abs(D_80145EC4 - ((s32)FIELD(s16, work, 0x36) << 16)) <= TO_COORD(2)) {
            goto call;
        }
        if (abs(D_80145EC4 - (((s32)FIELD(s16, work, 0x36) + 1) << 16)) <= TO_COORD(2)) {
            goto call;
        }
    } else {
        if (abs(D_80145EC4 - ((((s32)FIELD(s16, work, 0x36) + 1) << 16) | 0x8000)) > TO_COORD(2)) {
            goto advance;
        }
        if (abs(D_80145EC8 - ((s32)FIELD(s16, work, 0x3A) << 16)) <= TO_COORD(2)) {
            goto call;
        }
        if (abs(D_80145EC8 - (((s32)FIELD(s16, work, 0x3A) + 1) << 16)) <= TO_COORD(2)) {
            goto call;
        }
    }
advance:
    FIELD(u8, work, 0x02)++;
call:
    Area_Update();
}
