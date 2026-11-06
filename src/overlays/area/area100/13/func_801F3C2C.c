#include "area100_13.h"

MATCH void func_801F3C2C(void) {
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x45) == 0) {
        Area_SetCellCode(0x49, 0x1E, 0x50);
        Area_SetCellCode(0x49, 0x1F, 0x50);
        Area_SetCellCode(0x4D, 0x33, 0x50);
        Area_SetCellCode(0x4D, 0x34, 0x50);
    }
}
