/* The module entry: runs the task step that header.mode selects from g_BMagicSparkleModes, then steps every sparkle in use with g_BattleEffectBattler set to that sparkle's battler. */
/* func_801EEC28 (magic070), func_801EEC28 (magic071), func_801EEC28 (magic072) */
MATCH void BMagic_SparkleUpdate(void) {
    BMagicEffectSteps handlers;
    PartyMember*      active;
    u8                i;

    BMAGIC_DISPATCH_STEP_HANDLERS(g_BMagicSparkleModes, header.mode);
    for (i = 0; i < EFFECT_SPARKLE_COUNT; i++) {
        if (g_BMagicSparkles[i].header.flags & EFFECT_SPARKLE_IN_USE) {
            active                = g_BattleEffectBattler;
            g_BMagicSparkle       = &g_BMagicSparkles[i];
            g_BattleEffectBattler = g_BMagicSparkles[i].battler;
            Effect_SparkleRunMode();
            g_BattleEffectBattler = active;
        }
    }
}
