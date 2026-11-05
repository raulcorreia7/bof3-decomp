#include "sce15ef0_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801D0C0C(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801D1F88[entity[1]]();
}

MATCH void func_801D0C48(void) {
    g_SpadWork->pos_x      = 0x308000;
    g_SpadWork->pos_y      = 0x740000;
    g_SpadWork->pos_z      = Area_SampleHeight(g_SpadWork->pos_x, 0x740000) << 16;
    g_SpadWork->counter_0C = 0x308000;
    g_SpadWork->counter_10 = 0x718000;
    g_SpadWork->field_14   = 0xFEC00000;
    g_SpadWork->origin_x   = 0;
    g_SpadWork->color_r    = 0;
    g_SpadWork->timer      = 8;
    g_SpadWork->step += 1;
}

MATCH void func_801D0CEC(void) {
    Sce15ef0Work* work = g_SpadWork;

    work->color_r += 8;
    work->origin_x += 0x10;
    func_801D1C1C(&g_SpadWork->pos_x, &g_SpadWork->counter_0C, g_SpadWork->color_r);
    func_801D1A20(&g_SpadWork->pos_x, (s16)g_SpadWork->origin_x, 2);

    if (TIMER_EXPIRED(g_SpadWork->timer)) {
        g_SpadWork->timer = 0x3C;
        g_SpadWork->step += 1;
        SND_PlayCue(EMI_CUE_ID(2, 13));
    }
}

MATCH void func_801D0DB0(void) {
    func_801D1C1C(&g_SpadWork->pos_x, &g_SpadWork->counter_0C, g_SpadWork->color_r);
    func_801D1A20(&g_SpadWork->pos_x, (s16)g_SpadWork->origin_x, 2);

    if (TIMER_EXPIRED(g_SpadWork->timer)) {
        g_SpadWork->color_g = 0;
        g_SpadWork->timer   = 4;
        g_SpadWork->step += 1;
    }
}

/* 12 differing; first at +0x34: candidate lb a0,94(v0) against retail lb v0,94(v0) — the fade value
 * must stay in v0 and copy to the call argument in the arms (an s32 unused[2] filler sizes the frame
 * right); next lever: permuter on the fade value register. */
INCLUDE_ASM(func_801D0E5C);

MATCH void func_801D0F44(void) {
    g_SpadWork->color_g -= 0x40;
    func_801D1220(g_SpadWork->color_g);
    func_801D1C1C(&g_SpadWork->pos_x, &g_SpadWork->counter_0C, g_SpadWork->color_r);
    func_801D1A20(&g_SpadWork->pos_x, (s16)g_SpadWork->origin_x, 2);
    func_801D1914(0x40);

    if (TIMER_EXPIRED(g_SpadWork->timer)) {
        g_SpadWork->timer = 0x3C;
        g_SpadWork->step += 1;
    }
}

MATCH void func_801D101C(void) {
    func_801D1C1C(&g_SpadWork->pos_x, &g_SpadWork->counter_0C, g_SpadWork->color_r);
    func_801D1A20(&g_SpadWork->pos_x, (s16)g_SpadWork->origin_x, 2);
    func_801D1914(0x40);

    if (TIMER_EXPIRED(g_SpadWork->timer)) {
        g_SpadWork->timer = 0x3C;
        g_SpadWork->step += 1;
        SND_PlayCue(EMI_CUE_ID(2, 14));
    }
}

MATCH void func_801D10C4(void) {
    if ((s16)g_SpadWork->origin_x > 0) {
        g_SpadWork->origin_x -= 0x10;
    }
    if ((s8)g_SpadWork->color_r > 0) {
        g_SpadWork->color_r -= 8;
    }
    func_801D1C1C(&g_SpadWork->pos_x, &g_SpadWork->counter_0C, g_SpadWork->color_r);
    func_801D1A20(&g_SpadWork->pos_x, (s16)g_SpadWork->origin_x, 2);
    func_801D1914(0x40);

    if (TIMER_EXPIRED(g_SpadWork->timer)) {
        g_SpadWork->timer    = 0x10;
        g_SpadWork->origin_x = 0x40;
        g_SpadWork->step += 1;
    }
}

MATCH void func_801D11B4(void) {
    func_801D1914(g_SpadWork->origin_x -= 4);

    if (TIMER_EXPIRED(g_SpadWork->timer)) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801D1220);

INCLUDE_ASM(func_801D1370);

INCLUDE_ASM(func_801D1540);

INCLUDE_ASM(func_801D1690);

INCLUDE_ASM(func_801D1914);

INCLUDE_ASM(func_801D1A20);

INCLUDE_ASM(func_801D1C1C);
