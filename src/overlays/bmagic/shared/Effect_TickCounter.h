/* Counts the work counter at byte 0x09 down; at zero the active battler's effect ticker byte drops by one and the effect work record is cleared. */
/* func_801F0134 (magic144), func_801F0420 (magic092) */
MATCH void Effect_TickCounter(void) {
    u8 counter;

    counter        = g_Task->unk_09 - 1;
    g_Task->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        g_Task->header.flags = 0;
        g_Task->header.mode  = 0;
        g_Task->header.step  = 0;
        g_Task->unk_03       = 0;
        g_Task->unk_04       = 0;
    }
}
