#include "sce10eff_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The overlay's three entry points. @source: read:Scene_UpdateEffect@0x801D0C10 */
#define SCENE10_EFFECT_STEP_COUNT 3

typedef struct SceneEffect10Steps {
    Callback steps[SCENE10_EFFECT_STEP_COUNT];
} SceneEffect10Steps;

static SceneEffect10Steps D_801D0C04 = {
    {Scene_EffectBegin, Scene_EffectEnd, Scene_UpdateEffectState},
};

/* func_801D0C10 */
MATCH void Scene_UpdateEffect(void) { /* func_801D0C10 */
    SceneEffect10Steps handlers;

    handlers = D_801D0C04;
    handlers.steps[SELF_BYTES[1]]();
}

/* func_801D0C70 */
MATCH void Scene_EffectBegin(void) { /* func_801D0C70 */
    u8 i;
    u8 slot;

    D_801D2744 = SELF(SceneBandEffect);

    slot                               = Actor_FindFreeSpawned();
    g_SpawnedActors[slot].header.flags = 1;
    g_SpawnedActors[slot].type         = 0x69;
    g_SpawnedActors[slot].header.mode  = 2;
    g_SpawnedActors[slot].header.step  = 0;
    g_SpawnedActors[slot].unk_03       = 0;

    i = 0;
    do {
        slot                         = Actor_FindFreeSpawned();
        g_SpawnedActors[slot].unk_04 = i;
        i++;
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[slot].type         = 0x69;
        g_SpawnedActors[slot].header.mode  = 2;
        g_SpawnedActors[slot].header.step  = 1;
        g_SpawnedActors[slot].unk_03       = 0;
    } while (i < 4);

    i = 0;
    do {
        slot                         = Actor_FindFreeSpawned();
        g_SpawnedActors[slot].unk_04 = i;
        i++;
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[slot].type         = 0x69;
        g_SpawnedActors[slot].header.mode  = 2;
        g_SpawnedActors[slot].header.step  = 2;
        g_SpawnedActors[slot].unk_03       = 0;
    } while (i < 4);

    SELF(SceneBandEffect)->ticker = 0;
    SELF(SceneBandEffect)->unk_01++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
}

/* func_801D0E64 */
MATCH void Scene_EffectEnd(void) { /* func_801D0E64 */
    if (SELF(SceneBandEffect)->ticker == 9) {
        Actor_Clear();
    }
}

/* func_801D0E9C */
MATCH void Scene_UpdateEffectState(void) { /* func_801D0E9C */
    D_801D2708[SELF(SceneBandEffect)->state]();
}

/* func_801D0EE0 */
MATCH void Scene_EffectSetMatrix(void) { /* func_801D0EE0 */
    SceneBandEffect* scratch;
    SVECTOR          vertex;
    SVECTOR          rotation;
    MATRIX           matrix;
    long             flag;

    PushMatrix();

    scratch = SELF(SceneBandEffect);

    setVector(&rotation, 0, 0, ONE / 4);
    if ((scratch->flags & 0x1u) != 0u) {
        rotation.vz = 0;
    }

    setVector(&vertex, (scratch->proj.x >> 9) - 0x4000, (scratch->proj.y >> 9) - 0x4000, (-scratch->proj_z / 2));

    RotTransMatrix(&vertex, matrix, &flag);
    Camera_SetModelMatrix(&rotation, &matrix);
}

MATCH void func_801D0FAC(void) {
    D_801D2714[SELF(SceneBandEffect)->step_index]();
    func_801D2658();
    if (SELF(SceneBandEffect)->step_index != 0) {
        Scene_EffectSetMatrix();
        Scene_DrawBands(0x60, 32, 7);
        PopMatrix();
    }
}

