#include "battle_15.h"

/* The panel geometry the draw code reads: the origin x and y place the quad
 * on screen and the height is the quad's row count. */
typedef struct BattlePanelGeometry {
    u8  pad_00[0x0A];
    u8  height;
    u8  pad_0B[0x23];
    u16 origin_x;
    u16 origin_y;
} BattlePanelGeometry;

ASSERT_SIZE(BattlePanelGeometry, 0x32);
ASSERT_OFFSET(BattlePanelGeometry, height, 0x0A);
ASSERT_OFFSET(BattlePanelGeometry, origin_x, 0x2E);
ASSERT_OFFSET(BattlePanelGeometry, origin_y, 0x30);

/* Each panel texture entry is four bytes: the u pair then the v pair. */
#define BATTLE_PANEL_TEX_STRIDE 4
#define BATTLE_PANEL_TEX_SIZE   4

/* u: x, the quad's left u; v: y, the quad's top v. */
typedef Vec2us BattlePanelTexture;

ASSERT_SIZE(BattlePanelTexture, BATTLE_PANEL_TEX_SIZE);

/* The panel quad is 0x30 pixels wide. */
#define BATTLE_PANEL_WIDTH    0x30
/* The texture page and the clut the panel quads share. */
#define BATTLE_PANEL_TPAGE_X  0x380
#define BATTLE_PANEL_TPAGE_Y  0x100
#define BATTLE_PANEL_CLUT_X   0x10
#define BATTLE_PANEL_CLUT_Y   0x1FA
/* The draw mode's texture window: the lit and the dim panel palette. */
#define BATTLE_PANEL_MODE_LIT 0x25
#define BATTLE_PANEL_MODE_DIM 0x15

/* Draws the two panel quads at the active battle-work origin, one normal and one dark. */
MATCH void func_800AE9C4(u8 arg0) {
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
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, mode, NULL);
    GFX_AddPrim(2, 0xC);
    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    panel = (BattlePanelGeometry*)BATTLE_WORK;
    setXY4(primitive, panel->origin_x + 1, panel->origin_y + 1, panel->origin_x + 49, panel->origin_y + 1,
           panel->origin_x + 1, panel->origin_y + (panel->height + 1), panel->origin_x + 0x31,
           panel->origin_y + (panel->height + 1));
    primitive->tpage = GetTPage(0, 0, BATTLE_PANEL_TPAGE_X, BATTLE_PANEL_TPAGE_Y);
    primitive->clut  = GetClut(BATTLE_PANEL_CLUT_X, BATTLE_PANEL_CLUT_Y);
    /* The texture entry is read through the table symbol at every use: the retail
     * code materializes the table address again for each access. */
    tex_offset       = arg0 * BATTLE_PANEL_TEX_STRIDE;
    setUV4(primitive, ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->x,
           ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->y,
           ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->x + BATTLE_PANEL_WIDTH,
           ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->y,
           ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->x,
           ((BattlePanelGeometry*)BATTLE_WORK)->height + ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->y,
           ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->x + BATTLE_PANEL_WIDTH,
           ((BattlePanelGeometry*)BATTLE_WORK)->height + ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->y);
    setRGB0(primitive, 1, 1, 1);
    GFX_AddPrim(2, 0x28);
    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    panel2 = (BattlePanelGeometry*)BATTLE_WORK;
    setXY4(primitive, panel2->origin_x, panel2->origin_y, panel2->origin_x + BATTLE_PANEL_WIDTH, panel2->origin_y,
           panel2->origin_x, panel2->origin_y + panel2->height, panel2->origin_x + BATTLE_PANEL_WIDTH,
           panel2->origin_y + panel2->height);
    primitive->tpage = GetTPage(0, 0, BATTLE_PANEL_TPAGE_X, BATTLE_PANEL_TPAGE_Y);
    primitive->clut  = GetClut(BATTLE_PANEL_CLUT_X, BATTLE_PANEL_CLUT_Y);
    /* The second texture block reads the work record again for its last row, the
     * way the retail code reloads the scratchpad work pointer there. */
    setUV4(primitive, ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->x,
           ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->y,
           ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->x + BATTLE_PANEL_WIDTH,
           ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->y,
           ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->x,
           ((BattlePanelGeometry*)BATTLE_WORK)->height + ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->y,
           ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->x + BATTLE_PANEL_WIDTH,
           ((BattlePanelGeometry*)BATTLE_WORK)->height + ((BattlePanelTexture*)&g_BattlePanelUV[tex_offset])->y);
    PSX_SET_NEUTRAL_RGB(primitive);
    GFX_AddPrim(2, 0x28);
}
