#include "batl_end_00.h"

/* Steps g_BattleRowCursor over the party rows, asking func_801EF928 about each member's id. On
 * the first hit it sets bit 5 of g_BattleResult and steps g_BattleUiState; when no row hits it
 * resets g_BattleUiState and steps g_BattleUiStep.
 * needs: type, one record over 0x801462E3..0x80146328. */
MATCH void func_801EF054(void) {
    u8* first = &g_BattleRowCursor;
    u8* row;
    u8* step;
    u8  id;
    u8  state;

    if (*first < g_BattlePartyCount) {
        row = first;
        do {
            id     = func_801DD7AC(g_BattlePartyBattlers[*row].stats.character_id);
            row[2] = id;
            *row += 1;
            if (func_801EF928(id, 0) != 0) {
                state = row[-1] + 1;
                row[0x43] |= 0x20;
                row[-1] = state;
                return;
            }
        } while (*row < g_BattlePartyCount);
    }
    step            = &g_BattleUiStep;
    g_BattleUiState = 0;
    *step += 1;
}
