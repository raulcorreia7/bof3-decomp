/* Darkens the palette fade row indexed by the effect timer (work byte 0x0A) by one on each colour channel; when the effect ticker (work byte 0x09) reaches zero it frees the fade of the selected battler, tells the battle UI and advances the mode. */
/* func_801EF1A0 (magic162), func_801EF1A0 (magic168) */
MATCH void Effect_FadePaletteOut(void) {
    g_PaletteFades[SELF(PartyMember)->timer].offset.r--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b--;
    if (--SELF(PartyMember)->unk_09 == 0) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        SELF(PartyMember)->header.mode++;
    }
}
