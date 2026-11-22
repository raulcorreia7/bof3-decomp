#include "magic130_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEF18(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    D_801EFA4C[TASK(PartyMember)->header.step]();
    if ((TASK(PartyMember)->header.flags & ACTOR_FLAG_IN_USE) && (TASK(PartyMember)->header.step != 0)) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EEFB4(void) {
    PartyMember* work;
    PartyMember* next;
    u8           flag;
    s8           shade;

    flag                      = 1;
    shade                     = -0x80;
    work                      = g_Task;
    work->screen_x.value      = 0xDC;
    work->unk_25              = 0x1D;
    next                      = g_Task;
    work->screen_y.value      = 0x6E;
    next->unk_26              = 0;
    TASK(PartyMember)->unk_27 = 0x1A;
    TASK(PartyMember)->unk_28 = flag;
    TASK(PartyMember)->unk_24 = 0x80;
    {
        PartyMember* task;

        task          = g_Task;
        task->unk_48  = 0;
        task->scale.x = 0x10000;
        task->scale.y = 0x10000;
    }
    TASK(PartyMember)->header.flags |= 0x20;
    TASK(PartyMember)->unk_5C       = flag;
    TASK(PartyMember)->unk_5D       = shade;
    TASK(PartyMember)->unk_5E       = shade;
    TASK(PartyMember)->unk_5F       = shade;
    TASK(PartyMember)->unk_2A       = 0;
    TASK(PartyMember)->unk_29       = 3;
    TASK(PartyMember)->unk_2C.value = 0;
    TASK(PartyMember)->unk_2B       = flag;
    Script_Select(0);
    TASK(PartyMember)->unk_09 = 0x3C;
    TASK(PartyMember)->timer  = 0xFF;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF10C(void) {
    TASK(PartyMember)->unk_5D += 8;
    TASK(PartyMember)->unk_5E += 8;
    TASK(PartyMember)->unk_5F += 8;
    if ((s8)TASK(PartyMember)->unk_5D == 0) {
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountDownTimerStep.h"

MATCH void func_801EF1E0(void) {
    TASK(PartyMember)->unk_5D -= 8;
    TASK(PartyMember)->unk_5E -= 8;
    TASK(PartyMember)->unk_5F -= 8;
    if ((s8)TASK(PartyMember)->unk_5D == -0x80) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void func_801EF284(void) {
    SYS_DISPATCH_BYTE(D_801EFA5C, TASK(PartyMember)->header.step);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_FOREGROUND, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        func_801EF4D4();
        func_801EF730();
    }
}

MATCH void func_801EF354(void) {
    PartyMember* task;
    u16          value;

    task                     = g_Task;
    task->screen_x.value     = task->param.unk_0B * 26 + 0x98;
    value                    = D_801EFA6C[task->param.unk_0B];
    task->unk_14             = 0x20;
    task->unk_09             = 0x3C;
    task->screen_y.value     = value + 0x50;
    TASK(PartyMember)->timer = 0;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF3DC(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(timer, 1, 16);
}

MATCH void Effect_CountDownTimerStep2(void) {
    BMAGIC_COUNT_DOWN_TIMER_STEP();
}

#include "overlays/bmagic/shared/Effect_CountDownAndFinish.h"

MATCH void func_801EF4D4(void) {
    POLY_G3* prim;
    s32      i;

    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_14;
    g_ScratchPad.cells.halves[2] = TASK(PartyMember)->timer * 8;
    g_ScratchPad.cells.halves[3] = TASK(PartyMember)->timer * 8;
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->timer * 4;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->timer * 8;
    g_ScratchPadVectors[0].vx    = TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[0].vy    = TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    for (i = 1; i < 9; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, TASK(PartyMember)->screen_x.value, TASK(PartyMember)->screen_y.value, g_ScratchPadVectors[0].vx, g_ScratchPadVectors[0].vy,
               g_ScratchPadVectors[0].vx = TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]),
               g_ScratchPadVectors[0].vy = TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]));
        setRGB0(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G3));
    }
}

MATCH void func_801EF730(void) {
    POLY_G4* prim;
    s32      i;

    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_14;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_14 * 2 + (rand() & 7);
    g_ScratchPadVectors[0].vx    = TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[0].vy    = TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[1].vx    = TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    for (i = 1; i < 9; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, g_ScratchPadVectors[0].vx, g_ScratchPadVectors[0].vy);
        prim->x2 = g_ScratchPadVectors[1].vx;
        prim->y2 = g_ScratchPadVectors[1].vy;
        prim->x1 = g_ScratchPadVectors[0].vx = TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[1]);
        prim->y1 = g_ScratchPadVectors[0].vy = TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[1]);
        prim->x3 = g_ScratchPadVectors[1].vx = TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]);
        prim->y3 = g_ScratchPadVectors[1].vy = TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));
    }
}
