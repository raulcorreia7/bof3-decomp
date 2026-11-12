/* Starts the effect's next orbit once its delay runs out. */
/* func_801EEFAC (magic106), func_801EF40C (magic063) */
MATCH void Effect_StartOrbit(void) {
    u8 phase;

    if (--g_BMagicOrbitWork->unk_0A == 0) {
        D_1F800000.view.effect.params[0] = (g_BMagicOrbitWork->unk_04 >> 5) * 16 + 0x60;
        phase                            = g_BMagicOrbitWork->unk_04 & 0x1F;
        D_1F800000.view.effect.params[2] = phase << 7;
        g_BMagicOrbitWork->pos.x.fixed   = g_BattleEffectBattler->pos.x.fixed + rsin(phase << 7) * D_1F800000.view.effect.params[0];
        g_BMagicOrbitWork->pos.y.fixed   = g_BattleEffectBattler->pos.y.fixed + rcos(D_1F800000.view.effect.params[2]) * D_1F800000.view.effect.params[0];
        g_BMagicOrbitWork->pos.z.fixed   = g_BattleEffectBattler->pos.z.fixed;
        g_BMagicOrbitWork->angle         = D_1F800000.view.effect.params[2];
        g_BMagicOrbitWork->timer_05      = (rand() & 7) + 5;
        g_BMagicOrbitWork->timer_06      = (rand() & 7) + 5;
        g_BMagicOrbitWork->timer_07      = (rand() & 7) + 5;
        g_BMagicOrbitWork->unk_03        = 0;
        g_BMagicOrbitWork->unk_09        = 0;
        g_BMagicOrbitWork->unk_0A        = (rand() & 3) << 3;
        g_BMagicOrbitWork->unk_0B        = rand();
        g_BMagicOrbitWork->radius        = D_1F800000.view.effect.params[0];
        g_BMagicOrbitWork->header.step++;
    }
}
