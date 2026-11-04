/* Find the first row whose byte is zero in the area work window, or NULL. One
 * definition shared by the overlays that scan their own byte table; each
 * overlay's image header names its offset, stride and row count (SCRATCH_ROW_COUNT,
 * 16 when unset). Every change here must
 * verify every member address. */
/* func_801178C4 (area049), func_801F7FF8 (scena04), func_801F3158 (area052), func_801F3348 (area125), func_801F4D80 (area098) */
#ifndef SCRATCH_ROW_COUNT
#define SCRATCH_ROW_COUNT 16
#endif

MATCH u8* Area_FindFreeWorkRow(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK_WINDOW_ADDRESS);
    for (i = 0; i < SCRATCH_ROW_COUNT; i++) {
        if (p[SCRATCH_ROW_OFFSET] == 0) {
            return p;
        }
        p += SCRATCH_ROW_STRIDE;
    }
    return NULL;
}
