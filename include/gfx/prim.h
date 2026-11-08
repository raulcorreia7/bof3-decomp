#ifndef GRAPHICS_PRIM_H
#define GRAPHICS_PRIM_H

#include "psx/mem.h"
#include "psx/psyq.h"
#include "types.h"

/* The shared primitive cursor and color packing used by the menu, field and
 * effect drawers. */

/* A sprite rectangle in texture bytes: origin u, v and size w, h. The sprite
 * drawers copy it into a SPRT. */
typedef struct UvRect {
    u8 u;
    u8 v;
    u8 w;
    u8 h;
} UvRect;

ASSERT_SIZE(UvRect, 0x4);

/* The screen, in pixels. */
#define SCREEN_WIDTH                 320
#define SCREEN_HEIGHT                240

/* retail addresses */
/* First primitive arena: bank n starts at this address + n * 0x9000. */
#define PRIM_ARENA_BASE              0x80028FCCu

/* Begin a draw-mode primitive at the shared cursor with the default
 * texture window and no extra argument. */
#define GFX_SET_DRAW_MODE(tpage)     SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, (tpage), 0)

/* Draw one cue record's text at (x, y): the resource is the text bank. */
#define WinDrawCueText(x, y, cue)    UI_DrawText((x), (y), 0, 0xFF, Message_GetText(cue))
/* Fixed-address accessor global. */
#define g_GraphicsPaletteDst         MEM_PTR(volatile u16, 0x80037800u)

/* The low nibble of a sprite cell's size byte indexes g_SpriteSizes. */
#define GFX_SPRITE_SIZE_MASK         0x0F

/* The texture page the 4-bit font sheets load into (@source: wiki:systems/rendering). */
#define FONT_TPAGE_X                 960
#define FONT_TPAGE_Y                 0

/* A textured primitive's colour channel that leaves the texel unchanged (128 is 1.0 in the PSX modulation). */
#define GFX_COLOR_NEUTRAL            128

/* Color packing. */
#define PSX_COLOR_R(c)               ((u16)(c) & 0x1Fu)
#define PSX_COLOR_G(c)               (((u16)(c) >> 5) & 0x1Fu)
#define PSX_COLOR_B(c)               (((u16)(c) >> 10) & 0x1Fu)
#define PSX_COLOR_STP(c)             (((u16)(c) >> 15) & 1u)
#define PSX_PACK_COLOR(r, g, b, stp) ((u16)((r) | ((g) << 5) | ((b) << 10) | ((u16)(stp) << 15)))

/* Shared primitive cursor (PsyQ SDK global, owned by the main exe). A named
 * symbol (not a fixed-address macro) so codegen emits the symbol-relative
 * `lui + lw reg, %lo(reg)` load the original binary uses. */
/* D_8014598C */
extern u8* g_GfxPrimCursor;
/* D_80145AD4 */
extern u8  g_UiFormatBuffer[];

/* Queue a draw-mode primitive for the texture page at order-table slot 1: the
 * default texture window. */
static inline void GFX_AddDrawMode(s32 tpage) {
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(1, sizeof(DR_MODE));
}

/* The same draw mode with dithering on, at order-table slot `layer`. */
static inline void GFX_AddDitheredDrawMode(u32 layer, s32 tpage) {
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (tpage), 0);
    GFX_AddPrim(layer, sizeof(DR_MODE));
}

/* The shared cursor viewed as the primitive it is about to receive. */
/* The texture-page word getTPage builds, one macro per layout: GetGraphType() 1 and 2
 * keep the colour mode and blend in bits 9-10 and 7-8, the others in bits 7-8 and 5-6. */
#define GFX_TPAGE_STANDARD(tp, abr, x, y)                                                                             \
    ((((tp) & 0x3) << 7) | (((abr) & 0x3) << 5) | (((y) & 0x100) >> 4) | (((x) & 0x3FF) >> 6) | (((y) & 0x200) << 2))
#define GFX_TPAGE_GRAPH_TYPE_1_2(tp, abr, x, y)                                             \
    ((((tp) & 0x3) << 9) | (((abr) & 0x3) << 7) | (((y) >> 3) & 0x60) | (((x) >> 6) & 0xF))

#define GFX_CURSOR(type) ((type*)g_GfxPrimCursor)

/* Begin a semi-transparent, neutral-colour sprite at (x, y) on the shared
 * cursor and return it. */
static inline SPRT* GfxBeginSprite(s32 x, s32 y, u32 clut) {
    SPRT* sprt = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprt);
    SetSemiTrans(sprt, 1);
    setRGB0(sprt, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    setXY0(sprt, x, y);
    sprt->clut = clut;
    return sprt;
}

/* Begin a poly on the shared cursor, with semi-transparency `semi_trans`, and return it. The caller sets its
 * points, colours and texture, then queues it with GFX_AddPrim. */
static inline POLY_G3* GFX_BeginPolyG3(s32 semi_trans) {
    POLY_G3* prim = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(prim);
    SetSemiTrans(prim, semi_trans);
    return prim;
}

static inline POLY_G4* GFX_BeginPolyG4(s32 semi_trans) {
    POLY_G4* prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, semi_trans);
    return prim;
}

#endif
