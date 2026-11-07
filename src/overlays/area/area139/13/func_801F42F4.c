#include "area139_13.h"

MATCH s32 func_801F42F4(void) {
    u8* work;

    work = g_CurrentActor;
    work[0x74] &= 0xFE;
    if (g_BattlePartyBattlers[0].chr.character_id == 5) {
        SYS_SetFlag(g_SceneEventFlags, 0x4D);
        Area_SetCellPalette(4, 0xD);
        g_Task->header.flags = 0;
    }
}
