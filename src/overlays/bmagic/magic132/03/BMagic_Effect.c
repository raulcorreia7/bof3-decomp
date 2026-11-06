#include "magic132_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EEDD0);

INCLUDE_ASM(func_801EEEF4);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

MATCH void func_801EF0A4(void) {
    if (g_Task->unk_0B == 0xFF) {
        D_8014637C->unk_29 = 4;
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= 4;
        func_801E5988();
    }
}

MATCH void func_801EF114(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

extern Callback D_801EFD5C[];

MATCH void func_801EF158(void) {
    D_801EFD5C[g_Task->header.step]();
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        if (g_Task->header.step >= 2) {
            g_Task->timer += 1;
        }
        func_801EF4A4();
        func_801EF5B0();
        func_801EF914();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF200);

MATCH void func_801EF324(void) {
    PartyBattler* work;
    u8            count;

    work         = g_Task;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    if (count == 0) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF388(void) {
    s32 phase;

    g_Task->unk_0B = (g_Task->unk_0B - 1) & 0x3F;
    phase          = g_Task->unk_1C + 2;
    g_Task->unk_1C = phase;
    if (phase == 0x80) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF3E0(void) {
    g_Task->unk_0B = (g_Task->unk_0B - 1) & 0x3F;
    g_Task->unk_1C -= 2;
    g_Task->unk_20 -= 2;
    if (g_Task->unk_1C == 0x20) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF44C(void) {
    g_Task->unk_1C -= 1;
    g_Task->unk_20 -= 2;
    if (g_Task->unk_1C == 0) {
        BATTLE_ACTIVE_WORK->unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF4A4);

INCLUDE_ASM(func_801EF5B0);

INCLUDE_ASM(func_801EF914);
