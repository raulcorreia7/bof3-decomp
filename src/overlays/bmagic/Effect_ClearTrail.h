/* Clears the current battle magic trail slot. */
/* func_801F0390 (magic044), func_801F03A0 (magic173) */
MATCH void Effect_ClearTrail(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(BMagic_Trail)
    BMagic_Trail[g_Task->unk_04][g_Task->param.unk_0B].x = -1;
    BMagic_Trail[g_Task->unk_04][g_Task->param.unk_0B].y = -1;
}
