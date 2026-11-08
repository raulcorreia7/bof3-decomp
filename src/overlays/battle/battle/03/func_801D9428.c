#include "battle_03.h"

MATCH void func_801D9428(u8 index) {
    volatile u8*  state8;
    volatile u16* state16;

    Menu_OpenPanelTask(4, 3);
    state8          = (u8*)(EFFECT_BANK_80140000);
    state16         = BATTLE_GLOBAL_RAM_U16;
    state8[0x83C2]  = 3;
    state16[0x41E2] = 0x7C;
    state8[0x83C3]  = index;
    state16[0x41E3] = 0x2A;
}
