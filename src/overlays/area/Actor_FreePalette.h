/* Frees the palette slots owned by the running task. */
/* func_801F3BA4 (area085), func_801F2FD4 (area198) */
MATCH void Actor_FreePalette(void) {
    GFX_FreePaletteSlotOwner(g_Task);
}
