#include "area104_14.h"

MATCH bool func_801F50A8(void) {
    if ((g_Game.flags & 0x2000) != 0) {
        return 0;
    }
    if ((g_Game.input & g_InputMasks[WORLD_INPUT_VIEW]) == 0) {
        return 0;
    }
    g_GameStateIndex         = 4;
    SELF(Actor)->header.step = 0;
    return 1;
}
