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
    u8* work;

    work = SP_REF(u8*, 0x44);
    if (FIELD(u8, work, 0x08) != 0) {
        if (abs(D_80145EC8 - ((((s32)FIELD(s16, work, 0x3A) + 1) << 16) | 0x8000)) > 0x20000) {
            goto advance;
        }
        if (abs(D_80145EC4 - ((s32)FIELD(s16, work, 0x36) << 16)) <= 0x20000) {
            return;
        }
        if (abs(D_80145EC4 - (((s32)FIELD(s16, work, 0x36) + 1) << 16)) <= 0x20000) {
            return;
        }
    } else {
        if (abs(D_80145EC4 - ((((s32)FIELD(s16, work, 0x36) + 1) << 16) | 0x8000)) > 0x20000) {
            goto advance;
        }
        if (abs(D_80145EC8 - ((s32)FIELD(s16, work, 0x3A) << 16)) <= 0x20000) {
            return;
        }
        if (abs(D_80145EC8 - (((s32)FIELD(s16, work, 0x3A) + 1) << 16)) <= 0x20000) {
            return;
        }
    }
advance:
    FIELD(u8, work, 0x02)++;
}
