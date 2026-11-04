#include "area121_14.h"

MATCH void func_801F2CBC(void) {
    if (g_AreaCameraOffsetZ < 0x5DC) {
        g_AreaCameraOffsetZ += 0x40;
        g_ScriptState->cursor -= 2;
    } else {
        g_AreaCameraOffsetZ = 0x5DC;
        g_SpadWork->unk_04  = 0;
    }
    g_AreaCameraRefreshCount = 2;
}
