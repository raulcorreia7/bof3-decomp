/* When the effect timer reaches zero, frees the selected actor's palette fade, allocates a new one, stores its index in work byte 0x0A, restarts the timer at 8 and advances the effect step. */
/* func_801EEEC0 (magic062), func_801EEF0C (magic082), func_801EEFA0 (magic162, magic168), func_801EEFA4 (magic070,
   magic071, magic072) */
MATCH void Effect_ReplacePaletteFade(void) {
    PartyMember* actor;

    actor = g_Battle.selected_actor;
    if (--SELF(PartyMember)->unk_09 == 0) {
        GFX_PaletteFreeFadeTarget(actor);
        SELF(PartyMember)->timer  = GFX_PaletteAllocFade((u8*)actor, 0, 0, 0, 1);
        SELF(PartyMember)->unk_09 = 8;
        SELF(PartyMember)->header.mode++;
    }
}
