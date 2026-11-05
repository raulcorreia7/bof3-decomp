#include "boss002_16.h"

MATCH void func_800C191C(void) {
    u8* record;
    u8* flags;
    s32 index;

    func_8014DAEC();
    index  = (u8)func_800AC7D0(0);
    record = &g_Actors[index].flags_74;
    if (!Actor_RunHandler((s32)record, 0, -0xE, 0x40, -0x400, 0xFF, 0)) {
        Battle_ClearSlotPending(TASK_BYTES[5]);
        flags = &g_BattleResult;
        *flags |= BATTLE_RESULT_VICTORY;
        func_800ACFF4();
    }
}
