#include "battle_03.h"

MATCH void Battle_PlayEffectSE(u32 effect_index) {
    u32 base;
    u32 addr;

    effect_index &= BYTE_MASK;
    base = D_801EAFD0;
    addr = base + effect_index * 6u;
    SND_PlaySE(*(u16*)((g_Game.current->unk_2C.value * 2u + addr)));
}
