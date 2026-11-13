#include "sce15ef0_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801D0C48(void) {
    g_Task->pos.x      = TO_COORD(48) + COORD_HALF;
    g_Task->pos.y      = TO_COORD(116);
    g_Task->pos.z      = Area_SampleHeight(g_Task->pos.x, TO_COORD(116)) << 16;
    g_Task->counter_0C = 0x308000;
    g_Task->counter_10 = 0x718000;
    g_Task->field_14   = 0xFEC00000;
    g_Task->origin_x   = 0;
    g_Task->color_r    = 0;
    g_Task->timer      = 8;
    g_Task->header.mode += 1;
}

MATCH void func_801D0CEC(void) {
    Sce15ef0Work* work = g_Task;

    work->color_r += 8;
    work->origin_x += 0x10;
    func_801D1C1C(&g_Task->pos.x, &g_Task->counter_0C, g_Task->color_r);
    func_801D1A20(&g_Task->pos.x, g_Task->origin_x, 2);

    if (TIMER_EXPIRED(g_Task->timer)) {
        g_Task->timer = 60;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 13));
    }
}

MATCH void func_801D0DB0(void) {
    func_801D1C1C(&g_Task->pos.x, &g_Task->counter_0C, g_Task->color_r);
    func_801D1A20(&g_Task->pos.x, g_Task->origin_x, 2);

    if (TIMER_EXPIRED(g_Task->timer)) {
        g_Task->color_g = 0;
        g_Task->timer   = 4;
        g_Task->header.mode += 1;
    }
}

INCLUDE_ASM(func_801D0E5C);

MATCH void func_801D0F44(void) {
    g_Task->color_g -= 0x40;
    func_801D1220(g_Task->color_g);
    func_801D1C1C(&g_Task->pos.x, &g_Task->counter_0C, g_Task->color_r);
    func_801D1A20(&g_Task->pos.x, g_Task->origin_x, 2);
    func_801D1914(64);

    if (TIMER_EXPIRED(g_Task->timer)) {
        g_Task->timer = 60;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D101C(void) {
    func_801D1C1C(&g_Task->pos.x, &g_Task->counter_0C, g_Task->color_r);
    func_801D1A20(&g_Task->pos.x, g_Task->origin_x, 2);
    func_801D1914(64);

    if (TIMER_EXPIRED(g_Task->timer)) {
        g_Task->timer = 60;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
    }
}

MATCH void func_801D10C4(void) {
    if ((s16)g_Task->origin_x > 0) {
        g_Task->origin_x -= 0x10;
    }
    if ((s8)g_Task->color_r > 0) {
        g_Task->color_r -= 8;
    }
    func_801D1C1C(&g_Task->pos.x, &g_Task->counter_0C, g_Task->color_r);
    func_801D1A20(&g_Task->pos.x, g_Task->origin_x, 2);
    func_801D1914(64);

    if (TIMER_EXPIRED(g_Task->timer)) {
        g_Task->timer    = 16;
        g_Task->origin_x = 0x40;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D11B4(void) {
    func_801D1914(g_Task->origin_x -= 4);

    if (TIMER_EXPIRED(g_Task->timer)) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801D1220);

INCLUDE_ASM(func_801D1370);

MATCH void func_801D1540(s32 x, s32 y, s16 radius, u16 angle) {
    POLY_G3* prim;
    u8       i;

    i = 0;
    do {
        prim     = GFX_BeginPolyG3(1);
        prim->x0 = x;
        prim->y0 = y;
        prim->x1 = x + FIXED_MUL(radius, rcos(angle));
        prim->y1 = y + FIXED_MUL(radius, rsin(angle));
        angle += 0x100;
        prim->x2 = x + FIXED_MUL(radius, rcos(angle));
        i += 1;
        prim->y2 = y + FIXED_MUL(radius, rsin(angle));
        setRGB0(prim, 64, 0, 0);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        GFX_AddPrim(3, sizeof(POLY_G3));
    } while (i < 8);
}

INCLUDE_ASM(func_801D1690);

MATCH void func_801D1914(s16 amount) {
    VECTOR start;
    VECTOR end;

    start.vx = TO_COORD(48) + COORD_HALF;
    start.vy = TO_COORD(113) + COORD_HALF;
    start.vz = TO_COORD(-768);
    end.vx   = TO_COORD(48) + COORD_HALF;
    end.vy   = TO_COORD(113) + COORD_HALF;
    end.vz   = TO_COORD(-512);
    func_801D1370(&start, &end, amount);

    start.vx = TO_COORD(48);
    start.vy = TO_COORD(113) + COORD_HALF;
    start.vz = TO_COORD(-384);
    func_801D1370(&start, &end, amount);

    end.vx = TO_COORD(48);
    end.vy = TO_COORD(113) + COORD_HALF;
    end.vz = TO_COORD(-256);
    func_801D1370(&start, &end, amount);

    start.vx = TO_COORD(48) + COORD_HALF;
    start.vy = TO_COORD(113) + COORD_HALF;
    start.vz = TO_COORD(-128);
    func_801D1370(&start, &end, amount);

    end.vx = TO_COORD(48) + COORD_HALF;
    end.vy = TO_COORD(113) + COORD_HALF;
    end.vz = 0;
    func_801D1370(&start, &end, amount);
}

MATCH void func_801D1A20(s32* pos, s16 origin, s32 flags) {
    DVECTOR  screen;
    DVECTOR  point;
    DVECTOR  size;
    DVECTOR  scale;
    MATRIX   camera;
    POLY_G3* primitive;
    s32      angle;
    s32      i;

    GFX_AddDitheredDrawMode(2u, GetTPage(0, 1, 0x2C0, 0x100));
    Area_SetCameraMatrix(&camera);
    Area_ProjectPoint(pos, &screen);
    size.vx = size.vy = origin;
    Game_ProjectWorldPoint(pos, &size, &scale);
    scale.vx += g_FrameCount & 1;
    point.vx = screen.vx + scale.vx;
    point.vy = screen.vy;
    angle    = 0;
    i        = 0;
    do {
        primitive     = GFX_BeginPolyG3(1);
        primitive->x0 = screen.vx;
        primitive->y0 = screen.vy;
        primitive->x1 = point.vx;
        primitive->y1 = point.vy;
        angle += 128;
        point.vx      = screen.vx + (((s16)scale.vx * rcos((u16)angle)) >> 0xC);
        point.vy      = screen.vy + (((s16)scale.vx * rsin((u16)angle)) >> 0xC);
        primitive->x2 = point.vx;
        primitive->y2 = point.vy;
        setRGB0(primitive, (flags & 4) << 5, (flags & 2) << 6, (flags & 1) << 7);
        setRGB1(primitive, 0, 0, 0);
        setRGB2(primitive, 0, 0, 0);
        GFX_AddPrim(2u, sizeof(POLY_G3));
        i += 1;
    } while ((i & BYTE_MASK) < 32U);
}

INCLUDE_ASM(func_801D1C1C);
