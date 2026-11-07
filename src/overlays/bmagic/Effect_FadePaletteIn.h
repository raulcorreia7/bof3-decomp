/* Brightens the palette fade row indexed by the effect timer (work byte 0x0A)
 * by one on each colour channel; when the effect ticker (work byte 0x09)
 * reaches zero it advances the effect step. One definition shared by the
 * bmagic effect modules; every change here must verify every member. */
/* func_801EF3D4 (magic073), func_801EF3C0 (magic074) */
MATCH void Effect_FadePaletteIn(void) {
    D_80145BD6[g_Task->timer].red_offset++;
    D_80145BD6[g_Task->timer].green_offset++;
    D_80145BD6[g_Task->timer].blue_offset++;
    if (--g_Task->unk_09 == 0) {
        g_Task->header.step++;
    }
}
