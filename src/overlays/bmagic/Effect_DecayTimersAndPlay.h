/* Counts the effect work record's timer bytes 0x09 and 0x0A down while the tick byte 0x0B is under their
 * limits; once the top halfword of the word at 0x08 is zero it plays the effect the target selector chose
 * and raises the effect-playing flag. One definition shared by the bmagic effect modules; every change here
 * must verify every member. */
/* func_801EEEA8 (magic055), func_801EEEA8 (magic091) */
MATCH void Effect_DecayTimersAndPlay(void) {
    if (g_SpadWork->word_08.byte.unk_0B < 4u) {
        if (g_SpadWork->word_08.byte.unk_09 != 0) {
            g_SpadWork->word_08.byte.unk_09--;
        }
    }
    if (g_SpadWork->word_08.byte.unk_0B < 3u) {
        if (g_SpadWork->word_08.byte.unk_0A != 0) {
            g_SpadWork->word_08.byte.unk_0A--;
        }
    }
    if ((g_SpadWork->word_08.word & 0xFFFF0000u) == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}
