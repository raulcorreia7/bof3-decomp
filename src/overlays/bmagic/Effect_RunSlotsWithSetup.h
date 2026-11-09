/* Runs the effect step the task mode selects (the setup step, then the image's start handler), then
 * runs every effect slot in use with g_BattleEffectBattler set to the battler of that slot. One
 * definition shared by the bmagic overlays; every change here must verify every member. */
/* func_801EEC04 (magic083), func_801EEC04 (magic087), func_801EEC04 (magic093), func_801EEC04 (magic158),
   func_801EEC04 (magic213) */
MATCH void func_801EEC04(void) {
    Callback     handlers[2] = {func_801EED04, BMAGIC_EFFECT_START_HANDLER};
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    SYS_DISPATCH_BYTE(handlers, g_Task->header.mode);

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
