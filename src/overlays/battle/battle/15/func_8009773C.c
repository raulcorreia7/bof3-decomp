#include "battle_15.h"

MATCH void func_8009773C(void) {
    u8* substate_base;
    u32 substate;

    substate_base = (u8*)(u8*)(PARTY_STATE_PTR);
    substate      = substate_base[0x62E4];
    D_800B43D4[substate + 8u]();
}
