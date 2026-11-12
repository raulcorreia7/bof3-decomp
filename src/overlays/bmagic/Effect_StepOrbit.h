/* Circles the effect around its battler, one turn every 64 frames, until its frames run out. */
/* func_801EF29C (magic106), func_801EF704 (magic063) */
MATCH void Effect_StepOrbit(void) {
    u8 timer;

    g_BMagicOrbitWork->angle       = (g_BMagicOrbitWork->angle + 0x40) & 0xFFF;
    g_BMagicOrbitWork->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(g_BMagicOrbitWork->angle) * g_BMagicOrbitWork->radius;
    g_BMagicOrbitWork->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos((s16)g_BMagicOrbitWork->angle) * g_BMagicOrbitWork->radius;
    g_BMagicOrbitWork->unk_0B++;
    if (g_BMagicOrbitWork->timer_05 < 12) {
        g_BMagicOrbitWork->timer_05++;
    }
    if (g_BMagicOrbitWork->timer_06 >= 5) {
        g_BMagicOrbitWork->timer_06--;
    }
    if (g_BMagicOrbitWork->timer_07 >= 5) {
        g_BMagicOrbitWork->timer_07--;
    }
    if (g_BMagicOrbitWork->unk_03 < 7) {
        g_BMagicOrbitWork->unk_03++;
    }
    timer                          = g_BMagicOrbitWork->frames_left - 1;
    g_BMagicOrbitWork->frames_left = timer;
    if (timer == 0) {
        g_BMagicOrbitWork->header.step++;
    }
}
