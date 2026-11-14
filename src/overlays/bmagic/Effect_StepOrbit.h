/* Circles the effect around its battler, one turn every 64 frames, until its frames run out. */
/* func_801EF29C (magic106), func_801EF704 (magic063) */
MATCH void Effect_StepOrbit(void) {
    u8 timer;

    g_BMagicOrbit->angle       = (g_BMagicOrbit->angle + 0x40) & 0xFFF;
    g_BMagicOrbit->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(g_BMagicOrbit->angle) * g_BMagicOrbit->radius;
    g_BMagicOrbit->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos((s16)g_BMagicOrbit->angle) * g_BMagicOrbit->radius;
    g_BMagicOrbit->unk_0B++;
    if (g_BMagicOrbit->timer_05 < 12) {
        g_BMagicOrbit->timer_05++;
    }
    if (g_BMagicOrbit->timer_06 >= 5) {
        g_BMagicOrbit->timer_06--;
    }
    if (g_BMagicOrbit->timer_07 >= 5) {
        g_BMagicOrbit->timer_07--;
    }
    if (g_BMagicOrbit->unk_03 < 7) {
        g_BMagicOrbit->unk_03++;
    }
    timer                          = g_BMagicOrbit->frames_left - 1;
    g_BMagicOrbit->frames_left = timer;
    if (timer == 0) {
        g_BMagicOrbit->header.step++;
    }
}
