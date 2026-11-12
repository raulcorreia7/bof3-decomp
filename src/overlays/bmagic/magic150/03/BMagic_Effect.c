#include "magic150_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC20.h"

INCLUDE_ASM(func_801EECA4);

MATCH void func_801EED60(void) {
    u8 timer;

    func_801EF6F8();
    func_801EF8EC();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EEDCC(void) {
    if (func_801EF8EC() == 0) {
        g_Task->unk_09      = 4;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EEE24(void) {
    s16* radius;
    u8   timer;

    radius = &D_801EFAAC;
    *radius += 0x40;
    D_801EFAAE += 0x60;
    func_801EF254();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09 = 120;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
}

MATCH void func_801EEEC4(void) {
    u8 count;

    D_801EFAAC = ((g_FrameCount & 0x1) * 0x10) + 0x100;
    D_801EFAB0 -= 0x200;
    func_801EF254();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->unk_09 = 4;
        g_Task->header.mode += 1;
        Battle_MarkDamaged(g_Battle.target_selector);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
    }
}

INCLUDE_ASM(func_801EEF80);

#include "shared/Effect_StartPlaying.h"

INCLUDE_ASM(func_801EF040);

MATCH void func_801EF254(void) {
    GFX_AddDrawMode(GetTPage(0, 1, 0x2C0, 0x100) & HALF_MASK);
    func_801AFE18();
    func_801EF040();
    func_801EF4E0();
}

/* Projects the point and the points half a unit to its left and right to the screen. */
/* func_801EF2C0 */
MATCH void BMagic_ProjectSpan(ProjectedSpan* span) {
    Area_ProjectPoint(span->pos, &span->screen[1]);
    span->pos[0] -= COORD_HALF;
    Area_ProjectPoint(span->pos, &span->screen[0]);
    span->pos[0] += TO_COORD(1);
    Area_ProjectPoint(span->pos, &span->screen[2]);
}

INCLUDE_ASM(func_801EF324);

INCLUDE_ASM(func_801EF4E0);

MATCH void func_801EF6B0(void) {
    u8   i;
    u16* work;

    D_801EFAF4 = D_801EFAB4;
    i          = 0;
    do {
        work = (u16*)D_801EFAF4;
        i++;
        *work = 0;
        work += 4;
        D_801EFAF4 = (u8*)work;
    } while (i < 8);
}

INCLUDE_ASM(func_801EF6F8);

MATCH void func_801EF790(s32 x, s32 y, s16 radius, u8 colour, u8 alpha) {
    POLY_G3* prim;
    u16      angle;
    u16      next;

    for (angle = 0; angle < ONE; angle += 0x100) {
        prim     = GFX_BeginPolyG3(1);
        prim->x0 = x;
        prim->y0 = y;
        prim->x1 = x + FIXED_MUL(radius, rcos(angle));
        prim->y1 = y + FIXED_MUL(radius, rsin(angle));
        next     = angle + 0x100;
        prim->x2 = x + FIXED_MUL(radius, rcos(next));
        prim->y2 = y + FIXED_MUL(radius, rsin(next));
        setRGB0(prim, colour, 0, 0);
        setRGB1(prim, alpha, 0, 0);
        setRGB2(prim, alpha, 0, 0);
        GFX_AddPrim(1, sizeof(POLY_G3));
    }
}

INCLUDE_ASM(func_801EF8EC);
