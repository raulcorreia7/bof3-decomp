/* Raises the work counter at byte 0x09 and the timer at byte 0x0A each frame
 * and, when the counter reaches 0x19, sets the high bit of the active battler's
 * effect ticker byte and advances the effect state. One definition shared by
 * the bmagic effect modules; every change here must verify every member. */
/* func_801EF6A4 (magic144), func_801EF990 (magic092) */
MATCH void Effect_CountUpAndMarkBattler(void) {
    g_Task->unk_09 += 1;
    g_Task->timer += 1;
    if (g_Task->unk_09 == 0x19) {
        BATTLE_ACTIVE_WORK->unk_0B |= 0x80;
        g_Task->step += 1;
    }
}
