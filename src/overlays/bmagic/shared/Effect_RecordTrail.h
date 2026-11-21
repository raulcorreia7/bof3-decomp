/* Records the current battle magic trail position. */
/* func_801F02A0 (magic044), func_801F02B0 (magic173) */
MATCH void Effect_RecordTrail(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(BMagic_Trail)
    BMagic_Trail[g_Task->unk_04][g_Task->param.unk_0B].vx = g_Task->screen_x.value;
    BMagic_Trail[g_Task->unk_04][g_Task->param.unk_0B].vy = g_Task->screen_y.value;
}
