#include "engine/slus/slus.h"

/* The front-end state block shares its base with the cursor word at 0x00;
 * retail addresses the row selector and count from there at +0x15/+0x16. */
typedef struct {
    u8 row;
    s8 count;
} PanelRowIndex;

/* emits the D_801490C6+1 glyphs of the D_801490C5 row at the panel
 * position, stepping each by the row's scale and threading the cursor through
 * UI_DrawTextAt.
 */
MATCH void func_8015A098(void) {
    MenuPanelTask* panel;
    u8*            state;
    PanelRowIndex* rowp;
    u8*            cursor;
    s32            row;
    s32            table_offset;
    s32            i;

    state  = (u8*)&D_801490B0;
    cursor = *(u8**)state;
    i      = 0;
    if (g_MessageWindow.last_row >= 0) {
        rowp = (PanelRowIndex*)(state + 0x15);
        do {
            row          = rowp->row;
            table_offset = row * 6;
            panel        = g_MenuCurrentPanel;
            cursor = UI_DrawTextAt((*(u16*)((u8*)&D_8017F960 + table_offset) + ((s16)panel->pos.x >> 4)) & HALF_MASK,
                                   (*(u16*)((u8*)&D_8017F962 + table_offset) + ((s16)panel->pos.y >> 4) +
                                    *(s16*)((u8*)&D_8017F964 + table_offset) * i) &
                                       HALF_MASK,
                                   cursor);
            i++;
        } while (rowp->count >= i);
    }
}
