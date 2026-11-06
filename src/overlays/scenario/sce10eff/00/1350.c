#include "sce10eff_00.h"

/* The state table Scene_EffectRunState dispatches through; the word after its last
 * entry holds the work pointer Scene_EffectBegin publishes. */
Callback D_801D2708[15] = {
    func_801D0FAC, func_801D1218, func_801D1D58, func_801D1034, func_801D10C8,
    func_801D1138, func_801D11A0, func_801D12A8, func_801D13C0, func_801D1430,
    func_801D1544, func_801D1DE0, func_801D1EFC, func_801D1F50, func_801D2064,
};

SceneBandEffect* D_801D2744 = 0;

MATCH void func_801D1F50(void) {
    SceneBandEffect* work;
    s32              counter;
    s32              angle;
    s32*             angle_cell;
    s32              velocity;

    SCENE_PROJECT_ORBIT_STEP(0x10);
}

MATCH void func_801D2064(void) {
    SceneBandEffect* work;
    SceneBandEffect* scratch;
    s32              counter;
    s32              angle;
    s32*             angle_cell;
    s32              velocity;

    g_Task->ticker++;

    work                          = g_Task;
    counter                       = work->orbit_counter + 1;
    VOL(s32, work->orbit_counter) = counter;
    angle                         = SCE10EFF_ORBIT_ANGLE(counter);
    angle_cell                    = &D_1F800004;
    *angle_cell                   = angle;
    D_1F800000                    = 0x18;

    velocity     = rcos(angle) * D_1F800000;
    work         = g_Task;
    work->proj_x = D_801D2744->proj_x + velocity;

    velocity        = rsin(*angle_cell) * D_1F800000;
    scratch         = g_Task;
    scratch->proj_y = D_801D2744->proj_y + velocity;
    scratch->band -= 2;

    if (g_Task->band == 0) {
        D_801D2744->ticker++;
        Actor_Clear();
    }
}

MATCH void func_801D218C(void) {
    LINE_G2* primitive;
    s32*     d;
    s32*     cell;
    s16*     vec;
    long     p;
    long     flag;
    s32      page;
    s32      i;

    d          = &D_1F800000;
    vec        = (s16*)D_1F800014;
    d[0]       = 0x40;
    D_1F800004 = ((g_Task->ticker + 2) & 0xF) << 8;
    D_1F80000C = g_Task->band;
    i          = 1;
    D_1F800008 = RANDOM_MASK(0x3F);
    vec[0]     = 0;
    D_1F800016 = FIXED_MUL(rsin(D_1F800004), d[0]);
    D_1F800018 = 0;
    if (i < D_1F80000C) {
        cell = d + 1;
        do {
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(1, 1, 320, 256), 0);
            GFX_AddPrim(2, 0x0C);
            primitive = (LINE_G2*)g_GfxPrimCursor;
            SetLineG2(primitive);
            PSX_SET_SEMI_TRANSPARENT(primitive);
            RotTransPers((SVECTOR*)D_1F800014, (long*)&primitive->x0, &p, &flag);
            if (RANDOM_MASK(1)) {
                D_1F800000 = (RANDOM_MASK(0x3F)) + 0x80;
            } else {
                D_1F800000 = 0x80 - (RANDOM_MASK(0x3F));
            }
            page    = ((g_Task->ticker + i + 2) & 0xF) << 8;
            vec[0]  = 0;
            cell[0] = page;
            vec[1]  = FIXED_MUL(rsin(page), cell[-1]);
            vec[2]  = -(i << 6);
            RotTransPers((SVECTOR*)vec, (long*)&primitive->x1, &p, &flag);
            setRGB0(primitive, cell[1], cell[1], 32);
            cell[1]       = (rand() + 0x40) & 0x3F;
            primitive->r1 = cell[1];
            primitive->g1 = cell[1];
            primitive->b1 = 0x20;
            GFX_AddPrim(2, 0x14);
            i++;
        } while (i < cell[2]);
    }
}

MATCH void func_801D240C(void) {
    POLY_G3* primitive;
    s32*     angle_ptr;
    s32      angle;
    s32      i;

    D_1F800000 = (RANDOM_MASK(7)) + g_Task->band * 3;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetGraphType() != 1 ? (GetGraphType() == 2 ? 0xA5 : 0x35) : 0xA5, 0);
    i         = 0;
    angle_ptr = &D_1F800000;
    GFX_AddPrim(2, 0x0C);

    do {
        primitive = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(primitive);
        PSX_SET_SEMI_TRANSPARENT(primitive);

        primitive->x0 = g_Task->origin_x;
        primitive->y0 = g_Task->origin_y;
        angle         = i << 9;
        primitive->x1 = g_Task->origin_x + FIXED_MUL(rsin(angle), *angle_ptr);
        primitive->y1 = g_Task->origin_y + FIXED_MUL(rcos(angle), *angle_ptr);
        i++;
        angle         = i << 9;
        primitive->x2 = g_Task->origin_x + FIXED_MUL(rsin(angle), *angle_ptr);
        primitive->y2 = g_Task->origin_y + FIXED_MUL(rcos(angle), *angle_ptr);
        setRGB0(primitive, g_Task->band * 8, g_Task->band * 8, g_Task->band * 6);
        primitive->r1 = 1;
        primitive->g1 = 1;
        primitive->b1 = 1;
        primitive->r2 = 1;
        primitive->g2 = 1;
        primitive->b2 = 1;
        GFX_AddPrim(2, 0x1C);
    } while (i < 8);
}

MATCH void func_801D2658(void) {
    s16     vec[3];
    TILE_1* primitive;

    vec[0]    = (g_Task->proj_x >> 9) - 0x4000;
    primitive = (TILE_1*)g_GfxPrimCursor;
    vec[1]    = (g_Task->proj_y >> 9) - 0x4000;
    vec[2]    = -(g_Task->proj_z / 2);
    SetTile1(primitive);
    RotTransPers((SVECTOR*)vec, (long*)&primitive->x0, (long*)vec, (long*)&vec[2]);
    g_Task->origin_x = primitive->x0;
    g_Task->origin_y = primitive->y0;
}
