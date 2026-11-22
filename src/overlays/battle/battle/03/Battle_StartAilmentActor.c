#include "battle_03.h"

/* func_801E6E54 */
MATCH void Battle_StartAilmentActor(void) {
    PartyMember* work;
    /* FAKE: Pin the fresh work pointer to a0. */
    FAKE_REG(PartyMember*, next, "a0");
    s32 index;
    u8  slot;

    TASK(PartyMember)->param.unk_0B = 0;
    slot                            = func_801E8FA8();
    index                           = slot & BYTE_MASK;
    if ((index != GAME_NONE) && (s_BattleBattlerStepIds[index] != 0xFF)) {
        TASK(PartyMember)->param.unk_0B = slot;
        TASK(PartyMember)->unk_29       = 2;
        TASK(PartyMember)->unk_25       = 5;
        TASK(PartyMember)->unk_26       = 0xF0;
        TASK(PartyMember)->unk_24       = 0x80;
        TASK(PartyMember)->unk_27       = 0xFF;
        TASK(PartyMember)->unk_28       = 0;
        work                            = g_Task;
        work->unk_2B                    = 0;
        next                            = g_Task;
        work->unk_2C.value              = 1;
        next->unk_48                    = 0;
        work                            = g_Task;
        work->scale.y                   = 0x10000;
        work->scale.x                   = 0x10000;
        work->unk_18                    = 0x666;
        work->unk_0C                    = 0;
        work->timer                     = 60;
        func_801E8DD8();
        Script_Select(s_BattleBattlerStepIds[index]);
        work              = g_Task;
        work->header.mode = (work->header.mode) + 2;
    }
}
