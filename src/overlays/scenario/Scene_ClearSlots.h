/* Clears the state byte of each of the 16 six-byte slots at SCENE_SLOT_BASE. One
 * definition shared by the two scenario effect overlays; each image header names
 * SCENE_SLOT_BASE. Every change here must verify every member. */
/* func_801D15B0 (sce15ef2), func_801D25C0 (sce15ef3) */
MATCH void Scene_ClearSlots(void) {
    s32 index;
    s8* cell;

    cell  = (s8*)SCENE_SLOT_BASE;
    index = 0;
    do {
        *cell = 0;
        index += 1;
        cell += 6;
    } while ((u32)(index & BYTE_MASK) < 0x10U);
}
