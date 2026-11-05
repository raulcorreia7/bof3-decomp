/* Counts the work counter at byte 0x09 down; at zero the active battler's
 * effect ticker byte drops by one and the effect work record is cleared. One
 * definition shared by the bmagic effect modules; every change here must verify
 * every member. */
/* func_801F0134 (magic144), func_801F0420 (magic092) */
MATCH void Effect_CountDownCounterAndFinish(void) {
    u8 counter;

    counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if (!(counter & 0xFF)) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        g_SpadWork->flags_00 = 0;
        g_SpadWork->step_01  = 0;
        g_SpadWork->unk_02   = 0;
        g_SpadWork->unk_03   = 0;
        g_SpadWork->unk_04   = 0;
    }
}
