/* Clears the five bytes of the bmagic effect work array D_801F17B0. One
 * definition shared by the bmagic overlays; every change here must verify
 * every member. */
/* func_801F0068 (magic162), func_801F0068 (magic168) */
MATCH void func_801F0068(void) {
    D_801F17B0->flags  = 0;
    D_801F17B0->mode   = 0;
    D_801F17B0->step   = 0;
    D_801F17B0->unk_03 = 0;
    D_801F17B0->unk_04 = 0;
}
