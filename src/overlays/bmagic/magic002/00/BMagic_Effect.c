#include "magic002_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC78);

MATCH void func_801EEDE4(void) {
    if (D_801EC2E0->target.party->unk_09 >= 0x28) {
        g_Task->header.mode++;
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEE64(void) {
    BMagic_DispatchTaskPair(func_801EEEBC, func_801EEF84);
}

MATCH void func_801EEEBC(void) {
    PartyMember* work;
    PartyMember* draw;

    work = g_Task;
    work->unk_14 += 0x100;
    work->unk_18 += 4;
    work->unk_0C += work->unk_1C;
    work->unk_09++;
    work->unk_10 += work->unk_20;
    draw = g_Task;
    func_801EF1FC(draw->unk_0C >> 16, draw->unk_10 >> 16, (draw->unk_18 << 15) >> 16, draw->unk_14, draw->unk_60, draw->unk_58);
    if (g_Task->unk_09 >= 0xB) {
        g_Task->header.mode++;
    }
}

INCLUDE_ASM(func_801EEF84);

MATCH void func_801EF030(s32 x, s32 y, u16 radius, s32 phase) {
    SVECTOR  points[6];
    POLY_F3* prim;
    s32      angle;
    u16      tpage;
    u8       i;

    for (i = 0; i < 6; i++) {
        angle        = (i << 12) / 6 + (u16)phase;
        points[i].vx = x + ((rsin(angle) * radius) >> 12);
        points[i].vy = y + ((rcos(angle) * radius) >> 12);
    }
    tpage = GetTPage(0x3C0, 0x100, 0, 0);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
    GFX_AddPrim(1, sizeof(DR_MODE));
    for (i = 0; i < 2; i++) {
        prim = (POLY_F3*)g_GfxPrimCursor;
        SetPolyF3(prim);
        setXY3(prim, points[i].vx, points[i].vy, points[i + 2].vx, points[i + 2].vy, points[i + 4].vx, points[i + 4].vy);
        setRGB0(prim, 0xFF, 0xFF, 0);
        SetSemiTrans(prim, 1);
        GFX_AddPrim(1, sizeof(POLY_F3));
    }
}

INCLUDE_ASM(func_801EF1FC);
