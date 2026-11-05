#include "start_08.h"

/* Icon geometry: five u16 fields per icon, a 10-byte stride. The original
 * reads each field through its own symbol-relative lui/addu/lhu, so the five
 * symbol bindings stay separate; a single struct base would materialize one
 * register and change the addressing. */
#define START08_ICON_STRIDE 10u

MATCH void func_801E7514(s32 x, s32 y, s32 icon, s32 palette) {
    SPRT* sprite;
    u32   geom;

    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    sprite->r0   = 0x20;
    sprite->g0   = 0x20;
    sprite->b0   = 0x20;
    geom         = (u8)icon * START08_ICON_STRIDE;
    sprite->x0   = x;
    sprite->y0   = y;
    sprite->u0   = (u8) * (u16*)((u8*)D_801ED1FC + geom);
    sprite->v0   = (u8) * (u16*)((u8*)D_801ED1FE + geom);
    sprite->w    = *(u16*)((u8*)D_801ED200 + geom);
    sprite->h    = *(u16*)((u8*)D_801ED202 + geom);
    sprite->clut = (u16)(*(u16*)((u8*)D_801ED204 + geom) << 6);
    GFX_AddPrim((u8)palette, 20);
}
