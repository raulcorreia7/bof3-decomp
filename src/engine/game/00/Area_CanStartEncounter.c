#include "game_00.h"

MATCH s32 Area_CanStartEncounter(void) {
    Actor* rec;
    Actor* work;
    s32    i;
    u32    value;
    u8     ok;
    s32    x;
    s32    dy;

    if (g_Game.flags & 0x20) {
        D_80145FB8 = 0;
    }
    if (FIELD(u8, func_801B3C3C(D_80145EC6, D_80145ECA), 0x4u) == 0) {
        D_80145FB8 = 0;
    }
    if (D_80145FB8 == 0) {
        return 0;
    }
    if (g_Game.members[0].u.field.counter_11C.u8_value < 4) {
        value = ((u16)g_EncounterSteps * 7) / 10;
    } else {
        value = (u16)g_EncounterSteps;
    }
    if (value < D_80145FB8) {
        return 0;
    }
    if (g_Game.members[0].status.field.flags_12C.u8_value & AREA_LOAD_FLAG_WORLD_MAP) {
        return 0;
    }
    if (!(g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) && D_80143EFC >= 0xF1) {
        return 0;
    }
    for (i = 0; i < g_Game.party_size; i++) {
        if (g_Game.members[i].header.flags & ACTOR_FLAG_HIDDEN) {
            return 0;
        }
    }
    if (!(g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP)) {
        work   = g_Task;
        ok     = Area_BuildEncounter(4, 0);
        g_Task = work;
        if (ok != 0) {
            for (i = 0; i < g_Game.party_size; i++) {
                ok = func_801C472C(g_EncounterParty[i].x.fixed, g_EncounterParty[i].y.fixed, D_80181B1C[g_PartyBattleOrder[i]], 0x10, 1);
                if (ok == 0) {
                    break;
                }
            }
        }
        return ok;
    }
    rec   = g_Task;
    value = rec->pos.y.fixed;
    /* x holds the step count, then the x sum */
    x     = rec->timer;
    dy    = rec->vy * x;
    x     = rec->pos.x.fixed + rec->vx * x;
    return (AREA_CELL_CODE_S16(x >> 16, (value + dy) >> 16) & BYTE_MASK) == 0;
}
