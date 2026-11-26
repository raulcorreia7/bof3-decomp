#include "area192_13.h"
#include "menu/save_data.h"

MATCH void func_801F3678(void) {
    u8* flag;

    if (SYS_TestFlag(g_SceneEventFlags, 119)) {
        flag                    = &g_ScenarioState.flags_01;
        g_SaveData.desert.clock = 0x1E0;
        D_80146880              = 0;
        D_80146881              = 0;
        *flag                   = *flag & 0xFE;
        Actor_Clear();
    }
}
