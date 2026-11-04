/* Claims the first free slot of the 16 six-byte slots at SCENE_SLOT_BASE: its
 * state byte becomes 1 and its countdown halfword at +2 is cleared. One definition
 * shared by the two scenario effect overlays; each image header names
 * SCENE_SLOT_BASE. Every change here must verify every member. */
/* func_801D15DC (sce15ef2), func_801D25EC (sce15ef3) */
MATCH void Scene_ClaimSlot(void) {
    s32 index;
    u8* slot;

    slot  = (u8*)SCENE_SLOT_BASE;
    index = 0;
    do {
        if (*slot == 0) {
            *slot   = 1;
            slot[2] = 0;
            return;
        }
        index += 1;
        slot += 6;
    } while ((u32)(index & BYTE_MASK) < 0x10U);
}
