/* Runs the effect step the task mode selects, then runs every sparkle in use,
 * with D_801EB4E0 set to the battler of that sparkle. One definition shared by
 * the bmagic overlays; every change here must verify every member. */
/* func_801EEC28 (magic070), func_801EEC28 (magic071), func_801EEC28 (magic072) */
MATCH void func_801EEC28(void) {
    BMagicEffectFuncs handlers;
    PartyBattler*     active;
    u8                i;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC04, header.mode);
    for (i = 0; i < EFFECT_SPARKLE_COUNT; i++) {
        if (D_801F01B4[i].header.flags & 1) {
            active     = D_801EB4E0;
            D_801F17B4 = &D_801F01B4[i];
            D_801EB4E0 = D_801F01B4[i].battler;
            func_801EF33C();
            D_801EB4E0 = active;
        }
    }
}