MATCH void func_801D1034(void) {
    SceneBandEffect* source;
    SceneBandEffect* work;
    SceneBandEffect* scratch;
    s32              coord_y;
    s16              distance;

    SELF(SceneBandEffect)->ticker = RANDOM_MASK(0xF);
    SELF(SceneBandEffect)->timer  = 0;
    SELF(SceneBandEffect)->band   = 0;

    source       = D_801D2744;
    work         = SELF(SceneBandEffect);
    work->proj.x = source->proj.x;
    coord_y      = source->proj.y;
    work->proj.y = coord_y;
    distance     = Area_HeightSample(work->proj.x, coord_y);

    scratch = SELF(SceneBandEffect);
    scratch->step_index++;
    scratch->proj_z = distance;
}

MATCH void func_801D10C8(void) {
    Scene_AdvanceBand(18);
}

MATCH void func_801D1138(void) {
    SceneBandEffect* work;

    /* A store through the pointer may alias the cell, so each step reloads
     * it. */
    work = SELF(SceneBandEffect);
    work->ticker++;
    work = SELF(SceneBandEffect);
    work->timer--;
    if (work->timer == 0) {
        work = SELF(SceneBandEffect);
        work->step_index++;
    }
}

MATCH void func_801D11A0(void) {
    SceneBandEffect* work;
    u8               count;

    /* A store through the pointer may alias the cell, so each step reloads
     * it. */
    work = SELF(SceneBandEffect);
    work->ticker++;
    work       = SELF(SceneBandEffect);
    count      = work->band - 1;
    work->band = count;
    if (count == 0) {
        D_801D2744->ticker++;
        Actor_Clear();
    }
}

MATCH void func_801D1218(void) {
    SceneBandEffect* work;

    work = SELF(SceneBandEffect);
    D_801D2724[work->step_index]();
    func_801D2658();
    if (SELF(SceneBandEffect)->step_index != 0) {
        Scene_EffectSetMatrix();
        Scene_DrawBands(0x20, 80, 0x1F);
        func_801D240C();
        PopMatrix();
    }
}

MATCH void func_801D12A8(void) {
    SceneBandEffect* work;
    SceneBandEffect* scratch;
    SceneBandEffect* source;
    s32              counter;
    s32              angle;
    s32*             angle_cell;
    s32              velocity;

    SELF(SceneBandEffect)->ticker = RANDOM_MASK(0xF);
    SELF(SceneBandEffect)->timer  = 0;
    SELF(SceneBandEffect)->band   = 0;

    work                        = SELF(SceneBandEffect);
    counter                     = work->orbit_seed << 5;
    work->orbit_counter         = counter;
    angle                       = SCE10EFF_ORBIT_ANGLE(counter);
    angle_cell                  = &g_ScratchPad.cells.words[1];
    *angle_cell                 = angle;
    g_ScratchPad.cells.words[0] = 0x20;

    velocity     = rcos(angle) * g_ScratchPad.cells.words[0];
    work         = SELF(SceneBandEffect);
    work->proj.x = D_801D2744->proj.x + velocity;

    velocity        = rsin(*angle_cell) * g_ScratchPad.cells.words[0];
    source          = D_801D2744;
    scratch         = SELF(SceneBandEffect);
    scratch->proj.y = source->proj.y + velocity;
    scratch->proj_z = source->proj_z;
    scratch->step_index++;
}

MATCH void func_801D13C0(void) {
    Scene_AdvanceBand(16);
}

MATCH void func_801D1430(void) {
    SceneBandEffect* work;
    s32              counter;
    s32              angle;
    s32*             angle_cell;
    s32              velocity;

    SCENE_PROJECT_ORBIT_STEP(0x20);
}

