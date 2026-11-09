/* Records the current battle magic trail position. One definition shared by the bmagic overlays;
 * every change here must verify every member. */
/* func_801F02A0 (magic044), func_801F02B0 (magic173) */
MATCH void Effect_RecordTrail(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(BMagic_Trail)
    BMagic_Trail[g_Task->unk_04][g_Task->param.unk_0B].x = g_Task->unk_2E.half;
    BMagic_Trail[g_Task->unk_04][g_Task->param.unk_0B].y = g_Task->unk_30.half;
}
