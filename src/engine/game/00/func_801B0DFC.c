#include "game_00.h"

MATCH void func_801B0DFC(void) {
    Actor_Move();
    if (g_Game.current->u.field.counter_11C.u8_value >= 4U) {
        func_8014D978();
    }
}
