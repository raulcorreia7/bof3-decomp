/* Frees the palette slots owned by the running task. One definition shared by the area overlays; every change here
 * must verify every member. */
/* func_801F3BA4 (area085), func_801F2FD4 (area198) */
MATCH void Actor_FreePalette(void) {
    GFX_FreePaletteSlotOwner(g_Task);
}
