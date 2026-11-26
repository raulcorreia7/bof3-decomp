#include "game_00.h"

MATCH s32 func_801B4150(void) {
    s32 x;
    s32 y;
    s32 slot;
    s32 first;
    u8  dir;

    dir = SELF(Actor)->direction;
    if (!(dir & 0x1)) {
        first = func_801B43D0(SELF(Actor)->pos.x.fixed + g_FacingSteps[(u8)(dir - 1) & 0x7].x, SELF(Actor)->pos.y.fixed + g_FacingSteps[(u8)(dir - 1) & 0x7].y, (dir - 1) & 0x7);
        first = (s8)first;
        if (first != -1) {
            SELF(Actor)->direction = (SELF(Actor)->direction - 1) & 0x7;
            return first;
        }
        slot = func_801B43D0(SELF(Actor)->pos.x.fixed + g_FacingSteps[(u8)(SELF(Actor)->direction + 1) & 0x7].x, SELF(Actor)->pos.y.fixed + g_FacingSteps[(u8)(SELF(Actor)->direction + 1) & 0x7].y,
                             (SELF(Actor)->direction + 1) & 0x7);
        slot = (s8)slot;
        if (slot != first) {
            SELF(Actor)->direction = (SELF(Actor)->direction + 1) & 0x7;
            return slot;
        }
        dir = SELF(Actor)->direction;
        return (s8)func_801B43D0(SELF(Actor)->pos.x.fixed + g_FacingSteps[dir].x, SELF(Actor)->pos.y.fixed + g_FacingSteps[dir].y, dir);
    } else {
        s32 step = SELF(Actor)->voice_flags.scene_flag + 2;
        x        = SELF(Actor)->pos.x.fixed + g_FacingSteps[dir].x * step;
        y        = SELF(Actor)->pos.y.fixed + g_FacingSteps[dir].y * step;
        if ((Area_CellGetCode((x >> 16), (y >> 16)) & BYTE_MASK) != 0x30) {
            dir = SELF(Actor)->direction;
            x   = SELF(Actor)->pos.x.fixed + g_FacingSteps[dir].x;
            y   = SELF(Actor)->pos.y.fixed + g_FacingSteps[dir].y;
        } else if (SELF(Actor)->voice_flags.scene_flag == 0) {
            dir = SELF(Actor)->direction;
            x += g_FacingSteps[dir].x;
            y += g_FacingSteps[dir].y;
        }
    }
    return (s8)func_801B43D0(x, y, SELF(Actor)->direction);
}
