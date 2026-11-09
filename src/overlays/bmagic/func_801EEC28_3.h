/* Runs the effect step the task mode selects. */
/* func_801EEC28 (magic162), func_801EEC28 (magic168) */
MATCH void func_801EEC28(void) {
    BMagicEffectFuncs handlers;
    PartyMember*      active;
    u8                i;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC04, header.mode);
    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            active                = g_BattleEffectBattler;
            D_801F17B0            = &BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].battler;
            func_801EF338();
            g_BattleEffectBattler = active;
        }
    }
}
