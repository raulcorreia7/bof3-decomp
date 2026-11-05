/* When the effect ticker runs down, marks the selected battlers as damaged
 * (func_800A9820 with g_BattleTargetSelector) and steps the handler. Every
 * change here must verify every member.
 */
/* func_801EF05C (magic054), func_801EEE38 (magic103) */
MATCH void Effect_MarkTargetDamagedOnTickerZero(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_SpadWork->step_01 += 1;
    }
}
