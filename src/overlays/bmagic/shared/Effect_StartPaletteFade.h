/* Selects the battler in g_Battle.selected_actor, runs its selection hook, stores the result in the effect ticker byte (work byte 0x0B), clears the effect timer (work byte 0x09) and advances the effect step (work byte 0x01). */
MATCH void Effect_StartPaletteFade(void) {
    PartyMember** actor;

    actor = &g_Battle.selected_actor;
    GFX_PaletteFreeFadeTarget(*actor);
    SELF(PartyMember)->param.unk_0B = GFX_PaletteAllocFade(*actor, 0, 0, 0, 1);
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
}
