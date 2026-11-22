#include "batl_end_00.h"

/* Steps g_Battle.selection over the party members, asking func_801EF928 about each member's id. On
 * the first hit it sets bit 5 of g_Battle.outcome.result and steps g_Battle.ui_mode; when no member hits it
 * resets g_Battle.ui_mode and steps g_Battle.ui_step. Retail reaches g_Battle.ui_mode, the selected
 * member's id byte and g_Battle.outcome.result as offsets from the g_Battle.selection address, so this
 * keeps the address view. */
MATCH void func_801EF054(void) {
    u8* state = &g_Battle.selection;
    u8* cursor;
    u8* step;
    u8  id;
    u8  mode;

    if (*state < g_Battle.party_count) {
        cursor = state;
        do {
            id        = func_801DD7AC(g_Game.members[*cursor].chr.character_id);
            cursor[2] = id;
            *cursor += 1;
            if (func_801EF928(id, 0) != 0) {
                mode = cursor[-1] + 1;
                cursor[0x43] |= 0x20;
                cursor[-1] = mode;
                return;
            }
        } while (*cursor < g_Battle.party_count);
    }
    step             = &g_Battle.ui_step;
    g_Battle.ui_mode = 0;
    *step += 1;
}
