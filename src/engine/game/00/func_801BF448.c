#include "game_00.h"

MATCH void func_801BF448(void) {
    s32    tab;
    s32    count;
    s32    rec_off;
    s32    i;
    s16    val;
    u8     key;
    u8*    rec;
    Actor* work;

    count = 0;
    if (count < g_PartySize) {
        tab     = 0;
        rec_off = 0;
        do {
            i           = 0;
            rec         = (u8*)g_BattlePartyBattlers + rec_off;
            g_GameState = (GameState*)rec;
            TASK_SET(rec);
            key = rec[0x79];
            while (1) {
                if (g_SaveData.walk_order[i & BYTE_MASK] == key)
                    break;
                i += 1;
                if ((i & BYTE_MASK) >= 3U)
                    break;
            }
            g_Task->pos.x.fixed = *(s32*)(D_80143F2C + tab);
            val                 = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed = *(s32*)(D_80143F30 + tab));
            work                = g_Task;
            work->unk_0B        = 0;
            COORD_INT(work->pos.z) = val;
            if ((g_SaveData.characters[g_GameState->slot_13C].status & STATUS_KO) != 0)
                Actor_SelectScript((g_BattleScrollDir + 0x1C));
            else
                Actor_SelectScript(g_BattleScrollDir);
            tab += 8;
            rec_off += BATTLE_PARTY_STRIDE;
        } while (++count < g_PartySize);
    }
}
