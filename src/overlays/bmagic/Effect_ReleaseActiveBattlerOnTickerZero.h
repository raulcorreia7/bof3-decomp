/* When the effect ticker runs down, advances the active battler's script step
 * (func_800AEF98), clears the battler's flag bit 0x40 and steps the handler.
 * Every change here must verify every member.
 */
/* func_801EEF68 (magic017), func_801EEF38 (magic021) */
MATCH void Effect_ReleaseActiveBattlerOnTickerZero(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        g_SpadWork->step_01 += 1;
    }
}
