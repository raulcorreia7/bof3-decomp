#include "magic151_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EECB0);

MATCH void func_801EEDE0(void) {
    Callback handlers[2] = {func_801EEE38, func_801EF318};

    SYS_DISPATCH_TASK(handlers, 2, g_SpadWork);
}

MATCH void func_801EEE38(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_TASK(handlers.handlers, 3, g_SpadWork);
}

INCLUDE_ASM(func_801EEEA8);

INCLUDE_ASM(func_801EEF24);

INCLUDE_ASM(func_801EF070);

INCLUDE_ASM(func_801EF138);

INCLUDE_ASM(func_801EF2A0);

MATCH void func_801EF318(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC24;
    SYS_DISPATCH_TASK(handlers.handlers, 3, g_SpadWork);
}

INCLUDE_ASM(func_801EF388);

INCLUDE_ASM(func_801EF484);

INCLUDE_ASM(func_801EF938);

MATCH void func_801EF9F0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EFA34(void) {
    BmagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC38, unk_02);
}

INCLUDE_ASM(func_801EFAAC);

INCLUDE_ASM(func_801EFBAC);

INCLUDE_ASM(func_801EFC68);

MATCH void func_801EFD24(void) {
    u8 count;

    count              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->unk_0B = 1;
        g_SpadWork->unk_02         = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EFD80(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->step_01 == 2) {
        work         = SP_REF(PartyBattler*, 0x44u);
        work->unk_02 = work->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EFDC0);

MATCH void func_801EFE00(void) {
    SYS_DISPATCH_BYTE(D_801F24B8, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801F026C();
        func_801F0648();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EFE90);

MATCH void func_801EFF44(void) {
    u8 timer;

    timer              = g_SpadWork->unk_09 + 2;
    g_SpadWork->unk_09 = timer;
    if (timer == 32) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EFF94);

MATCH void func_801F00B4(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->unk_0B == 0) {
        work->unk_02++;
    }
}

INCLUDE_ASM(func_801F00E8);

INCLUDE_ASM(func_801F013C);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F026C);

INCLUDE_ASM(func_801F0648);

INCLUDE_ASM(func_801F0AC8);

INCLUDE_ASM(func_801F0BA8);

INCLUDE_ASM(func_801F0C50);

INCLUDE_ASM(func_801F0CB0);

INCLUDE_ASM(func_801F0D0C);

INCLUDE_ASM(func_801F10E8);

INCLUDE_ASM(func_801F11E0);

INCLUDE_ASM(func_801F129C);

MATCH void func_801F1318(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->unk_0B++;
    work = g_SpadWork;
    work->unk_09--;
    if (work->unk_09 == 0) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

MATCH void func_801F1380(void) {
    PartyBattler* active;

    g_SpadWork->unk_0B = g_SpadWork->unk_0B + 1;
    g_SpadWork->unk_0A = g_SpadWork->unk_0A - 2;
    if (g_SpadWork->unk_0A == 0) {
        active         = BATTLE_ACTIVE_WORK;
        active->unk_0B = active->unk_0B - 1;
        func_801E5988();
    }
}

MATCH void func_801F1408(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    if (g_SpadWork->unk_08 & 1) {
        rot.vz = ONE / 4;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_SpadWork);
}

INCLUDE_ASM(func_801F14D0);

MATCH void func_801F1C3C(void) {
    SYS_DISPATCH_BYTE(D_801F250C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F1DC0();
        func_801F1E70();
        func_801F2188();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F1CCC);

MATCH void func_801F1D28(void) {
    PartyBattler* work;
    s32           value;

    work         = g_SpadWork;
    value        = work->unk_14 + 0x80;
    work->unk_14 = value;
    if (value == 0x400) {
        work->unk_02++;
    }
}

INCLUDE_ASM(func_801F1D60);

MATCH void Effect_SetActorMatrix_801F1DC0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

INCLUDE_ASM(func_801F1E70);

INCLUDE_ASM(func_801F2188);
