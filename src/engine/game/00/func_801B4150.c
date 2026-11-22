#include "game_00.h"

MATCH s32 func_801B4150(void) {
    s32 x;
    s32 y;
    s32 slot;
    s32 first;
    u8  dir;

    dir = TASK(Actor)->direction;
    if (!(dir & 0x1)) {
        first = func_801B43D0(TASK(Actor)->pos.x.fixed + g_FacingSteps[(u8)(dir - 1) & 0x7].x, TASK(Actor)->pos.y.fixed + g_FacingSteps[(u8)(dir - 1) & 0x7].y, (dir - 1) & 0x7);
        first = (s8)first;
        if (first != -1) {
            TASK(Actor)->direction = (TASK(Actor)->direction - 1) & 0x7;
            return first;
        }
        slot = func_801B43D0(TASK(Actor)->pos.x.fixed + g_FacingSteps[(u8)(TASK(Actor)->direction + 1) & 0x7].x, TASK(Actor)->pos.y.fixed + g_FacingSteps[(u8)(TASK(Actor)->direction + 1) & 0x7].y,
                             (TASK(Actor)->direction + 1) & 0x7);
        slot = (s8)slot;
        if (slot != first) {
            TASK(Actor)->direction = (TASK(Actor)->direction + 1) & 0x7;
            return slot;
        }
        dir = TASK(Actor)->direction;
        return (s8)func_801B43D0(TASK(Actor)->pos.x.fixed + g_FacingSteps[dir].x, TASK(Actor)->pos.y.fixed + g_FacingSteps[dir].y, dir);
    } else {
        s32 step = TASK(Actor)->voice_flags.scene_flag + 2;
        x        = TASK(Actor)->pos.x.fixed + g_FacingSteps[dir].x * step;
        y        = TASK(Actor)->pos.y.fixed + g_FacingSteps[dir].y * step;
        if ((Area_CellGetCode((x >> 16), (y >> 16)) & BYTE_MASK) != 0x30) {
            dir = TASK(Actor)->direction;
            x   = TASK(Actor)->pos.x.fixed + g_FacingSteps[dir].x;
            y   = TASK(Actor)->pos.y.fixed + g_FacingSteps[dir].y;
        } else if (TASK(Actor)->voice_flags.scene_flag == 0) {
            dir = TASK(Actor)->direction;
            x += g_FacingSteps[dir].x;
            y += g_FacingSteps[dir].y;
        }
    }
    return (s8)func_801B43D0(x, y, TASK(Actor)->direction);
}
