#include "area149_13.h"

MATCH void func_801F2C48(void) {
    u8* work;

    g_AreaCameraOffsetZ      = 0x1C80;
    g_AreaCameraRefreshCount = 2;
    D_80145ED8               = 1;
    D_80146018               = 1;
    D_80146158               = 1;
    work                     = (u8*)g_SpadWork;
    work[0x5F]               = 0x7F;
    work[0x5E]               = 0x7F;
    work[0x5D]               = 0x7F;
    g_SpadWork->unk_09       = 0x96;
    g_SpadWork->unk_01       = 1;
}
