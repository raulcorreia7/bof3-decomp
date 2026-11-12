/* Releases the battle effect target when the timer expires. */
/* func_801EF324 (magic097), func_801EF334 (magic098) */
MATCH void Effect_ReleaseTarget(void) {
    u8 count;

    g_Task->param.unk_0B += 1;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            Battle_MarkDamaged((g_Task->unk_03 + 3) & BYTE_MASK);
            GFX_FreePaletteFadeTarget(&g_BattleEnemyBattlers[g_Task->unk_03]);
            func_800AF814((g_Task->unk_03 + 3) & BYTE_MASK);
        } else {
            Battle_MarkDamaged(g_Task->unk_03);
            GFX_FreePaletteFadeTarget((EnemyBattler*)&g_Game.members[g_Task->unk_03]);
            func_800AF814(g_Task->unk_03);
        }
        g_Task->header.step += 1;
    }
}
