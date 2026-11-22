MATCH void Effect_BrightenPalette(void) {
    g_PaletteFades[TASK(PartyMember)->timer].offset.r++;
    g_PaletteFades[TASK(PartyMember)->timer].offset.g++;
    g_PaletteFades[TASK(PartyMember)->timer].offset.b++;
    if (--TASK(PartyMember)->unk_09 == 0) {
        TASK(PartyMember)->header.mode++;
    }
}
