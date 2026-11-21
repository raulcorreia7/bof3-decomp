/* Clears the five bytes of the bmagic effect work array D_801F17B4. */
/* func_801F006C (magic070), func_801F006C (magic071), func_801F006C (magic072) */
MATCH void func_801F006C(void) {
    D_801F17B4->header.flags = 0;
    D_801F17B4->header.mode  = 0;
    D_801F17B4->header.step  = 0;
    D_801F17B4->unk_03       = 0;
    D_801F17B4->unk_04       = 0;
}
