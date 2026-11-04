#include "area121_14.h"

MATCH void func_801F5380(void) {
    s32 value;
    u16 value2;
    u8  value3;

    func_801C3598();
    func_801C2BEC();
    if (g_GameRequestFlags & 1) {
        if ((Area_GetCellCode((s32)g_SpadWork->x.part.integer, (s32)g_SpadWork->y.part.integer) & 0xFF) == 0xAF) {
            func_8019FA28(g_GameContextSeed, g_GameEntryPosX, g_GameEntryPosY, g_GameContextKind);
            g_GameEntryMode   = 0;
            g_GameRequestKind = 0xC;
            return;
        }
        if ((Area_GetCellCode((s32)g_SpadWork->x.part.integer, (s32)g_SpadWork->y.part.integer) & 0xFF) == 0xC0) {
            func_801A0048(g_SpadWork->x.part.integer, g_SpadWork->y.part.integer);
        }
    }
    value2     = D_80143F22;
    D_80143F22 = value2 + 1;
    value3     = g_SpadWork->direction_08;
    if ((value3 == 2) || (value3 == 6)) {
        D_80143F22 = value2 + 2;
    }
    Actor_StopMoving(value2);
    if (func_801A79A4(g_SpadWork->x.fixed, g_SpadWork->y.fixed) == 0) {
        func_801C329C();
        if (!(g_GameFlags & 0x100) && !(g_AreaWalkFlags & 0x40)) {
            value = D_8014625C & (D_80145AB6 | (g_InputMasks | 0xF000));
            if (value != 0) {
                func_801F4B4C(value);
                return;
            }
        }
        g_GameState->mode_12B.s8_value = 0;
    }
    g_SpadWork->state_02 = 0;
}
