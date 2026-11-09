#include "batl_end_00.h"

/* Steps g_Battle.row_cursor over the party rows, asking func_801EF928 about each member's id. On
 * the first hit it sets bit 5 of g_Battle.outcome.result and steps g_Battle.ui_state; when no row hits it
 * resets g_Battle.ui_state and steps g_Battle.ui_step. Retail reaches g_Battle.ui_state, the row's id byte
 * and g_Battle.outcome.result as offsets from the g_Battle.row_cursor address, so this keeps the address view. */
MATCH void func_801EF054(void) {
    u8* first = &g_Battle.row_cursor;
    u8* row;
    u8* step;
    u8  id;
    u8  state;

    if (*first < g_Battle.party_count) {
        row = first;
        do {
            id     = func_801DD7AC(g_Game.members[*row].chr.character_id);
            row[2] = id;
            *row += 1;
            if (func_801EF928(id, 0) != 0) {
                state = row[-1] + 1;
                row[0x43] |= 0x20;
                row[-1] = state;
                return;
            }
        } while (*row < g_Battle.party_count);
    }
    step              = &g_Battle.ui_step;
    g_Battle.ui_state = 0;
    *step += 1;
}
