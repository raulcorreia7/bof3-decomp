/* Releases the battle effect target when the timer expires. */
/* func_801EF324 (magic097), func_801EF334 (magic098) */
MATCH void Effect_ReleaseTarget(void) {
    u8 count;

    BMAGIC_WORK->param.unk_0B += 1;
    count               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            Battle_MarkDamaged((BMAGIC_WORK->unk_03 + 3) & BYTE_MASK);
            GFX_PaletteFreeFadeTarget(&g_BattleEnemyBattlers[BMAGIC_WORK->unk_03]);
            Battle_FadePoisonedBattler((BMAGIC_WORK->unk_03 + 3) & BYTE_MASK);
        } else {
            Battle_MarkDamaged(BMAGIC_WORK->unk_03);
            GFX_PaletteFreeFadeTarget((EnemyBattler*)&g_Game.members[BMAGIC_WORK->unk_03]);
            Battle_FadePoisonedBattler(BMAGIC_WORK->unk_03);
        }
        BMAGIC_WORK->header.step += 1;
    }
}
