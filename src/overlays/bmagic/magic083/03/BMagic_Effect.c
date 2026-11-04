#include "magic083_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH s32 func_801EF0CC(void) {
    if (*((u8*)&g_BattleActionType) != 4 && *((u16*)&g_BattleActionId) == 0x136) {
        g_BattleActionId = 0x53;
    }
    return 0;
}

MATCH void func_801EF108(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF14C(void) {
    SYS_DISPATCH_BYTE(D_801F0EF0, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EFB24();
        func_801EF844();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF1DC);

INCLUDE_ASM(func_801EF2F8);

MATCH void func_801EF528(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->word_08.byte.unk_0B == 0) {
        work->unk_02++;
    }
}

INCLUDE_ASM(func_801EF55C);

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF844);

INCLUDE_ASM(func_801EFB24);

MATCH void func_801EFE54(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 6), 1, g_SpadWork);
}

MATCH void func_801EFE98(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 7), 2, g_SpadWork);
}

INCLUDE_ASM(func_801EFEDC);

INCLUDE_ASM(func_801F0010);

INCLUDE_ASM(func_801F0104);

MATCH void func_801F01F8(void) {
    s32 value;
    s32 value2;
    s32 value3;
    u8  value4;
    u8  value5;

    func_800AF764();
    if ((g_SpadWork->unk_0C == 4) && ((u8)g_SpadWork->word_08.byte.unk_0A < 5U)) {
        value2 = (rand() & 3) | 0x40;
    } else {
        value2 = (rand() & 3) | 0x18;
    }
    func_801F0BA8(value2);
    Effect_SetActorMatrix();
    func_801F050C();
    PopMatrix();
    if (g_SpadWork->unk_0C < 4) {
        value              = g_SpadWork->unk_10 + 1;
        g_SpadWork->unk_10 = value;
        if (!(value & 7)) {
            g_SpadWork->unk_0C += 1;
        }
    }
    g_SpadWork->word_08.byte.unk_09 += g_SpadWork->unk_0C;
    if (g_SpadWork->unk_0C == 4) {
        value4                          = g_SpadWork->word_08.byte.unk_0A - 1;
        g_SpadWork->word_08.byte.unk_0A = value4;
        if (!(value4 & 0xFF)) {
            value5 = g_SpadWork->unk_03;
            if (!(value5 & 0xF0)) {
                value3 = 0x102;
                if (value5 & 1) {
                    value3 = 0x101;
                }
                SND_QueueSelectionFx(value3);
            }
            g_SpadWork->unk_10 = 8;
            g_SpadWork->unk_14 = 8;
            g_SpadWork->unk_20 = 8;
            g_SpadWork->unk_02 += 1;
        }
    }
}

INCLUDE_ASM(func_801F038C);

INCLUDE_ASM(func_801F050C);

INCLUDE_ASM(func_801F0BA8);

/* func_801F0DC0 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0E24 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
