/* Releases the battle effect target when the timer expires. */
/* func_801EF324 (magic097), func_801EF334 (magic098) */
MATCH void Effect_ReleaseTarget(void) {
    u8 count;

    SELF(PartyMember)->param.unk_0B += 1;
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            Battle_MarkDamaged((SELF(PartyMember)->unk_03 + 3) & BYTE_MASK);
            GFX_PaletteFreeFadeTarget(&g_BattleEnemyBattlers[SELF(PartyMember)->unk_03]);
            Battle_FadePoisonedBattler((SELF(PartyMember)->unk_03 + 3) & BYTE_MASK);
        } else {
            Battle_MarkDamaged(SELF(PartyMember)->unk_03);
            GFX_PaletteFreeFadeTarget((EnemyBattler*)&g_Game.members[SELF(PartyMember)->unk_03]);
            Battle_FadePoisonedBattler(SELF(PartyMember)->unk_03);
        }
        SELF(PartyMember)->header.step += 1;
    }
}
