#include "game_00.h"

MATCH s32 Area_CanStartEncounter(void) {
    Actor* rec;
    Actor* work;
    s32    i;
    u32    value;
    u8     ok;
    s32    x;
    s32    dy;

    if (g_GameFlags & 0x20) {
        D_80145FB8 = 0;
    }
    if (FIELD(u8, func_801B3C3C(D_80145EC6, D_80145ECA), 0x4u) == 0) {
        D_80145FB8 = 0;
    }
    if (D_80145FB8 == 0) {
        return 0;
    }
    if ((u8)D_80145FAC < 4) {
        value = ((u16)D_80143F22 * 7) / 10;
    } else {
        value = (u16)D_80143F22;
    }
    if (value < (u16)D_80145FB8) {
        return 0;
    }
    if (D_80145FBC & 1) {
        return 0;
    }
    if (!(g_GameRequestFlags & 1) && D_80143EFC >= 0xF1) {
        return 0;
    }
    for (i = 0; i < g_PartySize; i++) {
        if (g_BattlePartyBattlers[i].flags_00 & ACTOR_FLAG_HIDDEN) {
            return 0;
        }
    }
    if (!(g_GameRequestFlags & 1)) {
        work       = (Actor*)SCRATCH_WORK;
        ok         = Area_BuildEncounter(4, 0);
        g_SpadWork = work;
        if (ok != 0) {
            for (i = 0; i < g_PartySize; i++) {
                ok = func_801C472C(FIELD(s32, D_80143F2C, i << 3), FIELD(s32, D_80143F30, i << 3),
                                   D_80181B1C[D_80144F5D[i]], 0x10, 1);
                if (ok == 0) {
                    break;
                }
            }
        }
        return ok;
    }
    rec   = g_SpadWork;
    value = rec->y.fixed;
    /* x holds the step count, then the x sum */
    x     = rec->unk_09;
    dy    = rec->unk_10 * x;
    x     = rec->x.fixed + rec->unk_0C * x;
    return (AREA_CELL_CODE_S16(x >> 16, (value + dy) >> 16) & BYTE_MASK) == 0;
}
