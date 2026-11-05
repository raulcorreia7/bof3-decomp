#include "area106_13.h"

MATCH void func_801F38E8(void) {
    FIELD(u8, g_CurrentActor, 0x74u) &= 0xFEu;

    if (g_CharSlot[D_80145F09] == 0) {
        g_AreaSceneMode = 1;
        TASK_BYTES[0]   = 0;
    }
}
