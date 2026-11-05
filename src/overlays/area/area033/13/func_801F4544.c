#include "area033_13.h"

MATCH void func_801F4544(void) {
    u8* scratch;
    s32 row_offset;
    s32 map_offset;

    if (D_8014496D == 9 || (D_80146871 & 1) != 0) {
        Actor_Clear();
        return;
    }
    Game_FindAreaHandler();
    Area_FindSceneRecord(0x205);

    ((u8*)g_SpadWork)[0x48] = 0;
    g_SpadWork->flags_24    = 0;
    ((u8*)g_SpadWork)[0x2A] = 0;
    ((u8*)g_SpadWork)[0x5D] = 0;
    ((u8*)g_SpadWork)[0x5E] = 0;
    ((u8*)g_SpadWork)[0x5F] = 0;

    scratch                                                         = (u8*)g_SpadWork;
    row_offset                                                      = scratch[0x0B] * 4;
    map_offset                                                      = D_801F4CB0[0x19 + row_offset] * D_80104000;
    *(g_AreaCellCodes + map_offset + D_801F4CB0[0x18 + row_offset]) = 0xA0;
    Actor_SelectScript(0);
    ((u8*)g_SpadWork)[1] = 1;
}
