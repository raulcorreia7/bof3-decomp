/* Releases the battle effect target when the timer expires. */
/* func_801EF324 (magic097), func_801EF334 (magic098) */
MATCH void Effect_ReleaseTarget(void) {
    u8 count;

    TASK(PartyMember)->param.unk_0B += 1;
    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            Battle_MarkDamaged((TASK(PartyMember)->unk_03 + 3) & BYTE_MASK);
            GFX_PaletteFreeFadeTarget(&g_BattleEnemyBattlers[TASK(PartyMember)->unk_03]);
            Battle_FadePoisonedBattler((TASK(PartyMember)->unk_03 + 3) & BYTE_MASK);
        } else {
            Battle_MarkDamaged(TASK(PartyMember)->unk_03);
            GFX_PaletteFreeFadeTarget((EnemyBattler*)&g_Game.members[TASK(PartyMember)->unk_03]);
            Battle_FadePoisonedBattler(TASK(PartyMember)->unk_03);
        }
        TASK(PartyMember)->header.step += 1;
    }
}
