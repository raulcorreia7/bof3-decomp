/* Finds the first empty 0x18 record in the 256-entry sprite work table at
 * 0x800E4800, or NULL. One definition shared by the area and scenario
 * overlays; every change here must verify every member.
 */
/* func_801F2D7C (area143), func_801D171C (sce15ef3) */
MATCH u8* Area_FindFreeSpriteRow(void) {
    u8* p;
    u16 i;

    p = MEM_PTR(u8, 0x800E4800);
    for (i = 0; i < 256; i++) {
        if (p[0] == 0) {
            return p;
        }
        p += 0x18;
    }
    return NULL;
}
