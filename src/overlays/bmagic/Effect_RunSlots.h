/* Runs the effect step the task mode selects, then runs every effect slot in use with g_BattleEffectBattler set to the battler of that slot. */
/* func_801EEC10 (magic220), func_801EEC10 (magic223), func_801EEC10 (magic226) */
MATCH void func_801EEC10(void) {
    Magic220SharedSteps handlers = D_801EEC04;
    PartyMember*        saved_task;
    PartyMember*        saved_battler;
    u8                  i;

    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].target.party;
            BMAGIC_EFFECT_SLOT_STEP();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}
