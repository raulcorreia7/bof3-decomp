#include "area121_14.h"

MATCH void func_801F5380(void) {
    s32 temp_a0_2;
    u16 temp_a0;
    u8  temp_v1;

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
        goto block_5;
    }
block_5:
    temp_a0    = D_80143F22;
    D_80143F22 = temp_a0 + 1;
    temp_v1    = g_SpadWork->direction_08;
    if ((temp_v1 == 2) || (temp_v1 == 6)) {
        D_80143F22 = temp_a0 + 2;
    }
    Actor_StopMoving(temp_a0);
    if (func_801A79A4(g_SpadWork->x.fixed, g_SpadWork->y.fixed) == 0) {
        func_801C329C();
        if (!(g_GameFlags & 0x100) && !(g_AreaWalkFlags & 0x40)) {
            temp_a0_2 = D_8014625C & (D_80145AB6 | (g_InputMasks | 0xF000));
            if (temp_a0_2 != 0) {
                func_801F4B4C(temp_a0_2);
                return;
            }
        }
        g_GameState->mode_12B.s8_value = 0;
        goto block_14;
    }
block_14:
    g_SpadWork->state_02 = 0;
}
