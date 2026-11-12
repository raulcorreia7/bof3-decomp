#include "battle_03.h"

MATCH void func_801E6B28(void) {
    volatile u8* global;
    u32          kind;

    Area_SelectSceneRecord(0x18);
    g_Task->unk_24 = 0x80;
    g_Task->unk_2A = 0;
    global         = (u8*)(PARTY_STATE_PTR);
    kind           = *(u16*)((*(u32*)((global + 0x6380u)) + 2u));
    if ((D_801CA71C[kind].mask & 0x200u) != 0u) {
        Actor_SelectScript(0);
    } else {
        Actor_SelectScript(2);
    }
    g_Task->header.mode += 1;
}
