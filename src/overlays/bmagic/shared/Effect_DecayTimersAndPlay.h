/* Counts the effect work record's timer bytes 0x09 and 0x0A down while the tick byte 0x0B is under their limits; once the top halfword of the word at 0x08 is zero it plays the effect the target selector chose and raises the effect-playing flag. */
/* func_801EEEA8 (magic055), func_801EEEA8 (magic091) */
MATCH void Effect_DecayTimersAndPlay(void) {
    if (TASK(PartyMember)->param.unk_0B < 4u) {
        if (TASK(PartyMember)->unk_09 != 0) {
            TASK(PartyMember)->unk_09--;
        }
    }
    if (TASK(PartyMember)->param.unk_0B < 3u) {
        if (TASK(PartyMember)->timer != 0) {
            TASK(PartyMember)->timer--;
        }
    }
    if ((PARTY_MEMBER_WORD_08(TASK(PartyMember)) & 0xFFFF0000u) == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}
