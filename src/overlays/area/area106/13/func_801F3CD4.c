#include "area106_13.h"

/* The step into Tidal Caves: the scene-event flags select one of the six entrance steps, and a
 * position inside that step's window starts scene 0x24 at the step. */
MATCH s32 func_801F3CD4(s32 entry_x, s32 entry_y) {
    if (D_80143F03 != 0) {
        return 0;
    }

    if (SYS_TestFlag(g_SceneEventFlags, 0x4F) != 0) {
        if (SYS_TestFlag(g_SceneEventFlags, 0x51) == 0) {
            if (entry_y == TO_COORD(36) + COORD_HALF && ((entry_x >> 16) - 17) < 3U) {
                func_801F3E54(0);
                return 1;
            }
        } else if (entry_y == TO_COORD(10) + COORD_HALF && ((entry_x >> 16) - 18) < 2U) {
            func_801F3E54(2);
            return 1;
        }
        return 0;
    }

    if (SYS_TestFlag(g_SceneEventFlags, 0x52) != 0) {
        if (entry_y == TO_COORD(37) + COORD_HALF && ((entry_x >> 16) - 26) < 2U) {
            if (SYS_TestFlag(g_SceneEventFlags, 0x53) != 0) {
                func_801F3E54(0x10);
            } else {
                func_801F3E54(0xC);
            }
            return 1;
        }
        return 0;
    }

    if (SYS_TestFlag(g_SceneEventFlags, 0x53) != 0) {
        if (entry_x == TO_COORD(38) + COORD_HALF && ((entry_y >> 16) - 36) < 2U) {
            func_801F3E54(0xE);
            return 1;
        }
        return 0;
    }

    if (entry_x == TO_COORD(24) + COORD_HALF && ((entry_y >> 16) - 21) < 2U) {
        func_801F3E54(0xA);
        return 1;
    }
    return 0;
}
