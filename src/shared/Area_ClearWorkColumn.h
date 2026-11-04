/* Clear one byte of each row in the area work window. One definition shared by
 * the overlays that reset their own byte table; each overlay's image header
 * names its offset, stride and row count. Every change here must verify every
 * member address. */
/* func_801F3384 (area125), func_801F38BC (area172), func_801F3DB4 (area188), func_801F4974 (area134), func_801F5240 (area098), func_801F75AC (scena15), func_801F7AB8 (scena01) */
MATCH void Area_ClearWorkColumn(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK);
    i = 0;
    do {
        p[SCRATCH_COLUMN_OFFSET] = 0;
        i++;
        p += SCRATCH_COLUMN_STRIDE;
    } while (i < SCRATCH_COLUMN_COUNT);
}
