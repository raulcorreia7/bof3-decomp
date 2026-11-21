/* Fades the palette of the poisoned battler and advances the step when the counter ends; verify every image after a change. */
MATCH void Effect_FadePoisonedBattlerPalette(void) {
    u8           unk04;
    PartyMember* battler;

    unk04 = g_Task->unk_04;
    if (unk04 < 3) {
        battler = &g_Game.members[unk04];
    } else {
        battler = (PartyMember*)((EnemyBattler*)g_BattleEnemies + unk04);
    }
    g_PaletteFades[g_Task->timer].offset.r--;
    g_PaletteFades[g_Task->timer].offset.g--;
    g_PaletteFades[g_Task->timer].offset.b--;
    if (--g_Task->unk_09 == 0) {
        func_80196718(battler);
        Battle_FadePoisonedBattler(g_Task->unk_04);
        g_Task->header.step++;
    }
}
