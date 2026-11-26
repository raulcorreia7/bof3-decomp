/* The module entry: runs the task step that header.mode selects from g_BMagicSparkleModes, then steps every sparkle in use with g_BattleEffectBattler set to that sparkle's battler. */
/* func_801EEC28 (magic162), func_801EEC28 (magic168) */
MATCH void BMagic_SparkleUpdate(void) {
    BMagicEffectSteps handlers;
    PartyMember*      active;
    u8                i;

    BMAGIC_DISPATCH_STEP_HANDLERS(g_BMagicSparkleModes, header.mode);
    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            active                = g_BattleEffectBattler;
            g_BMagicSparkle       = &BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].battler;
            Effect_SparkleRunMode();
            g_BattleEffectBattler = active;
        }
    }
}
