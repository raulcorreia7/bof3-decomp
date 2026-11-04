/* Claims the first free row of the effect slot table and returns its index,
 * or 0xFF when all BATTLE_EFFECT_COUNT rows are in use. One definition shared by
 * the bmagic effect modules; each image header names its table
 * BMAGIC_EFFECT_SLOTS. Every change here must verify every member. */
MATCH u32 BMagic_AllocEffect(void) {
    u8 index;

    for (index = 0u; index < BATTLE_EFFECT_COUNT; index++) {
        if ((BMAGIC_EFFECT_SLOTS[index].unk_00 & 1u) == 0u) {
            BMAGIC_EFFECT_SLOTS[index].unk_00 |= 1u;
            return index;
        }
    }
    return 0xFFu;
}
