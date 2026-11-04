#include "game_00.h"

MATCH void func_801B036C(void) {
    if (!(g_GameFlags & GAME_FLAG_SCRIPT_ACTIVE) && !(g_AreaWalkFlags & AREA_WALK_ENTRY_PENDING) &&
        (g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) && !(func_801C3790(1) & BYTE_MASK) &&
        !(func_801C37DC(1) & BYTE_MASK)) {
        if (func_801B544C() & BYTE_MASK) {
            g_GameState->step_12A.s8_value = 0;
            return;
        }
        if ((D_8014625C != 0) && !(g_Characters[g_GameState->slot_13C].status & STATUS_CONFUSED)) {
            g_GameState->step_12A.s8_value = 0;
        }
        if (!(func_801B6674() & BYTE_MASK) && !(func_801B6258() & BYTE_MASK) && !(func_801B5684() & BYTE_MASK) &&
            !(func_801B5758() & BYTE_MASK) && !(func_801B5EBC() & BYTE_MASK) && !(func_801B5884() & BYTE_MASK) &&
            !(func_801B5910() & BYTE_MASK) && (D_8014625C != 0)) {
            func_801B59B4();
            g_SpadWork->option_flags = 0;
            g_SpadWork->unk_0A       = 2;
            g_SpadWork->unk_0B       = 0;
            func_801B5BDC(g_SpadWork->direction_08);
            g_SpadWork->state_02 = 1;
        }
    }
}
