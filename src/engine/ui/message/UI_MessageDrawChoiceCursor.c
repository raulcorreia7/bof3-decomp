#include "engine/slus/slus.h"

/* The panel's x coordinate is signed (MENU_PANEL_FLOOR_X is negative), and the
 * cursor opener's shared declaration types its first parameter u16; calling
 * through that type would zero-extend the coordinate, which retail does not do.
 * The s8 byte table at g_UIMessageChoice selects the entry in D_801490CF, and the fixed
 * base 4 offsets the group.
 * opens the panel cursor for the slot the panel's signed x-based
 * group and the selected byte-table entry name.
 */
/* func_8015A264 */
MATCH void UI_MessageDrawChoiceCursor(void) {
    /* FAKE: signed cursor-call prototype. */
    ((void (*)(s16, u16, s32))UI_CursorDraw)((g_UIPanelCurrent->pos.vx >> 4) + 4, D_801490CF[g_UIMessageWindow.selection_index], 0);
}