MATCH void func_801D1544(void) {
    SceneBandEffect* work;
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
    g_ScratchPad.cells.words[0] = 0x20;

    velocity     = rcos(angle) * g_ScratchPad.cells.words[0];
    work         = SELF(SceneBandEffect);
    work->proj.x = D_801D2744->proj.x + velocity;

    velocity                      = rsin(*angle_cell) * g_ScratchPad.cells.words[0];
    SELF(SceneBandEffect)->proj.y = D_801D2744->proj.y + velocity;

    if (TIMER_EXPIRED(SELF(SceneBandEffect)->band)) {
        D_801D2744->ticker++;
        Actor_Clear();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void Scene_DrawBands(s16 band_height, u16 radius, u16 jitter_mask) {
    long     depth;
    long     flag;
    POLY_G4* primitive;
    SVECTOR* quad;
    SVECTOR* prev;
    s32*     radius_cell;
    s32*     cell;
    s32*     ramp;
    s32      tpage;
    s32      shade;
    s32      radius_base;
    s32      i;

    radius_base                 = (s16)radius;
    radius_cell                 = &g_ScratchPad.cells.words[0];
    *radius_cell                = 0x10;
    g_ScratchPad.cells.words[1] = (SELF(SceneBandEffect)->ticker & 0xF) << 8;
    g_ScratchPad.cells.words[2] = SELF(SceneBandEffect)->band * 7;
    shade                       = SELF(SceneBandEffect)->band * 13;
    g_ScratchPadVectors[0].vy   = FIXED_MUL(rsin(g_ScratchPad.cells.words[1]), *radius_cell);
    g_ScratchPadVectors[0].vz   = 0;
    tpage                       = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    prev                        = &g_ScratchPadVectors[2];
    quad                        = prev - 2;
    cell                        = &g_ScratchPad.cells.words[1];
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(DR_MODE));
    ramp = cell + 1;
    for (i = 1; i < 18; i++) {
        cell[0] = ((SELF(SceneBandEffect)->ticker + i) & 0xF) << 8;
        if RANDOM_MASK (1) {
            cell[-1] = radius_base + RANDOM_MASK((s16)jitter_mask);
        } else {
            cell[-1] = radius_base - RANDOM_MASK((s16)jitter_mask);
        }
        prev[0].vx = 0;
        prev[1].vx = 0;
        quad[0].vx = 0;
        prev[0].vy = quad[0].vy;
        prev[1].vy = quad[0].vy - band_height;
        prev[0].vz = quad[0].vz;
        prev[1].vz = quad[0].vz;
        quad[0].vy = FIXED_MUL(rsin(cell[0]), cell[-1]);
        primitive  = (POLY_G4*)g_GfxPrimCursor;
        quad[1].vx = 0;
        quad[0].vz = -(i * 64);
        quad[1].vz = -(i * 64);
        quad[1].vy = quad[0].vy - band_height;
        SetPolyG4(primitive);
        SetSemiTrans(primitive, 1);
        setRGB0(primitive, cell[1], cell[1], cell[1]);
        setRGB1(primitive, shade, cell[1], 1);
        if (i == 1) {
            setRGB2(primitive, i, i, i);
            setRGB3(primitive, i, i, i);
        } else {
            setRGB2(primitive, cell[1], cell[1], cell[1]);
            setRGB3(primitive, shade, cell[1], 1);
        }
        RotTransPers4(quad, quad + 1, quad + 2, quad + 3, (long*)&primitive->x0, (long*)&primitive->x1, (long*)&primitive->x2, (long*)&primitive->x3, &depth, &flag);
        if (primitive->y2 > 0) {
            GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));
            primitive = (POLY_G4*)g_GfxPrimCursor;
            SPAD(0u)->vectors[0].vy -= band_height;
            SPAD(0u)->vectors[1].vy -= band_height;
            SPAD(0u)->vectors[2].vy -= band_height;
            SPAD(0u)->vectors[3].vy -= band_height;
            SetPolyG4(primitive);
            SetSemiTrans(primitive, 1);
            setRGB0(primitive, shade, *ramp, 1);
            setRGB1(primitive, 1, 1, 1);
            if (i == 1) {
                setRGB2(primitive, 1, 1, 1);
                setRGB3(primitive, 1, 1, 1);
            } else {
                setRGB2(primitive, shade, *ramp, 1);
                setRGB3(primitive, 1, 1, 1);
            }
            RotTransPers4(quad, quad + 1, quad + 2, quad + 3, (long*)&primitive->x0, (long*)&primitive->x1, (long*)&primitive->x2, (long*)&primitive->x3, &depth, &flag);
            GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));
            primitive = (POLY_G4*)g_GfxPrimCursor;
            SPAD(0u)->vectors[0].vy += band_height * 2;
            SPAD(0u)->vectors[1].vy += band_height * 2;
            SPAD(0u)->vectors[2].vy += band_height * 2;
            SPAD(0u)->vectors[3].vy += band_height * 2;
            SetPolyG4(primitive);
            SetSemiTrans(primitive, 1);
            setRGB0(primitive, shade, *ramp, 1);
            setRGB1(primitive, *ramp, *ramp, *ramp);
            if (i == 1) {
                setRGB2(primitive, 1, 1, 1);
                setRGB3(primitive, 1, 1, 1);
            } else {
                setRGB2(primitive, shade, *ramp, 1);
                setRGB3(primitive, *ramp, *ramp, *ramp);
            }
            RotTransPers4(quad, quad + 1, quad + 2, quad + 3, (long*)&primitive->x0, (long*)&primitive->x1, (long*)&primitive->x2, (long*)&primitive->x3, &depth, &flag);
            GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));
            primitive = (POLY_G4*)g_GfxPrimCursor;
            SPAD(0u)->vectors[0].vy += band_height;
            SPAD(0u)->vectors[1].vy += band_height;
            SPAD(0u)->vectors[2].vy += band_height;
            SPAD(0u)->vectors[3].vy += band_height;
            SetPolyG4(primitive);
            SetSemiTrans(primitive, 1);
            setRGB0(primitive, 1, 1, 1);
            setRGB1(primitive, shade, *ramp, 1);
            if (i == 1) {
                setRGB2(primitive, 1, 1, 1);
                setRGB3(primitive, 1, 1, 1);
            } else {
                setRGB2(primitive, 1, 1, 1);
                setRGB3(primitive, shade, *ramp, 1);
            }
            RotTransPers4(quad, quad + 1, quad + 2, quad + 3, (long*)&primitive->x0, (long*)&primitive->x1, (long*)&primitive->x2, (long*)&primitive->x3, &depth, &flag);
            GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));
            SPAD(0u)->vectors[0].vy -= band_height * 2;
        }
    }
}
#else
INCLUDE_ASM(Scene_DrawBands);
#endif

