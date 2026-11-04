#include "magic054_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC2C(void) {
    BattleResultRings table;

    table = D_801EEC04;
    SYS_DISPATCH_TASK(table.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC98);

INCLUDE_ASM(func_801EF05C);

#include "shared/Effect_StartPlaying.h"

#include "overlays/bmagic/Effect_CountDownAndPlay.h"

MATCH void func_801EF158(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF19C);

INCLUDE_ASM(func_801EF238);

INCLUDE_ASM(func_801EF3A4);

INCLUDE_ASM(func_801EF43C);

INCLUDE_ASM(func_801EF4A8);

MATCH void func_801EF534(void) {
    u8 value;
    u8 value2;

    if (func_8014DAEC() & 0xFF) {
        if (g_BattleTargetSelector & 0x40) {
            value2                    = g_SpadWork->unk_0B;
            D_801EB630[value2].unk_00 = D_801EB630[value2].unk_00 & 0xBF;
        } else {
            value                                 = g_SpadWork->unk_0B;
            g_BattlePartyBattlers[value].flags_00 = g_BattlePartyBattlers[value].flags_00 & 0xBF;
        }
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF624(void) {
    BMAGIC_TICK_EFFECT_WORK();
    func_801E5988();
}
