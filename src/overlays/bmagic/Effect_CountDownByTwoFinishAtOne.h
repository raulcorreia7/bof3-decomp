/* Counts the work counter at byte 0x09 down by 2 and raises the timer at byte
 * 0x0A on odd frames; when the counter reaches 1 the active battler's effect
 * ticker byte drops by one and the effect work record is cleared. One
 * definition shared by the bmagic effect modules; every change here must verify
 * every member. */
/* func_801EF738 (magic144), func_801EFA24 (magic092) */
MATCH void Effect_CountDownByTwoFinishAtOne(void) {
    g_SpadWork->word_08.byte.unk_09 -= 2;
    if (g_FrameCount & 1) {
        g_SpadWork->word_08.byte.timer_0A += 1;
    }
    if (g_SpadWork->word_08.byte.unk_09 == 1) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        g_SpadWork->flags_00 = 0;
        g_SpadWork->step_01  = 0;
        g_SpadWork->unk_02   = 0;
        g_SpadWork->unk_03   = 0;
        g_SpadWork->unk_04   = 0;
    }
}
