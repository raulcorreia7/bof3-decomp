#include "battle_03.h"

/* func_801E6E54 */
MATCH void Battle_StartAilmentActor(void) {
    PartyMember* work;
    /* FAKE: Pin the fresh work pointer to a0. */
    FAKE_REG(PartyMember*, next, "a0");
    s32 index;
    u8  slot;

    SELF(PartyMember)->param.unk_0B = 0;
    slot                            = func_801E8FA8();
    index                           = slot & BYTE_MASK;
    if ((index != GAME_NONE) && (s_BattleBattlerStepIds[index] != 0xFF)) {
        SELF(PartyMember)->param.unk_0B = slot;
        SELF(PartyMember)->unk_29       = 2;
        SELF(PartyMember)->unk_25       = 5;
        SELF(PartyMember)->unk_26       = 0xF0;
        SELF(PartyMember)->unk_24       = 0x80;
        SELF(PartyMember)->unk_27       = 0xFF;
        SELF(PartyMember)->unk_28       = 0;
        work                            = SELF(PartyMember);
        work->unk_2B                    = 0;
        next                            = SELF(PartyMember);
        work->unk_2C.value              = 1;
        next->unk_48                    = 0;
        work                            = SELF(PartyMember);
        work->scale.y                   = 0x10000;
        work->scale.x                   = 0x10000;
        work->unk_18                    = 0x666;
        work->unk_0C                    = 0;
        work->timer                     = 60;
        func_801E8DD8();
        Script_Select(s_BattleBattlerStepIds[index]);
        work              = SELF(PartyMember);
        work->header.mode = (work->header.mode) + 2;
    }
}
