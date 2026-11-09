/* Turns the orbiting effect one step around its battler and ages its timers. One definition shared by the bmagic
 * effect modules; every change here must verify every member. */
/* func_801EF29C (magic106), func_801EF704 (magic063) */
MATCH void Effect_StepOrbit(void) {
    u8 timer;

    g_BMagicOrbitWork->angle = (g_BMagicOrbitWork->angle + 0x40) & 0xFFF;
    g_BMagicOrbitWork->unk_10 =
        g_BattleEffectBattler->pos.x.fixed + rsin(g_BMagicOrbitWork->angle) * g_BMagicOrbitWork->radius;
    g_BMagicOrbitWork->unk_14 =
        g_BattleEffectBattler->pos.y.fixed + rcos((s16)g_BMagicOrbitWork->angle) * g_BMagicOrbitWork->radius;
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
    timer                       = g_BMagicOrbitWork->timer_08 - 1;
    g_BMagicOrbitWork->timer_08 = timer;
    if (timer == 0) {
        g_BMagicOrbitWork->header.step++;
    }
}
