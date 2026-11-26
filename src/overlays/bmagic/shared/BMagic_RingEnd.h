/* Task mode 2: lowers the disc radius step while fewer than 4 rings are live and the shade level while fewer than 3; once the shade level and the live ring count (byte 0x0B) are zero marks the battlers damaged and resets the effect. */
/* func_801EEEA8 (magic055), func_801EEEA8 (magic091) */
MATCH void BMagic_RingEnd(void) {
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
