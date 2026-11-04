/* When the effect timer reaches zero, frees the selected actor's palette fade,
 * allocates a new one, stores its index in work byte 0x0A, restarts the timer at
 * 8 and advances the effect step. One definition shared by the bmagic effect
 * modules; every change here must verify every member. */
/* func_801EEFA0 (magic162), func_801EEFA0 (magic168) */
MATCH void Effect_ReplacePaletteFade(void) {
    PartyBattler* actor;

    actor = g_BattleSelectedActor;
    if (--g_SpadWork->word_08.byte.unk_09 == 0) {
        GFX_FreePaletteFadeTarget(actor);
        g_SpadWork->word_08.byte.timer_0A = GFX_AllocPaletteFade((u8*)actor, 0, 0, 0, 1);
        g_SpadWork->word_08.byte.unk_09   = 8;
        g_SpadWork->step_01++;
    }
}
