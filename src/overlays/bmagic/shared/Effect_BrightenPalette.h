MATCH void Effect_BrightenPalette(void) {
    g_PaletteFades[SELF(PartyMember)->timer].offset.r++;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g++;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b++;
    if (--SELF(PartyMember)->unk_09 == 0) {
        SELF(PartyMember)->header.mode++;
    }
}
