#include "game_00.h"

MATCH s32 func_801B59B4(void) {
    s32 kind;

    kind = D_8014625C & INPUT_DIRECTIONAL;
    switch (kind) {
        case PADLup:
            g_Task->direction_08 = FACING_NW;
            break;
        case PADLup | PADLright:
            g_Task->direction_08 = FACING_N;
            break;
        case PADLright:
            g_Task->direction_08 = FACING_NE;
            break;
        case PADLright | PADLdown:
            g_Task->direction_08 = FACING_E;
            break;
        case PADLdown:
            g_Task->direction_08 = FACING_SE;
            break;
        case PADLdown | PADLleft:
            g_Task->direction_08 = FACING_S;
            break;
        case PADLleft:
            g_Task->direction_08 = FACING_SW;
            break;
        case PADLleft | PADLup:
            g_Task->direction_08 = FACING_W;
            break;
        default:
            return 0;
    }
    return 1;
}
