/* Clear the work reset flag, then hand the work pointer to the area step. */
/* func_801F2C30 (area036), func_801F2C34 (area146), func_801F2D5C (area059), func_801F2D80 (area116), func_801F35D4
   (area100), func_801F3638 (area112), func_801F3C40 (area143), func_801F4008 (area145) */
MATCH void Actor_RunAreaStep(void) {
    SELF(Actor)->unk_48 = 0;
    GFX_PaletteFreeFadeTarget(g_Self);
}
