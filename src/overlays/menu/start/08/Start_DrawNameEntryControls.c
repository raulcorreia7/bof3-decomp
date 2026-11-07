#include "start_08.h"

/* The commands the name entry screen labels, in g_NameEntryCommandLabels order. */
#define NAME_ENTRY_COMMAND_COUNT  4

/* The control window, relative to its (x, y). */
#define CONTROLS_WINDOW_INSET     3
#define CONTROLS_WINDOW_WIDTH     0x78
#define CONTROLS_WINDOW_HEIGHT    0x2F

/* The panel sprite at the window's right: sprite id, position, texture page and CLUT. */
#define CONTROLS_SPRITE_ID        0x2C
#define CONTROLS_SPRITE_X         0x50
#define CONTROLS_SPRITE_Y         5
#define CONTROLS_SPRITE_TPAGE_X   0x340
#define CONTROLS_SPRITE_TPAGE_Y   0x100
#define CONTROLS_SPRITE_CLUT_X    0xC0
#define CONTROLS_SPRITE_CLUT_Y    0x1E1

/* One row per command label; the footer icons take the row after them. */
#define CONTROLS_ROW_Y            6
#define CONTROLS_ROW_HEIGHT       8
#define CONTROLS_FOOTER_Y         (CONTROLS_ROW_Y + NAME_ENTRY_COMMAND_COUNT * CONTROLS_ROW_HEIGHT)

/* Columns: the button icon beside each label, the dot grid, the labels and the footer icons. */
#define CONTROLS_BUTTON_X         0xE
#define CONTROLS_PAIR_X           0xA
#define CONTROLS_DOT_X            0x1A
#define CONTROLS_DOT_STEP         4
#define CONTROLS_LABEL_X          0x2A
#define CONTROLS_ICON_STEP        8
#define CONTROLS_LABEL_LENGTH     0x10

/* The dot grid beside the labels. */
#define CONTROLS_DOT_ROWS         5
#define CONTROLS_DOT_COLUMNS      3

/* Menu_DrawPanelIcon cells: the button beside each command, the footer row and the pair at the footer's left. */
#define CONTROLS_ICON_OK          0x1D
#define CONTROLS_ICON_DEL         0x1C
#define CONTROLS_ICON_NEXT        0x1B
#define CONTROLS_ICON_BACK        0x1E
#define CONTROLS_ICON_BUTTONS_V   0
#define CONTROLS_ICON_FOOTER_V    0x13
#define CONTROLS_ICON_PAIR_FIRST  4
#define CONTROLS_ICON_PAIR_SECOND 5
#define CONTROLS_ICON_PAIR_V      2

/* The icon palettes on the menu CLUT row, and the icon and sprite brightness. */
#define MENU_ICON_CLUT_Y          0x1E0
#define CONTROLS_BUTTON_CLUT_X    0x30
#define CONTROLS_ICON_SHADE       0x7F
#define CONTROLS_SPRITE_SHADE     0x80

/* func_801E6784 */
/* Draws the name entry control window: the OK, Del, Next and Back labels beside the character grid and the button
 * icons that select them. */
