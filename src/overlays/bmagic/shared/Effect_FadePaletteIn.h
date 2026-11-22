/* Brightens the palette fade row indexed by the effect timer (work byte 0x0A) by one on each colour channel; when the effect ticker (work byte 0x09) reaches zero it advances the effect step. */
/* func_801EF3D4 (magic073), func_801EF3C0 (magic074) */
MATCH void Effect_FadePaletteIn(void) {
    g_PaletteFades[TASK(PartyMember)->timer].offset.r++;
    g_PaletteFades[TASK(PartyMember)->timer].offset.g++;
    g_PaletteFades[TASK(PartyMember)->timer].offset.b++;
    if (--TASK(PartyMember)->unk_09 == 0) {
        TASK(PartyMember)->header.step++;
    }
}
