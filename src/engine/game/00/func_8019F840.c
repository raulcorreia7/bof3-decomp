#include "game_00.h"

/* The battle slot byte views are volatile so the selection loop keeps the
 * per-byte symbol addressing instead of a strength-reduced pointer. */

MATCH void func_8019F840(void) {
    s32 i;
    s32 offset;
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);

    if (!(g_Game.walk_flags & AREA_WALK_LEADER_SWITCH_ACTIVE)) {
        if (LOHU(g_GameAreaId) == AREA_ID_PLANT) {
            func_801F2DCC();
        } else if (LOHU(g_GameAreaId) == AREA_ID_HIDDEN_FACTORY_ENTRANCE) {
            func_801F41D8();
        } else if (LOHU(g_GameAreaId) == AREA_ID_HIDDEN_FACTORY_ROOMS) {
            func_801F4CD0();
        } else if (LOHU(g_GameAreaId) == AREA_ID_MYRIA_STATION_HEAL) {
            func_801F3628();
        } else if (LOHU(g_GameAreaId) == AREA_ID_MYRIA_STATION_PLANT_ROOM) {
            func_801F3868();
        }
        if ((s16)g_Game.party_size > 0) {
            i      = 0;
            offset = 0;
            do {
                if ((g_Task->param.unk_0B >> i) & 0x1) {
                    D_80145E91[offset] = 1;
                    if (i != 0) {
                        D_80145E92[offset] = 1;
                    } else {
                        D_80145E92[offset] = 2;
                    }
                    D_80145E93[offset] = 0;
                    D_80145E94[offset] = 0;
                }
                i++;
                offset = i * BATTLE_PARTY_STRIDE;
            } while (i < g_PartySize);
        }
    }
}
