/* When the effect timer reaches zero, frees the palette fade of the battler that slot byte 0x04 names (party slots first. */
/* func_801EF2DC (magic073), func_801EF2C8 (magic074) */
MATCH void Effect_ReplaceSlotPaletteFade(void) {
    void* battler;
    u8    slot;
    u8    count;

    slot = g_Task->unk_04;
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[slot];
    } else {
        battler = &g_BattleEnemyBattlers[slot - BATTLE_PARTY_CHARACTERS_COUNT];
    }

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}
