#include "game_00.h"

MATCH void func_80197A60(void) {
    u16* state;

    func_801BEDD0();
    func_801A06D8();
    Area_RunLoadingFrame();
    state = &g_GameEntrySubstate;
    (*state)++;
}
