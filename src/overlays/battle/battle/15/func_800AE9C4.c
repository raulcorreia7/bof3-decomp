#include "common/vector.h"
#include "battle_15.h"

/* The panel geometry the draw code reads: the origin x and y place the quad
 * on screen and the height is the quad's row count. */
typedef struct BattlePanelGeometry {
    u8       pad_00[0x0A];
    u8       height;
    u8       pad_0B[0x23];
    Point2u origin;
} BattlePanelGeometry;

ASSERT_SIZE(BattlePanelGeometry, 0x32);
ASSERT_OFFSET(BattlePanelGeometry, height, 0x0A);
ASSERT_OFFSET(BattlePanelGeometry, origin, 0x2E);

/* Each panel texture entry is four bytes: the u pair then the v pair. */
#define BATTLE_PANEL_TEX_STRIDE 4

/* The panel quad is 0x30 pixels wide. */
#define BATTLE_PANEL_WIDTH      0x30
/* The texture page and the clut the panel quads share. */
#define BATTLE_PANEL_TPAGE_X    0x380
#define BATTLE_PANEL_TPAGE_Y    0x100
#define BATTLE_PANEL_CLUT_X     0x10
#define BATTLE_PANEL_CLUT_Y     (STAGE_PALETTE_Y + 26)
/* The draw mode's texture window: the lit and the dim panel palette. */
#define BATTLE_PANEL_MODE_LIT   0x25
#define BATTLE_PANEL_MODE_DIM   0x15

/* Draws the two panel quads at the active battle-work origin, one normal and one dark. */
MATCH void func_800AE9C4(u8 texture_index) {
    POLY_FT4*            primitive;
    u32                  tex_offset;
    s32                  mode;
    BattlePanelGeometry* panel;
    /* The second quad reads the work record again, the way the retail code does. */
    BattlePanelGeometry* panel2;

    if (GetGraphType() == 1) {
        mode = BATTLE_PANEL_MODE_LIT;
    } else {
        if (GetGraphType() == 2) {
            mode = BATTLE_PANEL_MODE_LIT;
        } else {
            mode = BATTLE_PANEL_MODE_DIM;
        }
    }
    GFX_AddDitheredDrawMode(2, mode);
    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    panel = (BattlePanelGeometry*)BATTLE_WORK;
    setXY4(primitive, panel->origin.x + 1, panel->origin.y + 1, panel->origin.x + 49, panel->origin.y + 1, panel->origin.x + 1, panel->origin.y + (panel->height + 1), panel->origin.x + 0x31,
           panel->origin.y + (panel->height + 1));
    primitive->tpage = GetTPage(0, 0, BATTLE_PANEL_TPAGE_X, BATTLE_PANEL_TPAGE_Y);
    setClut(primitive, BATTLE_PANEL_CLUT_X, BATTLE_PANEL_CLUT_Y);
    /* The texture entry is read through the table symbol at every use: the retail
     * code materializes the table address again for each access. */
    tex_offset = texture_index * BATTLE_PANEL_TEX_STRIDE;
    setUV4(primitive, ((Point2u*)&g_BattlePanelUV[tex_offset])->x, ((Point2u*)&g_BattlePanelUV[tex_offset])->y, ((Point2u*)&g_BattlePanelUV[tex_offset])->x + BATTLE_PANEL_WIDTH,
           ((Point2u*)&g_BattlePanelUV[tex_offset])->y, ((Point2u*)&g_BattlePanelUV[tex_offset])->x, ((BattlePanelGeometry*)BATTLE_WORK)->height + ((Point2u*)&g_BattlePanelUV[tex_offset])->y,
           ((Point2u*)&g_BattlePanelUV[tex_offset])->x + BATTLE_PANEL_WIDTH, ((BattlePanelGeometry*)BATTLE_WORK)->height + ((Point2u*)&g_BattlePanelUV[tex_offset])->y);
    setRGB0(primitive, 1, 1, 1);
    GFX_AddPrim(2, sizeof(POLY_FT4));
    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    panel2 = (BattlePanelGeometry*)BATTLE_WORK;
    setXY4(primitive, panel2->origin.x, panel2->origin.y, panel2->origin.x + BATTLE_PANEL_WIDTH, panel2->origin.y, panel2->origin.x, panel2->origin.y + panel2->height,
           panel2->origin.x + BATTLE_PANEL_WIDTH, panel2->origin.y + panel2->height);
    primitive->tpage = GetTPage(0, 0, BATTLE_PANEL_TPAGE_X, BATTLE_PANEL_TPAGE_Y);
    setClut(primitive, BATTLE_PANEL_CLUT_X, BATTLE_PANEL_CLUT_Y);
    /* The second texture block reads the work record again for its last row, the
     * way the retail code reloads the scratchpad work pointer there. */
    setUV4(primitive, ((Point2u*)&g_BattlePanelUV[tex_offset])->x, ((Point2u*)&g_BattlePanelUV[tex_offset])->y, ((Point2u*)&g_BattlePanelUV[tex_offset])->x + BATTLE_PANEL_WIDTH,
           ((Point2u*)&g_BattlePanelUV[tex_offset])->y, ((Point2u*)&g_BattlePanelUV[tex_offset])->x, ((BattlePanelGeometry*)BATTLE_WORK)->height + ((Point2u*)&g_BattlePanelUV[tex_offset])->y,
           ((Point2u*)&g_BattlePanelUV[tex_offset])->x + BATTLE_PANEL_WIDTH, ((BattlePanelGeometry*)BATTLE_WORK)->height + ((Point2u*)&g_BattlePanelUV[tex_offset])->y);
    setRGB0(primitive, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(2, sizeof(POLY_FT4));
}
