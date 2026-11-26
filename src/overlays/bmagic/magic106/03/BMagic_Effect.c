#include "magic106_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved;
    PartyMember* swap;
    s32          count;

    BMagic_DispatchTaskPair(func_801EECE4, Effect_MarkDamagedOnZeroTick);
    count = 0;
    do {
        if (D_801EF9F8[(u8)count << 5] & 0x1) {
            saved                 = g_BattleEffectBattler;
            swap                  = FIELD(PartyMember*, D_801EFA14, (u8)count << 5);
            g_BMagicOrbit         = D_801EF9F8 + ((u8)count << 5);
            g_BattleEffectBattler = swap;
            func_801EEEE0();
            g_BattleEffectBattler = saved;
        }
        count += 1;
    } while ((u8)count < 96);
}

MATCH void func_801EECE4(void) {
    PartyMember* work;
    u8           i;
    u32          row;
    u8           growth;
    u8           slot;

    for (i = 0; i < 96; i++) {
        D_801EF9F8[i << 5]       = 0;
        D_801EF9F8[(i << 5) + 1] = 0;
        D_801EF9F8[(i << 5) + 2] = 0;
    }
    work                      = TASK(PartyMember);
    work->pos.x.fixed         = g_Battle.selected_actor->pos.x.fixed;
    work->pos.y.fixed         = g_Battle.selected_actor->pos.y.fixed;
    work->pos.z.fixed         = g_Battle.selected_actor->pos.z.fixed + TO_COORD(256);
    work->param.unk_0B        = 0;
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->header.mode += 1;
    for (i = 0; i < 96; i++) {
        slot                  = func_801EF914();
        row                   = slot << 5;
        D_801EFA14[slot << 3] = TASK(PartyMember);
        D_801EF9F8[row + 1]   = 0;
        D_801EF9F8[row + 4]   = i;
        growth                = ((i >> 1) & 0x70) + (rand() & 0xF) + 1;
        D_801EF9F8[row + 10]  = growth;
        D_801EF9F8[row + 8]   = 0x40 - growth;
        TASK(PartyMember)->param.unk_0B += 1;
    }
    SND_SEQueueSelection(0x100);
    SND_SEQueueSelection(0x101);
}
