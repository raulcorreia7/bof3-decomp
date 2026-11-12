#include "battle_03.h"

/* The battle panel rows. Each row has an (x, y) offset pair in D_801EAE94 and a
 * row width in g_Battle.panel_widths; rows 0-4 are the queued battle panels and rows 5-6
 * the two entrance origins. g_Battle.panel_slot names the selected panel slot. */

/* draws the queued battle panel rows and the two entrance origins around (x, y), each quad sized by the
 * width of its own row.
 */
/* func_801D7A40 */
MATCH void Battle_DrawPanelRows(s16 x, s16 y) {
    u8  panel_index;
    u8  row_width;
    u8  shade;
    u8* entrance_widths;

    shade = 0;
    for (panel_index = 0; panel_index < BATTLE_PANEL_SLOT_COUNT; panel_index++) {
        if (panel_index != g_Battle.panel_slot) {
            shade = 0x80;
            /* Rows 2 and 3 use shade 0x40 instead of 0x80 while the battle
             * message slot's word at +0x128 has 0x2 set. */
            if ((panel_index == 2 || panel_index == 3) && (FIELD(s32, g_BattleMessageSlot, 0x128u) & 2)) {
                shade = 0x40;
            }
            row_width = g_Battle.panel_widths[panel_index];
            func_801644D8(panel_index, x + s_BattlePanelOffsets[panel_index][0] - (row_width >> 1), y + s_BattlePanelOffsets[panel_index][1] - (row_width >> 1), row_width + BATTLE_PANEL_SIZE,
                          row_width + BATTLE_PANEL_SIZE, shade);
        }
    }
    if (g_Battle.panel_slot < BATTLE_PANEL_SLOT_COUNT) {
        shade = 0x80;
        if ((g_Battle.panel_slot == 2 || g_Battle.panel_slot == 3) && (FIELD(s32, g_BattleMessageSlot, 0x128u) & 2)) {
            shade = 0x40;
        }
    }
    row_width = g_Battle.panel_widths[g_Battle.panel_slot];
    if (row_width == 0) {
        func_801644D8(g_Battle.panel_slot, x + s_BattlePanelOffsets[g_Battle.panel_slot][0], y + s_BattlePanelOffsets[g_Battle.panel_slot][1], BATTLE_PANEL_SIZE, BATTLE_PANEL_SIZE, shade);
    } else {
        func_801D7D10(g_Battle.panel_slot, (x + s_BattlePanelOffsets[g_Battle.panel_slot][0] - (row_width >> 1)), (y + s_BattlePanelOffsets[g_Battle.panel_slot][1] - (row_width >> 1)),
                      (u8)(row_width + BATTLE_PANEL_SIZE), (row_width + BATTLE_PANEL_SIZE), shade);
    }
    /* The entrance origins are the rows after the queued panels, with their
     * offsets and widths in the same two tables; a battle quad's palette row
     * follows the row index. */
    entrance_widths = g_Battle.panel_widths + BATTLE_PANEL_SLOT_COUNT;
    row_width       = entrance_widths[0];
    if (row_width != 0) {
        func_801D7D10(BATTLE_PANEL_SLOT_COUNT, (x + s_BattlePanelOffsets[BATTLE_PANEL_SLOT_COUNT][0] - (row_width >> 1)), (y + s_BattlePanelOffsets[BATTLE_PANEL_SLOT_COUNT][1] - (row_width >> 1)),
                      (u8)(row_width + BATTLE_PANEL_SIZE), (row_width + BATTLE_PANEL_SIZE), 0x80);
    }
    entrance_widths++;
    row_width = entrance_widths[0];
    if (row_width != 0) {
        func_801D7D10(BATTLE_PANEL_SLOT_COUNT + 1, (x + s_BattlePanelOffsets[BATTLE_PANEL_SLOT_COUNT + 1][0] - (row_width >> 1)),
                      (y + s_BattlePanelOffsets[BATTLE_PANEL_SLOT_COUNT + 1][1] - (row_width >> 1)), (u8)(row_width + BATTLE_PANEL_SIZE), (row_width + BATTLE_PANEL_SIZE), 0x80);
    }
}
