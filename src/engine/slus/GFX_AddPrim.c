#include "engine/slus/slus.h"

/* appends the current primitive to one OT head and advances the
 * shared primitive cursor when the requested byte count still fits in the
 * active buffer.
 */
MATCH void GFX_AddPrim(u32 ot_index, u32 primitive_size) {
    u8* primitive;
    u8  size;

    primitive = g_GfxPrimCursor;
    size      = (u8)primitive_size;
    if ((u8*)(g_FrameBufferIndex * 0x9000 + PRIM_ARENA_BASE) > (primitive + size)) {
        ot_index &= BYTE_MASK;
        CatPrim(D_801459D0[ot_index], primitive);
        D_801459D0[ot_index] = (u32*)g_GfxPrimCursor;
        g_GfxPrimCursor += size;
    }
}
