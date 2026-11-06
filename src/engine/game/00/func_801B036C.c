#include "game_00.h"

MATCH void func_801B036C(void) {
    if (!(g_GameFlags & GAME_FLAG_SCRIPT_ACTIVE) && !(g_AreaWalkFlags & AREA_WALK_ENTRY_PENDING) &&
        (g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) && !(func_801C3790(1) & 0xFF) && !(func_801C37DC(1) & 0xFF)) {
        if (func_801B544C() & 0xFF) {
            g_GameState->step_12A.s8_value = 0;
            return;
        }
        if ((D_8014625C != 0) && !(g_Characters[g_GameState->slot_13C].status & STATUS_CONFUSED)) {
            g_GameState->step_12A.s8_value = 0;
        }
        if (!(func_801B6674() & 0xFF) && !(func_801B6258() & 0xFF) && !(func_801B5684() & 0xFF) &&
            !(func_801B5758() & 0xFF) && !(func_801B5EBC() & 0xFF) && !(func_801B5884() & 0xFF) &&
            !(func_801B5910() & 0xFF) && (D_8014625C != 0)) {
            func_801B59B4();
            g_Task->option_flags = 0;
            g_Task->unk_0A       = 2;
            g_Task->unk_0B       = 0;
            func_801B5BDC(g_Task->direction_08);
            g_Task->header.step = 1;
        }
    }
}
