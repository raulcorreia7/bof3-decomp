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
    handlers.steps[TASK_BYTES[1]]();
}

/* func_801D0C70 */
MATCH void Scene_EffectBegin(void) { /* func_801D0C70 */
    u8 i;
    u8 slot;

    D_801D2744 = g_Task;

    slot                            = Actor_FindFreeSlot();
    g_ActorSlots[slot].header.flags = 1;
    g_ActorSlots[slot].type         = 0x69;
    g_ActorSlots[slot].header.mode  = 2;
    g_ActorSlots[slot].header.step  = 0;
    g_ActorSlots[slot].unk_03       = 0;

    i = 0;
    do {
        slot                      = Actor_FindFreeSlot();
        g_ActorSlots[slot].unk_04 = i;
        i++;
        g_ActorSlots[slot].header.flags = 1;
        g_ActorSlots[slot].type         = 0x69;
        g_ActorSlots[slot].header.mode  = 2;
        g_ActorSlots[slot].header.step  = 1;
        g_ActorSlots[slot].unk_03       = 0;
    } while (i < 4);

    i = 0;
    do {
        slot                      = Actor_FindFreeSlot();
        g_ActorSlots[slot].unk_04 = i;
        i++;
        g_ActorSlots[slot].header.flags = 1;
        g_ActorSlots[slot].type         = 0x69;
        g_ActorSlots[slot].header.mode  = 2;
        g_ActorSlots[slot].header.step  = 2;
        g_ActorSlots[slot].unk_03       = 0;
    } while (i < 4);

    g_Task->ticker = 0;
    g_Task->unk_01++;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
}

/* func_801D0E64 */
MATCH void Scene_EffectEnd(void) { /* func_801D0E64 */
    if (g_Task->ticker == 9) {
        Actor_Clear();
    }
}

/* func_801D0E9C */
MATCH void Scene_UpdateEffectState(void) { /* func_801D0E9C */
    D_801D2708[g_Task->state]();
}

/* func_801D0EE0 */
MATCH void Scene_EffectSetMatrix(void) { /* func_801D0EE0 */
    SceneBandEffect* scratch;
    SVECTOR          vertex;
    SVECTOR          rotation;
    MATRIX           matrix;
    long             flag;

    PushMatrix();

    scratch = g_Task;

    rotation.vx = 0;
    rotation.vy = 0;
    rotation.vz = ONE / 4;
    if ((scratch->flags & 0x1u) != 0u) {
        rotation.vz = 0;
    }

    vertex.vx = (scratch->proj.x >> 9) - 0x4000;
    vertex.vy = (scratch->proj.y >> 9) - 0x4000;
    vertex.vz = (-scratch->proj_z / 2);

    RotTransMatrix(&vertex, matrix, &flag);
    Camera_SetModelMatrix(&rotation, &matrix);
}

