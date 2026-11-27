#include "sce10eff_00.h"

/* The state table Scene_UpdateEffectState dispatches through; the word after its last
 * entry holds the work pointer Scene_EffectBegin publishes. */
Callback D_801D2708[15] = {
    func_801D0FAC, func_801D1218, func_801D1D58, func_801D1034, func_801D10C8, func_801D1138, func_801D11A0, func_801D12A8,
    func_801D13C0, func_801D1430, func_801D1544, func_801D1DE0, func_801D1EFC, func_801D1F50, func_801D2064,
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

    SELF(SceneBandEffect)->ticker++;

    work                        = SELF(SceneBandEffect);
    counter                     = work->orbit_counter + 1;
    work->orbit_counter         = counter;
    angle                       = SCE10EFF_ORBIT_ANGLE(counter);
    angle_cell                  = &g_ScratchPad.cells.words[1];
    *angle_cell                 = angle;
    g_ScratchPad.cells.words[0] = 0x18;

    velocity     = rcos(angle) * g_ScratchPad.cells.words[0];
    work         = SELF(SceneBandEffect);
    work->proj.x = D_801D2744->proj.x + velocity;

    velocity        = rsin(*angle_cell) * g_ScratchPad.cells.words[0];
    scratch         = SELF(SceneBandEffect);
    scratch->proj.y = D_801D2744->proj.y + velocity;
    scratch->band -= 2;

    if (SELF(SceneBandEffect)->band == 0) {
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

    d                         = &g_ScratchPad.cells.words[0];
    vec                       = (s16*)g_ScratchPadVectors;
    d[0]                      = 0x40;
    D_1F800004                = ((SELF(SceneBandEffect)->ticker + 2) & 0xF) << 8;
    D_1F80000C                = SELF(SceneBandEffect)->band;
    i                         = 1;
    D_1F800008                = RANDOM_MASK(0x3F);
    vec[0]                    = 0;
    g_ScratchPadVectors[0].vy = FIXED_MUL(rsin(D_1F800004), d[0]);
    g_ScratchPadVectors[0].vz = 0;
    if (i < D_1F80000C) {
        cell = d + 1;
        do {
            GFX_AddDitheredDrawMode(2, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256));
            primitive = (LINE_G2*)g_GfxPrimCursor;
            SetLineG2(primitive);
            PSX_SET_SEMI_TRANSPARENT(primitive);
            RotTransPers((SVECTOR*)g_ScratchPadVectors, (long*)&primitive->x0, &p, &flag);
            if RANDOM_MASK (1) {
                g_ScratchPad.cells.words[0] = RANDOM_MASK(0x3F) + 0x80;
            } else {
                g_ScratchPad.cells.words[0] = 0x80 - RANDOM_MASK(0x3F);
            }
            page    = ((SELF(SceneBandEffect)->ticker + i + 2) & 0xF) << 8;
            vec[0]  = 0;
            cell[0] = page;
            vec[1]  = FIXED_MUL(rsin(page), cell[-1]);
            vec[2]  = -(i << 6);
            RotTransPers((SVECTOR*)vec, (long*)&primitive->x1, &p, &flag);
            setRGB0(primitive, cell[1], cell[1], 32);
            cell[1] = (rand() + 0x40) & 0x3F;
            setRGB1(primitive, cell[1], cell[1], 0x20);
            GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(LINE_G2));
            i++;
        } while (i < cell[2]);
    }
}

MATCH void func_801D240C(void) {
    POLY_G3* primitive;
    s32*     angle_ptr;
    s32      angle;
    s32      i;

    g_ScratchPad.cells.words[0] = RANDOM_MASK(7) + SELF(SceneBandEffect)->band * 3;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    i         = 0;
    angle_ptr = &g_ScratchPad.cells.words[0];
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(DR_MODE));

    do {
        primitive = GFX_BeginPolyG3(1);

        setXY0(primitive, SELF(SceneBandEffect)->origin.x, SELF(SceneBandEffect)->origin.y);
        angle         = i << 9;
        primitive->x1 = SELF(SceneBandEffect)->origin.x + FIXED_MUL(rsin(angle), *angle_ptr);
        primitive->y1 = SELF(SceneBandEffect)->origin.y + FIXED_MUL(rcos(angle), *angle_ptr);
        i++;
        angle         = i << 9;
        primitive->x2 = SELF(SceneBandEffect)->origin.x + FIXED_MUL(rsin(angle), *angle_ptr);
        primitive->y2 = SELF(SceneBandEffect)->origin.y + FIXED_MUL(rcos(angle), *angle_ptr);
        setRGB0(primitive, SELF(SceneBandEffect)->band * 8, SELF(SceneBandEffect)->band * 8, SELF(SceneBandEffect)->band * 6);
        setRGB1(primitive, 1, 1, 1);
        setRGB2(primitive, 1, 1, 1);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G3));
    } while (i < 8);
}

MATCH void func_801D2658(void) {
    s16     vec[3];
    TILE_1* primitive;

    vec[0]    = (SELF(SceneBandEffect)->proj.x >> 9) - 0x4000;
    primitive = (TILE_1*)g_GfxPrimCursor;
    vec[1]    = (SELF(SceneBandEffect)->proj.y >> 9) - 0x4000;
    vec[2]    = -(SELF(SceneBandEffect)->proj_z / 2);
    SetTile1(primitive);
    RotTransPers((SVECTOR*)vec, (long*)&primitive->x0, (long*)vec, (long*)&vec[2]);
    SELF(SceneBandEffect)->origin.x = primitive->x0;
    SELF(SceneBandEffect)->origin.y = primitive->y0;
}
