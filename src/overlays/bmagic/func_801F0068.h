/* Clears the five bytes of the bmagic effect work array D_801F17B0. */
/* func_801F0068 (magic162), func_801F0068 (magic168) */
MATCH void func_801F0068(void) {
    D_801F17B0->header.flags = 0;
    D_801F17B0->header.mode  = 0;
    D_801F17B0->header.step  = 0;
    D_801F17B0->unk_03       = 0;
    D_801F17B0->unk_04       = 0;
}
