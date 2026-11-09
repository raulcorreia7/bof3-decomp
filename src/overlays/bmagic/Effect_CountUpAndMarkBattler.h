/* Raises the work counter at byte 0x09 and the timer at byte 0x0A each frame and. */
/* func_801EF6A4 (magic144), func_801EF990 (magic092) */
MATCH void Effect_CountUpAndMarkBattler(void) {
    g_Task->unk_09 += 1;
    g_Task->timer += 1;
    if (g_Task->unk_09 == 0x19) {
        BATTLE_ACTIVE_WORK->param.unk_0B |= 0x80;
        g_Task->header.step += 1;
    }
}
