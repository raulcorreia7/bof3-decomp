/* Finishes the effect once its ticker (work byte 0x0B) is zero: the side mask
 * at work byte 0x04 goes to func_800A9820, the active battler's effect ticker
 * byte is lowered by one and the effect work is cleared. One definition shared
 * by the bmagic effect modules; every change here must verify every member. */
/* func_801EF2E4 (magic063), func_801EF2A0 (magic146) */
MATCH void Effect_FinishOnZeroTick(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800A9820(g_SpadWork->unk_04);
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}
