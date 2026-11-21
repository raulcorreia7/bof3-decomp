#ifndef OVERLAY_GFX_PRIM_H
#define OVERLAY_GFX_PRIM_H

#include "types.h"

/* func_8014E564 */
void GFX_ClearRect(s16 x, s16 y, s16 width, s16 height);
/* func_8014E5A0 */
void GFX_AddPrim(u32 ot_index, u32 primitive_size);
/* func_8014E6D0 */
void GFX_UpdateTransferQueue(void);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_GFX_PRIM_H_LOCAL)
#define OVERLAY_GFX_PRIM_H_LOCAL

void        GFX_DrawLine(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b, s32 blend);
extern void GFX_ExpandRgb555(u32* pixels, RECT rect);
extern void GFX_DecodeLzss(u32* packed, RECT rect);

#endif
