#include "engine/game/00/game_00.h"

/* func_801B59B4 */
MATCH bool Game_GetInput(void) {
    s32 type;

    type = g_Game.input & INPUT_DIRECTIONAL;
    switch (type) {
        case PADLup:
            SELF(Actor)->direction = FACING_UP_LEFT;
            break;
        case PADLup | PADLright:
            SELF(Actor)->direction = FACING_UP;
            break;
        case PADLright:
            SELF(Actor)->direction = FACING_UP_RIGHT;
            break;
        case PADLright | PADLdown:
            SELF(Actor)->direction = FACING_RIGHT;
            break;
        case PADLdown:
            SELF(Actor)->direction = FACING_DOWN_RIGHT;
            break;
        case PADLdown | PADLleft:
            SELF(Actor)->direction = FACING_DOWN;
            break;
        case PADLleft:
            SELF(Actor)->direction = FACING_DOWN_LEFT;
            break;
        case PADLleft | PADLup:
            SELF(Actor)->direction = FACING_LEFT;
            break;
        default:
            return 0;
    }
    return 1;
}
