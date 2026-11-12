/* Counts the effect work record's timer bytes 0x09 and 0x0A down while the tick byte 0x0B is under their limits; once the top halfword of the word at 0x08 is zero it plays the effect the target selector chose and raises the effect-playing flag. */
/* func_801EEEA8 (magic055), func_801EEEA8 (magic091) */
MATCH void Effect_DecayTimersAndPlay(void) {
    if (g_Task->param.unk_0B < 4u) {
        if (g_Task->unk_09 != 0) {
            g_Task->unk_09--;
        }
    }
    if (g_Task->param.unk_0B < 3u) {
        if (g_Task->timer != 0) {
            g_Task->timer--;
        }
    }
    if ((PARTY_MEMBER_WORD_08(g_Task) & 0xFFFF0000u) == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}
