#include "area104_14.h"

MATCH void func_801F4E3C(void) {
    s32 value;
    u16 value2;
    u8  value3;

    func_801C3598();
    func_801C2BEC();
    if (g_GameRequestFlags & 1) {
        if ((Area_GetCellCode((s32)COORD_INT(g_Task->pos.x), (s32)COORD_INT(g_Task->pos.y)) & 0xFF) == 0xAF) {
            Game_RequestAreaChange(g_GameContextSeed, g_GameEntryPosX, g_GameEntryPosY, g_GameContextKind);
            g_GameEntryMode   = 0;
            g_GameRequestKind = 0xC;
            return;
        }
        if ((Area_GetCellCode((s32)COORD_INT(g_Task->pos.x), (s32)COORD_INT(g_Task->pos.y)) & 0xFF) == 0xC0) {
            func_801A0048(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y));
        }
    }
    value2     = D_80143F22;
    D_80143F22 = value2 + 1;
    value3     = g_Task->direction_08;
    if ((value3 == 2) || (value3 == 6)) {
        D_80143F22 = value2 + 2;
    }
    Actor_StopMoving();
    if (func_801A79A4(g_Task->pos.x.fixed, g_Task->pos.y.fixed) == 0) {
        func_801C329C();
        if (!(g_GameFlags & GAME_FLAG_SCRIPT_ACTIVE) && !(g_AreaWalkFlags & AREA_WALK_ENTRY_PENDING)) {
            value = D_8014625C & (g_InputMasks[INPUT_SLOT_DASH] | (g_InputMasks[INPUT_SLOT_EXAMINE] | 0xF000));
            if (value != 0) {
                func_801F4608(value);
                return;
            }
        }
        g_GameState->mode_12B.s8_value = 0;
    }
    g_Task->header.step = 0;
}
