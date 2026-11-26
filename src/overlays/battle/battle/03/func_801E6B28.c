#include "battle_03.h"

MATCH void func_801E6B28(void) {
    volatile u8* global;
    u32          type;

    Area_SceneSelectRecord(0x18);
    SELF(PartyMember)->unk_24 = 0x80;
    SELF(PartyMember)->unk_2A = 0;
    global                    = (u8*)(PARTY_STATE_PTR);
    type                      = *(u16*)((*(u32*)((global + 0x6380u)) + 2u));
    if ((D_801CA71C[type].mask & 0x200u) != 0u) {
        Script_Select(0);
    } else {
        Script_Select(2);
    }
    SELF(PartyMember)->header.mode += 1;
}