MATCH void func_801D0FAC(void) {
    D_801D2714[g_Task->step_index]();
    func_801D2658();
    if (g_Task->step_index != 0) {
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

    g_Task->ticker = RANDOM_MASK(0xF);
    g_Task->timer  = 0;
    g_Task->band   = 0;

    source       = D_801D2744;
    work         = g_Task;
    work->proj.x = source->proj.x;
    coord_y      = source->proj.y;
    work->proj.y = coord_y;
    distance     = Area_SampleHeight(work->proj.x, coord_y);

    scratch = g_Task;
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
    work = g_Task;
    work->ticker++;
    work = g_Task;
    work->timer--;
    if (work->timer == 0) {
        work = g_Task;
        work->step_index++;
    }
}

MATCH void func_801D11A0(void) {
    SceneBandEffect* work;
    u8               count;

    /* A store through the pointer may alias the cell, so each step reloads
     * it. */
    work = g_Task;
    work->ticker++;
    work       = g_Task;
    count      = work->band - 1;
    work->band = count;
    if (count == 0) {
        D_801D2744->ticker++;
        Actor_Clear();
    }
}

MATCH void func_801D1218(void) {
    SceneBandEffect* work;

    work = g_Task;
    D_801D2724[work->step_index]();
    func_801D2658();
    if (g_Task->step_index != 0) {
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

    g_Task->ticker = RANDOM_MASK(0xF);
    g_Task->timer  = 0;
    g_Task->band   = 0;

    work                          = g_Task;
    counter                       = work->orbit_seed << 5;
    VOL(s32, work->orbit_counter) = counter;
    angle                         = SCE10EFF_ORBIT_ANGLE(counter);
    angle_cell                    = &D_1F800004;
    *angle_cell                   = angle;
    D_1F800000                    = 0x20;

    velocity     = rcos(angle) * D_1F800000;
    work         = g_Task;
    work->proj.x = D_801D2744->proj.x + velocity;

    velocity        = rsin(*angle_cell) * D_1F800000;
    source          = D_801D2744;
    scratch         = g_Task;
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

    g_Task->ticker++;

    work                          = g_Task;
    counter                       = work->orbit_counter + 1;
    VOL(s32, work->orbit_counter) = counter;
    angle                         = SCE10EFF_ORBIT_ANGLE(counter);
    angle_cell                    = &D_1F800004;
    *angle_cell                   = angle;
    D_1F800000                    = 0x20;

    velocity     = rcos(angle) * D_1F800000;
    work         = g_Task;
    work->proj.x = D_801D2744->proj.x + velocity;

    velocity       = rsin(*angle_cell) * D_1F800000;
    g_Task->proj.y = D_801D2744->proj.y + velocity;

    if (TIMER_EXPIRED(g_Task->band)) {
        D_801D2744->ticker++;
        Actor_Clear();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void Scene_DrawBands(s32 band_height, u16 radius, u16 jitter_mask) {
    s16              new_var;
    long             depth;
    long             flag;
    POLY_G4*         primitive;
    SVECTOR*         quad;
    SVECTOR*         prev;
    s32*             depth_cell;
    s32*             cell;
    s32*             ramp;
    SceneBandEffect* work;
    s32              radius_base;
    s32              tpage;
    s32              shade;
    s32              i;
    work        = g_Task;
    depth_cell  = &D_1F800000;
    prev        = &D_1F800014[2];
    quad        = prev - 2;
    *depth_cell = 0x10;
    D_1F800004  = (work->ticker & 0xF) << 8;
    D_1F800008  = work->band * 7;
    shade       = work->band * 13;
    quad[0].vz  = 0;
    quad[0].vy  = FIXED_MUL(rsin((work->ticker & 0xF) << 8), (*depth_cell));
    tpage       = getTPage(0, 1, 320, 256);
    i           = 1;
    cell        = &D_1F800004;
    ramp        = cell + 1;
    GFX_AddDitheredDrawMode(2, tpage);
    radius_base = (s16)radius;
    do {
        work    = g_Task;
        cell[0] = ((work->ticker + i) & 0xF) << 8;
        if RANDOM_MASK (1) {
            new_var  = (s16)jitter_mask;
            cell[-1] = radius_base + (RANDOM_MASK(new_var));
        } else {
            cell[-1] = radius_base - (RANDOM_MASK(new_var));
        }
        prev[0].vx = 0;
        prev[1].vx = 0;
        quad[0].vx = 0;
        prev[0].vy = quad[0].vy;
        prev[0].vz = quad[0].vz;
        prev[1].vy = quad[0].vy - band_height;
        prev[1].vz = quad[0].vz;
        quad[1].vx = 0;
        quad[0].vz = -(i << 6);
        quad[1].vz = -(i << 6);
        quad[0].vy = FIXED_MUL(rsin(cell[0]), cell[-1]);
        quad[1].vy = quad[0].vy - band_height;
        primitive  = GFX_BeginPolyG4(1);
        setRGB0(primitive, cell[1], cell[1], cell[1]);
        setRGB1(primitive, shade, cell[1], 1);
        if (i == 1) {
            setRGB2(primitive, i, i, i);
            setRGB3(primitive, i, i, i);
        } else {
            setRGB2(primitive, cell[1], cell[1], cell[1]);
            setRGB3(primitive, shade, cell[1], 1);
        }
        RotTransPers4(quad, quad + 1, prev, prev + 1, (long*)&primitive->x0, (long*)&primitive->x1, (long*)&primitive->x2, (long*)&primitive->x3, &depth, &flag);
        if (primitive->y2 > 0) {
            GFX_AddPrim(2, sizeof(POLY_G4));
            D_1F800014[0].vy -= band_height;
            D_1F800014[1].vy -= band_height;
            D_1F800014[2].vy -= band_height;
            D_1F800014[3].vy -= band_height;
            primitive = GFX_BeginPolyG4(1);
            setRGB0(primitive, shade, ramp[0], 1);
            setRGB1(primitive, 1, 1, 1);
            if (i == 1) {
                setRGB2(primitive, 1, 1, 1);
                setRGB3(primitive, 1, 1, 1);
            } else {
                setRGB2(primitive, shade, ramp[0], 1);
                setRGB3(primitive, 1, 1, 1);
            }
            RotTransPers4(quad, quad + 1, prev, prev + 1, (long*)&primitive->x0, (long*)&primitive->x1, (long*)&primitive->x2, (long*)&primitive->x3, &depth, &flag);
            GFX_AddPrim(2, sizeof(POLY_G4));
            D_1F800014[0].vy += ((s16)band_height) * 2;
            D_1F800014[1].vy += ((s16)band_height) * 2;
            D_1F800014[2].vy += ((s16)band_height) * 2;
            D_1F800014[3].vy += ((s16)band_height) * 2;
            primitive = GFX_BeginPolyG4(1);
            setRGB0(primitive, shade, ramp[0], 1);
            setRGB1(primitive, ramp[0], ramp[0], ramp[0]);
            if (i == 1) {
                setRGB2(primitive, 1, 1, 1);
                setRGB3(primitive, 1, 1, 1);
            } else {
                setRGB2(primitive, shade, ramp[0], 1);
                setRGB3(primitive, ramp[0], ramp[0], ramp[0]);
            }
            RotTransPers4(quad, quad + 1, prev, prev + 1, (long*)&primitive->x0, (long*)&primitive->x1, (long*)&primitive->x2, (long*)&primitive->x3, &depth, &flag);
            GFX_AddPrim(2, sizeof(POLY_G4));
            D_1F800014[0].vy += band_height;
            D_1F800014[1].vy += band_height;
            D_1F800014[2].vy += band_height;
            D_1F800014[3].vy += band_height;
            primitive = GFX_BeginPolyG4(1);
            setRGB0(primitive, 1, 1, 1);
            setRGB1(primitive, shade, ramp[0], 1);
            if (i == 1) {
                setRGB2(primitive, 1, 1, 1);
                setRGB3(primitive, 1, 1, 1);
            } else {
                setRGB2(primitive, 1, 1, 1);
                setRGB3(primitive, shade, ramp[0], 1);
            }
            RotTransPers4(quad, quad + 1, prev, prev + 1, (long*)&primitive->x0, (long*)&primitive->x1, (long*)&primitive->x2, (long*)&primitive->x3, &depth, &flag);
            GFX_AddPrim(2, sizeof(POLY_G4));
            D_1F800014[0].vy -= ((s16)band_height) * 2;
        }
        i++;
    } while (i < 18);
}
#else
INCLUDE_ASM(Scene_DrawBands);
#endif

MATCH void func_801D1D58(void) {
    D_801D2734[g_Task->step_index]();
    func_801D2658();
    if (g_Task->step_index != 0) {
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

    g_Task->ticker = RANDOM_MASK(0xF);
    g_Task->timer  = 0;
    g_Task->band   = 0;

    work                          = g_Task;
    counter                       = (work->orbit_seed << 5) + 0x10;
    angle                         = SCE10EFF_ORBIT_ANGLE(counter);
    VOL(s32, work->orbit_counter) = counter;
    angle_cell                    = &D_1F800004;
    *angle_cell                   = angle;
    D_1F800000                    = 0x18;

    velocity       = rcos(angle) * D_1F800000;
    g_Task->proj.x = D_801D2744->proj.x + velocity;

    velocity       = rsin(*angle_cell) * D_1F800000;
    g_Task->proj.y = D_801D2744->proj.y + velocity;

    g_Task->proj_z = D_801D2744->proj_z;
    g_Task->step_index++;
}
