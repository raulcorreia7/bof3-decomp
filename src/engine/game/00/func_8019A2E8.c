#include "game_00.h"

MATCH void func_8019A2E8(void) {
    g_AreaHandlers[Game_FindArea() & BYTE_MASK].handler_0C();
}
