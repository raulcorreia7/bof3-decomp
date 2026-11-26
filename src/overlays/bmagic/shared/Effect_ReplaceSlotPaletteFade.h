/* When the effect timer reaches zero, frees the palette fade of the battler that slot byte 0x04 names (party slots first, then enemy slots), allocates a new one, stores its index in the timer, restarts the effect timer at 8 and advances the effect step. */
/* func_801EF2DC (magic073), func_801EF2C8 (magic074) */
MATCH void Effect_ReplaceSlotPaletteFade(void) {
    void* battler;
    u8    slot;
    u8    count;

    slot = SELF(PartyMember)->unk_04;
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[slot];
    } else {
        battler = &g_BattleEnemyBattlers[slot - BATTLE_PARTY_CHARACTERS_COUNT];
    }

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        GFX_PaletteFreeFadeTarget(battler);
        SELF(PartyMember)->timer  = GFX_PaletteAllocFade(battler, 0, 0, 0, 1);
        SELF(PartyMember)->unk_09 = 8;
        SELF(PartyMember)->header.step += 1;
    }
}
