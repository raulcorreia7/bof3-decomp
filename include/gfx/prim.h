#ifndef GRAPHICS_PRIM_H
#define GRAPHICS_PRIM_H

#include "psx/mem.h"
#include "psx/psyq.h"
#include "types.h"
#include "engine/gfx/fade/fade.h"
#include "engine/gfx/prim/prim.h"

/* The shared primitive cursor and color packing used by the menu, field and effect drawers. */

/* A sprite rectangle in texture bytes: origin u, v and size w, h. */
typedef struct UvRect {
    u8 u;
    u8 v;
    u8 w;
    u8 h;
} UvRect;

ASSERT_SIZE(UvRect, 0x4);

/* A screen rectangle: the corner and the size. */
typedef union RectU16 {
    struct {
        u16 x;
        u16 y;
        u16 w;
        u16 h;
    } box;

    struct {
        s16 x;
        s16 y;
        u16 w;
        u16 h;
    } signed_box;
} RectU16;

ASSERT_SIZE(RectU16, 0x08);

/* The screen, in pixels. */
#define SCREEN_WIDTH                320
#define SCREEN_HEIGHT               240

/* retail addresses */
/* First primitive arena: bank n starts at this address + n * 0x9000. */
#define PRIM_ARENA_BASE             0x80028FCCu

/* Semi-transparent primitive: the PsyQ SetSemiTrans code bit, set. */
#define PSX_SET_SEMI_TRANSPARENT(p) SetSemiTrans((p), 1)

/* Neutral full-brightness colour: 0x80 is the midpoint of each 5-bit channel. */
#define PSX_SET_NEUTRAL_RGB(p)      setRGB0((p), 128, 128, 128)

/* Begin a draw-mode primitive at the shared cursor with the default
 * texture window and no extra argument. */
#define GFX_SET_DRAW_MODE(tpage)    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, (tpage), 0)

/* Draw one cue record's text at (x, y): the resource is the text bank. */
#define WinDrawCueText(x, y, cue)   UI_TextDraw((x), (y), 0, 0xFF, UI_MessageGetText(cue))
/* Fixed-address accessor global. */
#define g_GraphicsPaletteDst        MEM_PTR(volatile u16, 0x80037800u)

/* The low nibble of a sprite cell's size byte indexes g_SpriteSizes. */
#define GFX_SPRITE_SIZE_MASK        0x0F

/* The texture page the 4-bit font sheets load into (@source: wiki:systems/rendering). */
#define FONT_TPAGE_X                960
#define FONT_TPAGE_Y                0

/* GetTPage `tp`: the colour depth of the texture page (bits 7-8 of the page word; PsyQ manual: 4-bit CLUT, 8-bit CLUT, 15-bit direct). */
#define TPAGE_DEPTH_4BIT            0
#define TPAGE_DEPTH_8BIT            1
#define TPAGE_DEPTH_15BIT           2

/* GetTPage `abr`: the semi-transparency rate (bits 5-6 of the page word): B is the back pixel, F the primitive's. */
#define TPAGE_ABR_HALF              0 /* 0.5 B + 0.5 F */
#define TPAGE_ABR_ADD               1 /* B + F */
#define TPAGE_ABR_SUB               2 /* B - F */
#define TPAGE_ABR_QUARTER           3 /* B + 0.25 F */

/* The eight ordering-table layers of GFX_AddPrim: layer 7 is linked first and draws first (behind everything), layer 0 last
 * (in front). Proof: SYS_Main clears the table with ClearOTagR(work + 0x70, 8) and draws it from work + 0x8C, which is entry 7.
 * The layers named here are the ones whose content the callers show; the battle-magic family names 2, 3 and 5
 * relative to GFX_LAYER_BATTLE_SCENE (src/overlays/bmagic/bmagic.h). */
#define GFX_LAYER_COUNT             8
#define GFX_LAYER_TOP               0 /* the menu cursor and full-screen flashes */
#define GFX_LAYER_UI                1 /* text, windows and menu sprites */
#define GFX_LAYER_EFFECT_FRONT      2 /* screen effects and effect sprites in front of the scene */
#define GFX_LAYER_EFFECT            3 /* effect portraits, rings and quads over the scene */
#define GFX_LAYER_BATTLE_SCENE      4 /* g_AreaDrawMode while a battle runs (Game_BattleLoadPartySprites) */
#define GFX_LAYER_SCENE_BACK        5 /* scenery pieces and display moves behind the actors */
#define GFX_LAYER_FIELD_SCENE       6 /* g_AreaDrawMode in the field (Game_NewGame) */
#define GFX_LAYER_BACKDROP          7 /* gradients and map quads behind the scene */

/* A textured primitive's colour channel that leaves the texel unchanged (128 is 1.0 in the PSX modulation). */
#define GFX_COLOR_NEUTRAL           128

/* Color packing. */
#define PSX_COLOR_R(c)              ((u16)(c) & 0x1Fu)
#define PSX_COLOR_G(c)              (((u16)(c) >> 5) & 0x1Fu)
#define PSX_COLOR_B(c)              (((u16)(c) >> 10) & 0x1Fu)
/* The semi-transparency (STP) bit of a 15-bit colour word. */
#define PSX_COLOR_STP_BIT           0x8000

/* Shared primitive cursor (PsyQ SDK global, owned by the main exe). A named
 * symbol (not a fixed-address macro) so codegen emits the symbol-relative
 * `lui + lw reg, %lo(reg)` load the original binary uses. */
/* D_8014598C */
extern u8* g_GfxPrimCursor;
/* D_80145AD4 */
extern u8  g_UITextFormatBuffer[];

/* Queue a draw-mode primitive for the texture page at order-table slot 1: the default texture window. */
static inline void GFX_AddDrawMode(s32 tpage) {
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
}

/* The same draw mode with dithering on, at order-table slot `layer`. */
static inline void GFX_AddDitheredDrawMode(u32 layer, s32 tpage) {
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (tpage), 0);
    GFX_AddPrim(layer, sizeof(DR_MODE));
}

/* Queue a draw mode for the texture page `tpage` at order-table slot `layer`: the default texture window, dithering off. */
#define GFX_ADD_LAYER_DRAW_MODE(layer, tpage) \
    GFX_SET_DRAW_MODE(tpage);                 \
    GFX_AddPrim((layer), sizeof(DR_MODE))

/* The same draw mode at order-table slot 1. */
#define GFX_ADD_DRAW_MODE(tpage) GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_UI, tpage)

/* The same draw mode with dithering on. */
#define GFX_ADD_DITHERED_DRAW_MODE(layer, tpage)              \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (tpage), 0); \
    GFX_AddPrim((layer), sizeof(DR_MODE))

/* The shared cursor viewed as the primitive it is about to receive. */
/* Give all four vertices of a Gouraud quad one colour. */
#define GFX_SET_RGB_ALL(poly, r, g, b) \
    setRGB0(poly, r, g, b);            \
    setRGB1(poly, r, g, b);            \
    setRGB2(poly, r, g, b);            \
    setRGB3(poly, r, g, b)

#define GFX_CURSOR(type) ((type*)g_GfxPrimCursor)

/* Begin a semi-transparent, neutral-colour sprite at (x, y) on the shared cursor and return it. */
static inline SPRT* GfxBeginSprite(s32 x, s32 y, u32 clut) {
    SPRT* sprt = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprt);
    PSX_SET_SEMI_TRANSPARENT(sprt);
    setRGB0(sprt, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    setXY0(sprt, x, y);
    sprt->clut = clut;
    return sprt;
}

/* Begin a poly on the shared cursor, with semi-transparency `semi_trans`, and return it. */
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
