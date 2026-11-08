#include "game_00.h"

MATCH void func_80197C1C(void) {
    u8   local_ready;
    u16* state;

    local_ready = func_801BF11C();
    func_801A06D8();
    func_801992B8();
    if (EMI_IsReady() && local_ready && g_AreaCameraMoving == 0) {
        state = &g_GameEntrySubstate;
        (*state)++;
    }
}
