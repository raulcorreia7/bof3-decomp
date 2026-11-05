#include "magic060_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC34(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EECA4);

MATCH void func_801EED68(void) {
    u32           slot;
    PartyBattler* work;

    if (g_SpadWork->word_08.byte.unk_0B == 2) {
        slot                               = Battle_AllocEffect(1, 0x12) & BYTE_MASK;
        work                               = g_SpadWork;
        g_BattleEffects[slot].unk_01       = 2;
        g_BattleEffects[slot].target.party = work;
        g_SpadWork->word_08.byte.unk_09    = 0x10;
        g_SpadWork->step_01                = g_SpadWork->step_01 + 1;
    }
}

MATCH void func_801EEE00(void) {
    u8 temp_v0;

    if ((u8)g_BattleTargetSelector < 3U) {
        func_801EF174();
    } else {
        func_801EF2DC();
    }
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->step_01 += 1;
    }
}

MATCH void func_801EEE84(void) {
    if (g_BattleTargetSelector < 3) {
        func_801EF174();
    } else {
        func_801EF2DC();
    }
    if (g_InputPressed != 0) {
        g_SpadWork->word_08.byte.unk_0B = 0x83;
        g_SpadWork->step_01++;
    }
}

MATCH void func_801EEF04(void) {
    u16* flags;

    if (g_SpadWork->word_08.byte.unk_0B == 0x80) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EEF50);

INCLUDE_ASM(func_801EF0B8);

INCLUDE_ASM(func_801EF118);

INCLUDE_ASM(func_801EF174);

INCLUDE_ASM(func_801EF2DC);

INCLUDE_ASM(func_801EF470);

INCLUDE_ASM(func_801EF590);

INCLUDE_ASM(func_801EF76C);

INCLUDE_ASM(func_801EF924);

INCLUDE_ASM(func_801EFB00);

INCLUDE_ASM(func_801EFCE8);

MATCH void func_801EFF44(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EFF88(void) {
    SYS_DISPATCH_BYTE(D_801F0BBC, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F012C();
    }
}

#include "overlays/bmagic/Effect_ClearTimerNextStep.h"

MATCH void func_801F0030(void) {
    u8 temp_v1;

    temp_v1                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x10) {
        D_801EB4E0->word_08.byte.unk_0B = 1;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F0090(void) {
    PartyBattler* work;

    work = (PartyBattler*)D_801EB4E0;
    if (work->word_08.byte.unk_0B == 0x83) {
        g_SpadWork->unk_02++;
    }
}

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801F012C);

MATCH void func_801F0254(void) {
    SYS_DISPATCH_BYTE(D_801F0BCC, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F0428();
    }
}

MATCH void func_801F02CC(void) {
    if (D_801EB4E0->word_08.byte.unk_0B == 1) {
        g_SpadWork->word_08.byte.unk_09 = 0;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F031C(void) {
    u8 temp_v1;

    temp_v1                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x1E) {
        D_801EB4E0->word_08.byte.unk_0B = 2;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F037C(void) {
    PartyBattler* work;

    work = (PartyBattler*)D_801EB4E0;
    if (work->word_08.byte.unk_0B == 0x83) {
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801F03BC(void) {
    PartyBattler* active;

    g_SpadWork->word_08.byte.unk_09 = g_SpadWork->word_08.byte.unk_09 - 2;
    if (g_SpadWork->word_08.byte.unk_09 == 0) {
        active                      = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B = active->word_08.byte.unk_0B - 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0428);

MATCH void func_801F07E8(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs + 11, 2, g_SpadWork);
}

MATCH void func_801F082C(void) {
    PartyBattler** actor;

    actor = &g_BattleSelectedActor;
    func_80196718(*actor);
    g_SpadWork->word_08.byte.unk_0B = func_8019651C(*actor, 0, 0, 0, 1);
    g_SpadWork->word_08.byte.unk_09 = 0;
    g_SpadWork->unk_02 += 1;
}

INCLUDE_ASM(func_801F08B8);

INCLUDE_ASM(func_801F09E0);
