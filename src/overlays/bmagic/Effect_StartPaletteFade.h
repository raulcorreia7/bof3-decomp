/* Selects the battler in g_Battle.selected_actor, runs its selection hook, stores the result in the effect ticker byte
   (work byte 0x0B), clears the effect timer (work byte 0x09) and advances the effect step (work byte 0x01). One
   definition shared by the bmagic effect modules; every change here must verify every member. */
MATCH void Effect_StartPaletteFade(void) {
    PartyMember** actor;

    actor = &g_Battle.selected_actor;
    GFX_FreePaletteFadeTarget(*actor);
    g_Task->param.unk_0B = GFX_AllocPaletteFade(*actor, 0, 0, 0, 1);
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
}
