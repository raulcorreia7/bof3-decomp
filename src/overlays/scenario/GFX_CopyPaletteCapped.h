/* Copies the 16-colour palette at 0x80033800 to the palette upload buffer with
 * each 5-bit colour component limited to the low byte of its argument, sets
 * the semi-transparency bit on non-black colours and flags the upload. One
 * definition shared by the scenario overlays; every change here must verify
 * every member. */
/* func_801FB0B8 (scena13), func_801F83B0 (scena16) */
MATCH void GFX_CopyPaletteCapped(u32 intensity) {
    s32 component_index;
    /* FAKE: Pin merged accumulator to $a3. */
    MATCH_REG(u32, merged, "a3");
    u32                 packed;
    const u16*          src;
    s32                 color;
    u32                 dst_offset;
    u32                 limit;
    volatile const u16* src_end;
    u32                 scratch;
    u32                 value;

    intensity &= BYTE_MASK;
    limit      = intensity & HALF_MASK;
    dst_offset = 0u;
    src        = (const u16*)MEM_PTR(const volatile u16, 0x80033800u);
    src_end    = MEM_PTR(const volatile u16, 0x80033800u) + 0x10;
    do {
        packed          = 0u;
        component_index = 0;
        color           = *src;
        for (; component_index < 3; component_index++) {
            value = (u32)(color >> (component_index * 5)) & 0x1Fu;
            if (limit < value) {
                value = intensity;
            }
            scratch = packed << 5;
            merged  = scratch | value;
            packed  = merged;
        }
        /* The write target is g_GraphicsPaletteDst; the raw base keeps one
         * materialization, which the symbol macro does not reproduce. */
        scratch      = AREA_PALETTE_WORK;
        value        = dst_offset + scratch;
        *(u16*)value = (u16)packed;
        scratch      = packed & HALF_MASK;
        if (scratch != 0u) {
            scratch      = merged | 0x8000u;
            *(u16*)value = (u16)scratch;
        }
        src += 1;
        dst_offset += 2u;
    } while ((s32)src < (s32)src_end);
    g_GfxPalettePending = (u8)(g_GfxPalettePending + 1u);
}
