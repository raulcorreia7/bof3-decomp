#include "start_08.h"

void Menu_DrawPanelIcon(u16 icon_x, u16 icon_y, s32 icon_u, s32 icon_v, u16 icon_clut, u8 icon_shade);

/* The commands the name entry screen labels, in D_801ED1B8 order. */
#define NAME_ENTRY_COMMAND_COUNT 4

/* func_801E6784 */
/* Draws the name entry control window: the OK, Del, Next and Back labels beside the character grid and the button
 * icons that select them. */
MATCH s32 Start_DrawNameEntryControls(u8 page, s32 x, s32 y) {
    SPRT* sprite;
    u8*   rect;
    u16   left;
    u16   top;
    u16   i;
    u16   j;
    s32   tpage;

    left = x;
    top  = y;

    if (GetGraphType() != 1) {
        GetGraphType();
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, 0xF, NULL);
    GFX_AddPrim(1, 0xC);
    UI_DrawWindow(x + 3, y + 3, 0x78, 0x2F, 0, g_WindowStyle);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, 0x340, 0x100), NULL);
    GFX_AddPrim(1, 0xC);
    rect   = func_801AF270(0x2C, 1);
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    SetSemiTrans(sprite, 0);
    sprite->x0   = x + 0x50;
    sprite->y0   = y + 5;
    sprite->u0   = rect[0];
    sprite->v0   = rect[1];
    sprite->w    = rect[2];
    sprite->h    = rect[3];
    sprite->clut = GetClut(0xC0, 0x1E1);
    sprite->r0   = 0x80;
    sprite->g0   = 0x80;
    sprite->b0   = 0x80;
    GFX_AddPrim(1, 0x14);

    for (i = 0; i < NAME_ENTRY_COMMAND_COUNT; i++) {
        UI_DrawTextString(x + 0x2A, top + i * 8 + 6, 0, 0x10, D_801ED1B8[i]);
    }

    Menu_DrawPanelIcon(left + 0x2A, top + i * 8 + 6, 0, 0x13, GetClut(0, 0x1E0), 0x7F);
    Menu_DrawPanelIcon(left + 0x32, top + i * 8 + 6, 1, 0x13, GetClut(0, 0x1E0), 0x7F);
    Menu_DrawPanelIcon(left + 0x3A, top + i * 8 + 6, 2, 0x13, GetClut(0, 0x1E0), 0x7F);
    Menu_DrawPanelIcon(left + 0x42, top + i * 8 + 6, 3, 0x13, GetClut(0, 0x1E0), 0x7F);

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            UI_DrawTextString(left + j * 4 + 0x1A, top + i * 8 + 6, 0, 1, D_801ED1D4);
        }
    }

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x8F;
    } else {
        tpage = 0x2F;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, NULL);
    GFX_AddPrim(1, 0xC);

    Menu_DrawPanelIcon(left + 0xE, top + 6, 0x1D, 0, GetClut(0x30, 0x1E0), 0x7F);
    Menu_DrawPanelIcon(left + 0xE, top + 0xE, 0x1C, 0, GetClut(0x30, 0x1E0), 0x7F);
    Menu_DrawPanelIcon(left + 0xE, top + 0x16, 0x1B, 0, GetClut(0x30, 0x1E0), 0x7F);
    Menu_DrawPanelIcon(left + 0xE, top + 0x1E, 0x1E, 0, GetClut(0x30, 0x1E0), 0x7F);
    Menu_DrawPanelIcon(left + 0xA, top + 0x26, 4, 2, GetClut(0, 0x1E0), 0x7F);
    Menu_DrawPanelIcon(left + 0x12, top + 0x26, 5, 2, GetClut(0, 0x1E0), 0x7F);

    return func_801AF390(left, top, D_801ED05C, 0);
}
