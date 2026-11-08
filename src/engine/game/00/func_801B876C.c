#include "game_00.h"

MATCH void func_801B876C(void) {
    g_Task->timer                             = 0;
    g_Task->param.unk_0B                      = g_Task->direction_08;
    g_GameState->u.field.counter_11C.u8_value = 4;
    g_Task->unk_03                            = 1;
}
