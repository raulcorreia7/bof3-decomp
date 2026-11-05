#include "game_00.h"

MATCH void func_8019F430(void) {
    s32    heightOffset;
    s32    step;
    Actor* record;
    Actor* slot;
    Actor* work;

    record          = g_SpadWork;
    step            = record->vy + 0x14000;
    record->y.fixed = (s32)(record->y.fixed + step);
    record->vy      = step;
    if (record->y.part.integer >= 0) {
        record->unk_09 = 6;
        work           = g_SpadWork;
        record->vy     = (s32)-record->vy;
        work->unk_01   = (u8)(work->unk_01 + 1);
    }
    slot         = g_SpadWork;
    heightOffset = slot->unk_0B * BATTLE_PARTY_STRIDE;
    func_8019F5B8(
        *(s16*)((u8*)((u8*)&g_BattlePartyBattlers[0].unk_2E) + heightOffset),
        (s16)(*(u16*)((u8*)((u8*)&g_BattlePartyBattlers[0].unk_30) + heightOffset) + (u16)slot->y.part.integer),
        slot->unk_06, slot->unk_27);
}
