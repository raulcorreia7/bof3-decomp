#include "magic144_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEE9C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEEE0(void) {
    SYS_DISPATCH_BYTE(D_801F04D4, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EF294();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEF68);

INCLUDE_ASM(func_801EF078);

#include "overlays/bmagic/Effect_StepOnOwnTickFlag.h"

MATCH void func_801EF154(void) {
    u8 temp_v0;

    temp_v0 = g_SpadWork->word_08.byte.unk_09;
    if (temp_v0 != 0) {
        g_SpadWork->word_08.byte.unk_09 = temp_v0 - 1;
    }
    if (g_SpadWork->word_08.byte.unk_0B == 0x80) {
        func_80196718(g_BattleSelectedActor);
        func_800AF814(g_BattleTargetSelector);
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF294);

MATCH void func_801EF510(void) {
    SYS_DISPATCH_TASK(D_801F04E4, 1, g_SpadWork);
}

MATCH void func_801EF554(void) {
    SYS_DISPATCH_BYTE(D_801F04EC, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_800AF764();
        func_801EF818();
    }
}

INCLUDE_ASM(func_801EF5D4);

INCLUDE_ASM(func_801EF654);

INCLUDE_ASM(func_801EF6A4);

INCLUDE_ASM(func_801EF738);

INCLUDE_ASM(func_801EF818);

INCLUDE_ASM(func_801EFF74);

INCLUDE_ASM(func_801F0034);

INCLUDE_ASM(func_801F00A0);

#include "overlays/bmagic/Effect_StepOnTickFlag.h"

MATCH void func_801F0134(void) {
    u8 counter;

    counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if (!(counter & 0xFF)) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        g_SpadWork->flags_00 = 0;
        g_SpadWork->step_01  = 0;
        g_SpadWork->unk_02   = 0;
        g_SpadWork->unk_03   = 0;
        g_SpadWork->unk_04   = 0;
    }
}

INCLUDE_ASM(func_801F01D0);

/* func_801F046C */
#include "overlays/bmagic/BMagic_AllocEffect.h"
