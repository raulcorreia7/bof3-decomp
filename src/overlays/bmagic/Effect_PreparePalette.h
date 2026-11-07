/* Prepares the selected battler palette. Every change must verify every member. */
MATCH void Effect_PreparePalette(void) {
    PartyBattler** selected;

    if (--g_Task->unk_09 == 0) {
        selected = &g_BattleSelectedActor;
        GFX_FreePaletteFadeTarget(*selected);
        g_Task->timer  = GFX_AllocPaletteFade(*selected, 0, 0, 0, 1);
        g_Task->unk_09 = 8;
        g_Task->header.mode++;
    }
}
