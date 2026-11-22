enum {
    BMAGIC_PALETTE_BRIGHTEN_FRAMES = 8
};

/* Prepares the selected battler palette. */
MATCH void Effect_PreparePalette(void) {
    PartyMember** selected;

    if (--TASK(PartyMember)->unk_09 == 0) {
        selected = &g_Battle.selected_actor;
        GFX_PaletteFreeFadeTarget(*selected);
        TASK(PartyMember)->timer  = GFX_PaletteAllocFade(*selected, 0, 0, 0, 1);
        TASK(PartyMember)->unk_09 = BMAGIC_PALETTE_BRIGHTEN_FRAMES;
        TASK(PartyMember)->header.mode++;
    }
}
