#include "sce15ef2_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801D0C0C);

MATCH void func_801D0C70(void) {
    u8* work;
    u8* step;

    work                  = (u8*)g_SpadWork;
    work[9]               = 0x10;
    step                  = (u8*)g_SpadWork;
    FIELD(s32, work, 0xC) = 0;
    step[1]++;
}

MATCH void func_801D0CA0(void) {
    Actor* work;
    u8     timer;

    work         = g_SpadWork;
    timer        = work->unk_09 - 1;
    work->unk_0C = work->unk_0C + 0x10;
    work->unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->unk_09 = 0x20;
        g_SpadWork->unk_01 = g_SpadWork->unk_01 + 1;
    }
}

MATCH void func_801D0D00(void) {
    u8 timer;

    timer              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->unk_09 = 0x10;
        g_SpadWork->unk_01 = g_SpadWork->unk_01 + 1;
    }
}

MATCH void func_801D0D5C(void) {
    Actor* work;
    u8     timer;

    work         = g_SpadWork;
    timer        = work->unk_09 - 1;
    work->unk_0C = work->unk_0C - 0x10;
    work->unk_09 = timer;
    if (timer == 0) {
        Actor_Clear();
    }
}

MATCH void func_801D0DA4(void) {
    SYS_DISPATCH_TASK(D_801D1B2C, 1, g_SpadWork);
}

MATCH void func_801D0DE8(void) {
    Actor* work;

    work         = g_SpadWork;
    work->unk_2E = 300;
    work->unk_09 = 0;
    Scene_ClearScanBars();
    g_SpadWork->unk_01 = g_SpadWork->unk_01 + 1;
}

INCLUDE_ASM(func_801D0E30);

MATCH void func_801D0EC4(void) {
    if (!(Scene_StepScanBars(0xF0) & BYTE_MASK)) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801D0EF8);

MATCH void func_801D0F68(void) {
    Actor* work;

    work               = g_SpadWork;
    work->unk_09       = 10;
    work->unk_2E       = 0;
    work->unk_30       = 0;
    g_SpadWork->unk_01 = g_SpadWork->unk_01 + 1;
}

MATCH void func_801D0F9C(void) {
    Actor* work;
    u8     timer;

    work         = g_SpadWork;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->unk_2E = work->unk_2E + 0x15;
    work->unk_30 = work->unk_30 + 9;
    if (timer == 0) {
        g_SpadWork->unk_09 = 0x5A;
        g_SpadWork->unk_01 = g_SpadWork->unk_01 + 1;
    }
}

MATCH void func_801D1008(void) {
    if (g_ScriptVars[0] == 9) {
        g_SpadWork->unk_09 = 0x1E;
        g_SpadWork->unk_01 = g_SpadWork->unk_01 + 1;
    }
}

MATCH void func_801D1050(void) {
    Actor* work;
    u8     timer;

    work         = g_SpadWork;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->unk_2E = work->unk_2E - 7;
    work->unk_30 = work->unk_30 - 3;
    if (timer == 0) {
        Actor_Clear();
    }
}

MATCH void func_801D10A4(void) {
    SYS_DISPATCH_TASK(D_801D1B48, 1, g_SpadWork);
}

MATCH void func_801D10E8(void) {
    u8* work;

    work    = (u8*)g_SpadWork;
    work[9] = 0x10;
    work    = (u8*)g_SpadWork;
    work[1]++;
}

INCLUDE_ASM(func_801D1118);

INCLUDE_ASM(func_801D11A4);

INCLUDE_ASM(func_801D1218);

INCLUDE_ASM(Scene_DrawScanBar);

#include "overlays/scenario/Scene_ClearScanBars.h"

#include "overlays/scenario/Scene_ClaimScanBar.h"

/* Not matched: retail keeps the case constant 1 in v0 apart from the in-use flag in s3; candidates share s3 (first byte difference +0x8C). */
INCLUDE_ASM(Scene_StepScanBars);

INCLUDE_ASM(func_801D17A0);

INCLUDE_ASM(func_801D19A8);
