/* Counts the effect timer (work byte 0x09) down; at zero it marks the battlers of the target selector damaged, raises the effect-playing flag and resets the effect. */
/* func_801EF0EC (magic054), func_801EF3D4 (magic113), func_801EF0BC (magic114) */
MATCH void Effect_CountDownAndMarkDamaged(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}
