enum {
    BMAGIC_PALETTE_BRIGHTEN_FRAMES = 8
};

/* Prepares the selected battler palette. Every change must verify every member. */
MATCH void Effect_PreparePalette(void) {
    PartyMember** selected;

    if (--g_Task->unk_09 == 0) {
        selected = &g_BattleSelectedActor;
        GFX_FreePaletteFadeTarget(*selected);
        g_Task->timer  = GFX_AllocPaletteFade(*selected, 0, 0, 0, 1);
        g_Task->unk_09 = BMAGIC_PALETTE_BRIGHTEN_FRAMES;
        g_Task->header.mode++;
    }
}
