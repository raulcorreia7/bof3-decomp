/* Records the current battle magic trail position. */
/* func_801F02A0 (magic044), func_801F02B0 (magic173) */
MATCH void Effect_RecordTrail(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(BMagic_Trail)
    BMagic_Trail[BMAGIC_WORK->unk_04][BMAGIC_WORK->param.unk_0B].vx = BMAGIC_WORK->screen_x.value;
    BMagic_Trail[BMAGIC_WORK->unk_04][BMAGIC_WORK->param.unk_0B].vy = BMAGIC_WORK->screen_y.value;
}
