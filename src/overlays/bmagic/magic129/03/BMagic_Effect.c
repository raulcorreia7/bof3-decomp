#include "magic129_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF80(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEFC4);

INCLUDE_ASM(func_801EF058);

INCLUDE_ASM(func_801EF38C);

INCLUDE_ASM(func_801EF3DC);

/* needs: type. Effect_TickOnTimerZero shape on work byte 0x5D with a signed zero test (sll 24, bnez) where PartyBattler.unk_5D is u8; first differing instruction is andi v0,v0,0xff against sll v0,v0,24. */
INCLUDE_ASM(func_801EF4F0);

INCLUDE_ASM(func_801EF54C);

MATCH void func_801EFF40(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 5), 1, g_SpadWork);
}

INCLUDE_ASM(func_801EFF84);

MATCH void func_801F00D4(void) {
    s32 value;
    s32 value2;
    u8  value3;

    value3             = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = value3;
    if (!(value3 & 0xFF)) {
        g_SpadWork->unk_14         = 0x40000;
        g_SpadWork->unk_20         = 0x20000;
        value2                     = (rand() & 0xF) + 0x1C;
        value                      = (g_SpadWork->unk_0B & 0x1F) << 7;
        g_SpadWork->coord_x_34.raw = D_801EB4E0->coord_x_34.raw + (rsin(value) * value2);
        g_SpadWork->coord_y_38.raw = D_801EB4E0->coord_y_38.raw + (rcos(value) * value2);
        g_SpadWork->word_3C.word   = D_801EB4E0->word_3C.word;
        g_SpadWork->unk_5D         = (rand() & 7) + 5;
        g_SpadWork->unk_5E         = (rand() & 7) + 5;
        g_SpadWork->unk_5F         = (rand() & 7) + 5;
        g_SpadWork->unk_09         = 0x10;
        g_SpadWork->unk_0A         = 0x10;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801F023C);

INCLUDE_ASM(func_801F029C);

INCLUDE_ASM(func_801F030C);

/* func_801F0500 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0564 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
