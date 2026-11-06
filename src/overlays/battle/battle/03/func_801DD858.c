#include "battle_03.h"

MATCH void func_801DD858(u32 effect_index) {
    u32 base;
    u32 addr;

    effect_index &= 0xFF;
    base = D_801EAFD0;
    addr = base + effect_index * 6u;
    SND_PlayCue(*(u16*)((g_GameState->unk_2C.half * 2u + addr)));
}