MATCH void func_801D1D58(void) {
    D_801D2734[SELF(SceneBandEffect)->step_index]();
    func_801D2658();
    if (SELF(SceneBandEffect)->step_index != 0) {
        Scene_EffectSetMatrix();
        func_801D218C();
        func_801D240C();
        PopMatrix();
    }
}

MATCH void func_801D1DE0(void) {
    SceneBandEffect* work;
    s32              counter;
    s32              angle;
    s32*             angle_cell;
    s32              velocity;

    SELF(SceneBandEffect)->ticker = RANDOM_MASK(0xF);
    SELF(SceneBandEffect)->timer  = 0;
    SELF(SceneBandEffect)->band   = 0;

    work                        = SELF(SceneBandEffect);
    counter                     = (work->orbit_seed << 5) + 0x10;
    angle                       = SCE10EFF_ORBIT_ANGLE(counter);
    work->orbit_counter         = counter;
    angle_cell                  = &g_ScratchPad.cells.words[1];
    *angle_cell                 = angle;
    g_ScratchPad.cells.words[0] = 0x18;

    velocity                      = rcos(angle) * g_ScratchPad.cells.words[0];
    SELF(SceneBandEffect)->proj.x = D_801D2744->proj.x + velocity;

    velocity                      = rsin(*angle_cell) * g_ScratchPad.cells.words[0];
    SELF(SceneBandEffect)->proj.y = D_801D2744->proj.y + velocity;

    SELF(SceneBandEffect)->proj_z = D_801D2744->proj_z;
    SELF(SceneBandEffect)->step_index++;
}
