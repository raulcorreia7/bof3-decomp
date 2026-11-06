#include "game_00.h"

MATCH void func_801B2C38(void) {
    if (D_8014625C != 0) {
        g_GameState->mode_12B.u8_value = 0U;
    } else {
        D_801CD1D8[g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK]();
    }
    if (g_GameState->mode_12B.u8_value == 0) {
        Actor_RequestScript(g_Task->direction_08);
        g_Task->unk_09 = 0;
        Party_ClearBattlerState(0);
        g_Task->header.mode = 1;
        g_Task->unk_0B      = 0;
        func_801B036C();
    }
}
