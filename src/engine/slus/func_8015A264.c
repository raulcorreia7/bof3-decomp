#include "engine/slus/slus.h"

/* The panel's x coordinate is signed (MENU_PANEL_FLOOR_X is negative). */
MATCH void func_8015A264(void) {
    /* FAKE: signed cursor-call prototype. */
    ((void (*)(s16, u16, s32))Menu_DrawCursorSprite)(((s16)g_MenuCurrentPanel->pos.x >> 4) + 4,
                                                     D_801490CF[g_MessageWindow.selection_index], 0);
}
