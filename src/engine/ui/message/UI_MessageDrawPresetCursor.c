#include "engine/slus/slus.h"

/* places the front-end panel cursor through UI_CursorDraw at the
 * panel record's tile column and tile row, the row adding the 6-byte row-table
 * entry the panel index byte D_801490C5 selects and that entry's scale halfword
 * times g_UIMessageChoice.
 */
/* func_8015A1D8 */
MATCH void UI_MessageDrawPresetCursor(void) {
    MenuPanelTask* panel;
    s32            index;
    s32            row_offset;

    index      = g_UIMessageWindow.panel_index;
    row_offset = D_8017F962[index].scale * g_UIMessageWindow.selection_index;
    panel      = g_UIPanelCurrent;
    /* The retail call leaves both arguments unconverted; the shared u16 view of
     * UI_CursorDraw masks each one, so the call goes through the 32-bit view. */
    ((void (*)(s32, s32, s32))UI_CursorDraw)((panel->pos.vx >> 4) + 4, (panel->pos.vy >> 4) + D_8017F962[index].row_offset + row_offset, 0);
}
