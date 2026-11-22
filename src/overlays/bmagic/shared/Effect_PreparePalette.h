enum {
    BMAGIC_PALETTE_BRIGHTEN_FRAMES = 8
};

/* Prepares the selected battler palette. */
MATCH void Effect_PreparePalette(void) {
    PartyMember** selected;

    if (--BMAGIC_WORK->unk_09 == 0) {
        selected = &g_Battle.selected_actor;
        GFX_PaletteFreeFadeTarget(*selected);
        BMAGIC_WORK->timer  = GFX_PaletteAllocFade(*selected, 0, 0, 0, 1);
        BMAGIC_WORK->unk_09 = BMAGIC_PALETTE_BRIGHTEN_FRAMES;
        BMAGIC_WORK->header.mode++;
    }
}
