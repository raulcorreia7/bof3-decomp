#include "engine/slus/slus.h"

/* places the front-end panel cursor through Menu_DrawCursorSprite at the
 * panel record's tile column and tile row, the row adding the 6-byte row-table
 * entry the panel index byte D_801490C5 selects and that entry's scale halfword
 * times g_MessageChoice.
 */
MATCH void func_8015A1D8(void) {
    MenuPanelTask* panel;
    s32            index;
    s32            row_offset;

    index      = g_MessageWindow.panel_index;
    row_offset = D_8017F962[index].scale * g_MessageWindow.selection_index;
    panel      = g_MenuCurrentPanel;
    /* The retail call leaves both arguments unconverted; the shared u16 view of
     * Menu_DrawCursorSprite masks each one, so the call goes through the 32-bit view. */
    ((void (*)(s32, s32, s32))Menu_DrawCursorSprite)(((s16)panel->pos.x >> 4) + 4, ((s16)panel->pos.y >> 4) + D_8017F962[index].row_offset + row_offset, 0);
}
