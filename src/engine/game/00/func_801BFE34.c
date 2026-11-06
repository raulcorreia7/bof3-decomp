#include "game_00.h"

MATCH void func_801BFE34(s32 work_kind, s32 work_index, s32 work_mode) {
    s32 offset;
    s32 kind;
    s32 count;
    u8  mode;
    u8  key;
    u8* record;

    mode              = D_801CD78D[(work_mode & BYTE_MASK) * 4];
    D_80143F24        = work_kind;
    D_80143F28        = work_index;
    g_BattleScrollDir = mode;
    count             = 0;
    if (count < g_PartySize) {
        offset = 0;
        do {
            kind        = 0;
            record      = (u8*)g_BattlePartyBattlers + offset;
            g_GameState = (GameState*)record;
            TASK_SET(record);
            key = record[0x79];
            while (1) {
                if (g_SaveData.battle_order[kind & BYTE_MASK] == key)
                    break;
                kind += 1;
                if ((kind & BYTE_MASK) >= 3U)
                    break;
            }
            kind &= BYTE_MASK;
            func_801BF5A8(D_80143F24, D_80143F28, kind);
            kind <<= 3;
            FIELD(s32, D_80143F2C, kind) = g_Task->pos.x.fixed;
            FIELD(s32, D_80143F30, kind) = g_Task->pos.y.fixed;
            g_Task->unk_48               = 0;
            g_Task->direction_08         = s_RouteIndexByMode[g_BattleScrollDir];
            Actor_RequestScript(g_Task->direction_08);
            offset += BATTLE_PARTY_STRIDE;
            count += 1;
        } while (count < g_PartySize);
    }
}
