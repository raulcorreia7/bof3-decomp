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

INCLUDE_ASM(func_801D1540);

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

INCLUDE_ASM(func_801D1A20);

INCLUDE_ASM(func_801D1C1C);
