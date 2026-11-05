#include "game_00.h"

MATCH s32 func_801B59B4(void) {
    s32 kind;

    kind = D_8014625C & INPUT_DIRECTIONAL;
    switch (kind) {
        case PADLup:
            g_Task->direction_08 = 0;
            break;
        case PADLup | PADLright:
            g_Task->direction_08 = 1;
            break;
        case PADLright:
            g_Task->direction_08 = 2;
            break;
        case PADLright | PADLdown:
            g_Task->direction_08 = 3;
            break;
        case PADLdown:
            g_Task->direction_08 = 4;
            break;
        case PADLdown | PADLleft:
            g_Task->direction_08 = 5;
            break;
        case PADLleft:
            g_Task->direction_08 = 6;
            break;
        case PADLleft | PADLup:
            g_Task->direction_08 = 7;
            break;
        default:
            return 0;
    }
    return 1;
}
