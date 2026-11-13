#include "game_00.h"

/* func_801B59B4 */
MATCH bool Game_GetInput(void) {
    s32 kind;

    kind = g_Game.input & INPUT_DIRECTIONAL;
    switch (kind) {
        case PADLup:
            g_Task->direction_08 = FACING_UP_LEFT;
            break;
        case PADLup | PADLright:
            g_Task->direction_08 = FACING_UP;
            break;
        case PADLright:
            g_Task->direction_08 = FACING_UP_RIGHT;
            break;
        case PADLright | PADLdown:
            g_Task->direction_08 = FACING_RIGHT;
            break;
        case PADLdown:
            g_Task->direction_08 = FACING_DOWN_RIGHT;
            break;
        case PADLdown | PADLleft:
            g_Task->direction_08 = FACING_DOWN;
            break;
        case PADLleft:
            g_Task->direction_08 = FACING_DOWN_LEFT;
            break;
        case PADLleft | PADLup:
            g_Task->direction_08 = FACING_LEFT;
            break;
        default:
            return 0;
    }
    return 1;
}
