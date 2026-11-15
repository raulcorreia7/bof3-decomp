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
    GFX_DrawColorFan(&g_Task->pos.x, g_Task->origin_x, 2);

    if (TIMER_EXPIRED(g_Task->timer)) {
        g_Task->timer = 60;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 13));
    }
}

MATCH void func_801D0DB0(void) {
    func_801D1C1C(&g_Task->pos.x, &g_Task->counter_0C, g_Task->color_r);
    GFX_DrawColorFan(&g_Task->pos.x, g_Task->origin_x, 2);

    if (TIMER_EXPIRED(g_Task->timer)) {
        g_Task->color_g = 0;
        g_Task->timer   = 4;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D0E5C(void) {
    g_Task->color_g += 0x40;
    if ((s8)g_Task->color_g != 0) {
        func_801D1220((u8)g_Task->color_g);
    } else {
        func_801D1220(0xFF);
    }
    func_801D1C1C(&g_Task->pos.x, &g_Task->counter_0C, g_Task->color_r);
    GFX_DrawColorFan(&g_Task->pos.x, g_Task->origin_x, 2);
    if (TIMER_EXPIRED(g_Task->timer)) {
        g_Task->timer = 4;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D0F44(void) {
    g_Task->color_g -= 0x40;
    func_801D1220(g_Task->color_g);
    func_801D1C1C(&g_Task->pos.x, &g_Task->counter_0C, g_Task->color_r);
    GFX_DrawColorFan(&g_Task->pos.x, g_Task->origin_x, 2);
    func_801D1914(64);

    if (TIMER_EXPIRED(g_Task->timer)) {
        g_Task->timer = 60;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D101C(void) {
    func_801D1C1C(&g_Task->pos.x, &g_Task->counter_0C, g_Task->color_r);
    GFX_DrawColorFan(&g_Task->pos.x, g_Task->origin_x, 2);
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
    GFX_DrawColorFan(&g_Task->pos.x, g_Task->origin_x, 2);
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

/* Draw a red line between two points with a fan at each end. */
MATCH void func_801D1370(s32* first, s32* second, s16 width) {
    LINE_F2* line;
    u16      size[2];
    u16      scale[2];
    MATRIX   camera;
    s32      angle;
    u16      angle1;
    u16      angle2;
    s16      radius1;
    s16      radius2;

    GFX_AddDitheredDrawMode(3, GetTPage(0, 1, 960, 0));
    Area_SetCameraMatrix(&camera);
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 0);
    Area_ProjectPoint(first, (DVECTOR*)&line->x0);
    Area_ProjectPoint(second, (DVECTOR*)&line->x1);
    setRGB0(line, 64, 0, 0);
    GFX_AddPrim(3, sizeof(LINE_F2));
    angle   = ratan2(line->y1 - line->y0, line->x1 - line->x0);
    size[0] = size[1] = width;
    Game_ProjectWorldPoint(first, size, scale);
    angle1  = angle + ANGLE_90;
    radius1 = scale[0] + (g_FrameCount & 1);
    func_801D1540(line->x0, line->y0, radius1, angle1);
    Game_ProjectWorldPoint(second, size, scale);
    angle2  = angle + ANGLE_270;
    radius2 = scale[0] + (g_FrameCount & 1);
    func_801D1540(line->x1, line->y1, radius2, angle2);
    func_801D1690(line->x0, line->y0, radius1, angle1, line->x1, line->y1, radius2, angle2);
}

MATCH void func_801D1540(s32 x, s32 y, s16 radius, u16 angle) {
    POLY_G3* prim;
    u8       i;

    i = 0;
    do {
        prim = GFX_BeginPolyG3(1);
        setXY2(prim, x, y, x + FIXED_MUL(radius, rcos(angle)), y + FIXED_MUL(radius, rsin(angle)));
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

MATCH void func_801D1690(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2) {
    POLY_G4* poly;
    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    SetSemiTrans(poly, 1);
    setXY4(poly, x1, y1, x2, y2, x1 + FIXED_MUL(radius1, rcos(angle1)), y1 + FIXED_MUL(radius1, rsin(angle1)), x2 + FIXED_MUL(radius2, rcos(angle2 + ANGLE_180)),
           y2 + FIXED_MUL(radius2, rsin(angle2 + ANGLE_180)));
    setRGB0(poly, 64, 0, 0);
    setRGB1(poly, 64, 0, 0);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    GFX_AddPrim(3, sizeof(POLY_G4));

    poly++;
    memcpy(poly, poly - 1, sizeof(POLY_G4));
    poly->x2 = x1 + FIXED_MUL(radius1, rcos(angle1 + ANGLE_180));
    poly->y2 = y1 + FIXED_MUL(radius1, rsin(angle1 + ANGLE_180));
    poly->x3 = x2 + FIXED_MUL(radius2, rcos(angle2));
    poly->y3 = y2 + FIXED_MUL(radius2, rsin(angle2));
    GFX_AddPrim(3, sizeof(POLY_G4));
}

MATCH void func_801D1914(s16 amount) {
    VECTOR start;
    VECTOR end;

    setVector(&start, TO_COORD(48) + COORD_HALF, TO_COORD(113) + COORD_HALF, TO_COORD(-768));
    setVector(&end, TO_COORD(48) + COORD_HALF, TO_COORD(113) + COORD_HALF, TO_COORD(-512));
    func_801D1370(&start, &end, amount);

    setVector(&start, TO_COORD(48), TO_COORD(113) + COORD_HALF, TO_COORD(-384));
    func_801D1370(&start, &end, amount);

    setVector(&end, TO_COORD(48), TO_COORD(113) + COORD_HALF, TO_COORD(-256));
    func_801D1370(&start, &end, amount);

    setVector(&start, TO_COORD(48) + COORD_HALF, TO_COORD(113) + COORD_HALF, TO_COORD(-128));
    func_801D1370(&start, &end, amount);

    setVector(&end, TO_COORD(48) + COORD_HALF, TO_COORD(113) + COORD_HALF, 0);
    func_801D1370(&start, &end, amount);
}

/* func_801D1A20 */
#include "shared/GFX_DrawColorFan.h"

INCLUDE_ASM(func_801D1C1C);
