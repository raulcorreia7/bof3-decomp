#include "area149_13.h"

MATCH void func_801F2C48(void) {
    u8* work;

    g_AreaCameraOffsetZ      = 0x1C80;
    g_AreaCameraRefreshCount = 2;
    g_Game.members[0].unk_48 = 1;
    g_Game.members[1].unk_48 = 1;
    g_Game.members[2].unk_48 = 1;
    work                     = SELF(u8);
    work[0x5F]               = 0x7F;
    work[0x5E]               = 0x7F;
    work[0x5D]               = 0x7F;
    SELF(Actor)->timer       = 150;
    SELF(Actor)->header.mode = 1;
}
