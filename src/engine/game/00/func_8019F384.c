#include "game_00.h"

MATCH void func_8019F384(void) {
    s32 offset;

    g_Task->unk_09 -= 1;
    offset = g_Task->unk_0B * BATTLE_PARTY_STRIDE;
    func_8019F5B8(*(s16*)(((u8*)&g_BattlePartyBattlers[0].unk_2E) + offset),
                  (*(u16*)(((u8*)&g_BattlePartyBattlers[0].unk_30) + offset) + g_Task->y.part.integer),
                  g_Task->unk_06, g_Task->unk_27);
    if (g_Task->unk_09 == 0) {
        g_Task->mode += 1;
    }
}
