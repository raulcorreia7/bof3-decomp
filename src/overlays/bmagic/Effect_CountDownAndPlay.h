/* Counts the effect timer (work byte 0x09) down; at zero it plays the effect the
 * target selector chose and raises the effect-playing flag. One definition
 * shared by the bmagic effect modules; every change here must verify every member. */
/* func_801EF0EC (magic054), func_801EF3D4 (magic113), func_801EF0BC (magic114) */
MATCH void Effect_CountDownAndPlay(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}
