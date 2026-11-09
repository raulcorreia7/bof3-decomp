#include "area189_13.h"

MATCH void func_801F497C(u8 size) {
    u8* prim;

    prim = g_GfxPrimCursor;
    if ((u8*)(g_FrameBufferIndex * 0x9000 + PRIM_ARENA_BASE) > (prim + size)) {
        g_GfxPrimCursor = prim + size;
        setaddr(D_80143534[g_FrameBufferIndex + 4][0], prim);
        D_80143534[g_FrameBufferIndex + 4][0] = (u32*)prim;
    }
}