MATCH s32 Start_DrawNameEntryControls(u8 page, s32 x, s32 y) {
    SPRT* sprite;
    u8*   rect;
    u16   left;
    u16   top;
    u16   row;
    u16   column;

    left = x;
    top  = y;

    /* The window. */
    GFX_AddDitheredDrawMode(getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
    UI_DrawWindow(x + CONTROLS_WINDOW_INSET, y + CONTROLS_WINDOW_INSET, CONTROLS_WINDOW_WIDTH, CONTROLS_WINDOW_HEIGHT,
                  0, g_WindowStyle);

    /* The panel sprite. */
    GFX_AddDrawMode(GetTPage(0, 0, CONTROLS_SPRITE_TPAGE_X, CONTROLS_SPRITE_TPAGE_Y));
    rect   = func_801AF270(CONTROLS_SPRITE_ID, 1);
    sprite = GFX_CURSOR(SPRT);
    SetSprt(sprite);
    SetSemiTrans(sprite, 0);
    sprite->x0   = x + CONTROLS_SPRITE_X;
    sprite->y0   = y + CONTROLS_SPRITE_Y;
    sprite->u0   = rect[0];
    sprite->v0   = rect[1];
    sprite->w    = rect[2];
    sprite->h    = rect[3];
    sprite->clut = GetClut(CONTROLS_SPRITE_CLUT_X, CONTROLS_SPRITE_CLUT_Y);
    setRGB0(sprite, CONTROLS_SPRITE_SHADE, CONTROLS_SPRITE_SHADE, CONTROLS_SPRITE_SHADE);
    GFX_AddPrim(1, sizeof(SPRT));

    /* The command labels. */
    for (row = 0; row < NAME_ENTRY_COMMAND_COUNT; row++) {
        UI_DrawTextString(x + CONTROLS_LABEL_X, top + row * CONTROLS_ROW_HEIGHT + CONTROLS_ROW_Y, 0,
                          CONTROLS_LABEL_LENGTH, g_NameEntryCommandLabels[row]);
    }

    /* The footer icons, on the row after the last label (row is NAME_ENTRY_COMMAND_COUNT here). */
    Menu_DrawPanelIcon(left + CONTROLS_LABEL_X, top + row * CONTROLS_ROW_HEIGHT + CONTROLS_ROW_Y, 0,
                       CONTROLS_ICON_FOOTER_V, GetClut(0, MENU_ICON_CLUT_Y), CONTROLS_ICON_SHADE);
    Menu_DrawPanelIcon(left + CONTROLS_LABEL_X + CONTROLS_ICON_STEP, top + row * CONTROLS_ROW_HEIGHT + CONTROLS_ROW_Y,
                       1, CONTROLS_ICON_FOOTER_V, GetClut(0, MENU_ICON_CLUT_Y), CONTROLS_ICON_SHADE);
    Menu_DrawPanelIcon(left + CONTROLS_LABEL_X + 2 * CONTROLS_ICON_STEP,
                       top + row * CONTROLS_ROW_HEIGHT + CONTROLS_ROW_Y, 2, CONTROLS_ICON_FOOTER_V,
                       GetClut(0, MENU_ICON_CLUT_Y), CONTROLS_ICON_SHADE);
    Menu_DrawPanelIcon(left + CONTROLS_LABEL_X + 3 * CONTROLS_ICON_STEP,
                       top + row * CONTROLS_ROW_HEIGHT + CONTROLS_ROW_Y, 3, CONTROLS_ICON_FOOTER_V,
                       GetClut(0, MENU_ICON_CLUT_Y), CONTROLS_ICON_SHADE);

    /* The dot grid. */
    for (row = 0; row < CONTROLS_DOT_ROWS; row++) {
        for (column = 0; column < CONTROLS_DOT_COLUMNS; column++) {
            UI_DrawTextString(left + column * CONTROLS_DOT_STEP + CONTROLS_DOT_X,
                              top + row * CONTROLS_ROW_HEIGHT + CONTROLS_ROW_Y, 0, 1, g_NameEntryGridDot);
        }
    }

    /* The button icons, blended. */
    GFX_AddDrawMode(getTPage(0, 1, FONT_TPAGE_X, FONT_TPAGE_Y));

    Menu_DrawPanelIcon(left + CONTROLS_BUTTON_X, top + CONTROLS_ROW_Y, CONTROLS_ICON_OK, CONTROLS_ICON_BUTTONS_V,
                       GetClut(CONTROLS_BUTTON_CLUT_X, MENU_ICON_CLUT_Y), CONTROLS_ICON_SHADE);
    Menu_DrawPanelIcon(left + CONTROLS_BUTTON_X, top + CONTROLS_ROW_Y + CONTROLS_ROW_HEIGHT, CONTROLS_ICON_DEL,
                       CONTROLS_ICON_BUTTONS_V, GetClut(CONTROLS_BUTTON_CLUT_X, MENU_ICON_CLUT_Y), CONTROLS_ICON_SHADE);
    Menu_DrawPanelIcon(left + CONTROLS_BUTTON_X, top + CONTROLS_ROW_Y + 2 * CONTROLS_ROW_HEIGHT, CONTROLS_ICON_NEXT,
                       CONTROLS_ICON_BUTTONS_V, GetClut(CONTROLS_BUTTON_CLUT_X, MENU_ICON_CLUT_Y), CONTROLS_ICON_SHADE);
    Menu_DrawPanelIcon(left + CONTROLS_BUTTON_X, top + CONTROLS_ROW_Y + 3 * CONTROLS_ROW_HEIGHT, CONTROLS_ICON_BACK,
                       CONTROLS_ICON_BUTTONS_V, GetClut(CONTROLS_BUTTON_CLUT_X, MENU_ICON_CLUT_Y), CONTROLS_ICON_SHADE);
    Menu_DrawPanelIcon(left + CONTROLS_PAIR_X, top + CONTROLS_FOOTER_Y, CONTROLS_ICON_PAIR_FIRST, CONTROLS_ICON_PAIR_V,
                       GetClut(0, MENU_ICON_CLUT_Y), CONTROLS_ICON_SHADE);
    Menu_DrawPanelIcon(left + CONTROLS_PAIR_X + CONTROLS_ICON_STEP, top + CONTROLS_FOOTER_Y, CONTROLS_ICON_PAIR_SECOND,
                       CONTROLS_ICON_PAIR_V, GetClut(0, MENU_ICON_CLUT_Y), CONTROLS_ICON_SHADE);

    /* The window frame. */
    return func_801AF390(left, top, g_NameEntryControlsFrame, 0);
}
