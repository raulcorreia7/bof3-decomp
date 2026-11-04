/* Plays the effect the target selector chose once the effect ticker (work byte
 * 0x0B) holds its 0xFF idle value. One definition shared by the bmagic effect
 * modules; every change here must verify every member. */
/* func_801EEE5C (magic066), func_801EEE84 (magic078), func_801EF168 (magic086), func_801EED40 (magic107), func_801EED1C (magic108), func_801EEFB0 (magic120), func_801EEE08 (magic121), func_801EEDFC (magic122) */
MATCH void Effect_PlayOnIdleTick(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0xFF) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}
