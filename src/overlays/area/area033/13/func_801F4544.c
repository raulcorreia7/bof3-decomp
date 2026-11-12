#include "area033_13.h"

MATCH void func_801F4544(void) {
    u8* scratch;
    s32 row_offset;
    s32 map_offset;

    if (D_8014496D == 9 || (g_SceneState.flags_01 & 0x1) != 0) {
        Actor_Clear();
        return;
    }
    Game_FindAreaHandler();
    Area_FindSceneRecord(0x205);

    g_Task->unk_48       = 0;
    g_Task->active_flags = 0;
    g_Task->unk_2A       = 0;
    ACTOR_CLEAR_TINT();

    scratch                                                         = (u8*)g_Task;
    row_offset                                                      = scratch[0x0B] * 4;
    map_offset                                                      = D_801F4CB0[0x19 + row_offset] * g_AreaMapBundle.width;
    *(g_AreaCellCodes + map_offset + D_801F4CB0[0x18 + row_offset]) = 0xA0;
    Actor_SelectScript(0);
    g_Task->header.mode = 1;
}
