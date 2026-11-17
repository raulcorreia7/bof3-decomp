#include "game_00.h"

MATCH void func_8019A370(void) {
    g_AreaHandlers[Game_FindArea() & BYTE_MASK].steps[4]();
}
