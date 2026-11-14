#include "boss002_16.h"
#include "area/spad.h"

MATCH void func_800C191C(void) {
    u8* record;
    u8* flags;
    s32 index;

    Actor_StepAnimOnce();
    index  = (u8)func_800AC7D0(0);
    record = &g_Actors[index].interaction_flags;
    if (!Actor_Run(record, 0, -0xE, 0x40, -0x400, 0xFF, 0)) {
        Battle_ClearSlotPending(g_Task->unk_05);
        flags = &g_Battle.outcome.result;
        *flags |= BATTLE_RESULT_VICTORY;
        func_800ACFF4();
    }
}
