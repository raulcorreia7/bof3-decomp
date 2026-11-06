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

/* The game's own sprite primitives are the PsyQ SDK's records: the panel icon
 * is an `SPRT_8` (the menu names it `MenuIconPrim` in menu/panel.h), written at
 * the primitive cursor `g_GfxPrimCursor`. */

/* The screen, in pixels. */
#define SCREEN_WIDTH                 320

/* retail addresses */
/* First primitive arena: bank n starts at this address + n * 0x9000. */
#define PRIM_ARENA_BASE              0x80028FCCu

/* Semi-transparent primitive: the PsyQ SetSemiTrans code bit, set. */
#define PSX_SET_SEMI_TRANSPARENT(p)  SetSemiTrans((p), 1)

/* Neutral full-brightness colour: 0x80 is the midpoint of each 5-bit channel. */
#define PSX_SET_NEUTRAL_RGB(p)       setRGB0((p), 128, 128, 128)

/* Begin a draw-mode primitive at the shared cursor with the default
 * texture window and no extra argument. */
#define GFX_SET_DRAW_MODE(tpage)     SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, (tpage), 0)

/* Draw one cue record's text at (x, y): the resource is the text bank. */
#define WinDrawCueText(x, y, cue)    UI_DrawText((x), (y), 0, 0xFF, Resource_GetText(cue))
/* Fixed-address accessor global. */
#define g_GraphicsPaletteDst         MEM_PTR(volatile u16, 0x80037800u)

/* The low nibble of a sprite cell's size byte indexes g_SpriteSizes. */
#define GFX_SPRITE_SIZE_MASK         0x0F

/* The texture page the 4-bit font sheets load into (@source: wiki:systems/rendering). */
#define FONT_TPAGE_X                 960
#define FONT_TPAGE_Y                 0

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
 * default texture window, primitive size 0xC. */
static inline void GFX_AddDrawMode(s32 tpage) {
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(1, 0xC);
}

/* Begin a semi-transparent, neutral-colour sprite at (x, y) on the shared
 * cursor and return it. */
static inline SPRT* GfxBeginSprite(s32 x, s32 y, u32 clut) {
    SPRT* sprt = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprt);
    PSX_SET_SEMI_TRANSPARENT(sprt);
    PSX_SET_NEUTRAL_RGB(sprt);
    sprt->x0   = x;
    sprt->y0   = y;
    sprt->clut = clut;
    return sprt;
}

#endif
