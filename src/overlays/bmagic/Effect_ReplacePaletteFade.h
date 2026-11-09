/* When the effect timer reaches zero, frees the selected actor's palette fade,
 * allocates a new one, stores its index in work byte 0x0A, restarts the timer at
 * 8 and advances the effect step. One definition shared by the bmagic effect
 * modules; every change here must verify every member. */
/* func_801EEEC0 (magic062), func_801EEF0C (magic082), func_801EEFA0 (magic162, magic168), func_801EEFA4 (magic070,
   magic071, magic072) */
MATCH void Effect_ReplacePaletteFade(void) {
    PartyMember* actor;

    actor = g_Battle.selected_actor;
    if (--g_Task->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(actor);
        g_Task->timer  = GFX_AllocPaletteFade((u8*)actor, 0, 0, 0, 1);
        g_Task->unk_09 = 8;
        g_Task->header.mode++;
    }
}
