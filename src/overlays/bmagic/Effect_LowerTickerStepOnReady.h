/* Once func_8014DAEC reports its low byte set, lowers the active battler's
 * effect ticker (work byte 0x0B) and advances the effect step (work byte
 * 0x02). One definition shared by the bmagic effect modules; every change here
 * must verify every member. */
/* func_801EFA70 (magic004), func_801EF158 (magic161) */
MATCH void Effect_LowerTickerStepOnReady(void) {
    if (func_8014DAEC() & BYTE_MASK) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B--;
        g_SpadWork->unk_02++;
    }
}
