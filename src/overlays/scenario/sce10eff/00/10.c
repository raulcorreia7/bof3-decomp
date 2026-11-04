#include "sce10eff_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The overlay's three entry points. @source: read:Scene_RunEffect@0x801D0C10 */
static BattleHandlerTable3 D_801D0C04 = {
    {Scene_EffectBegin, Scene_EffectEnd, Scene_EffectRunState},
};

/* func_801D0C10 */
MATCH void Scene_RunEffect(void) { /* func_801D0C10 */
    BattleHandlerTable3 handlers;

    handlers = D_801D0C04;
    handlers.handlers[((u8*)g_SpadWork)[1]]();
}

/* func_801D0C70 */
MATCH void Scene_EffectBegin(void) { /* func_801D0C70 */
    u8 i;
    u8 slot;

    D_801D2744 = g_SpadWork;

    slot                        = Actor_FindFreeSlot();
    g_ActorSlots[slot].flags_00 = 1;
    g_ActorSlots[slot].type     = 0x69;
    g_ActorSlots[slot].unk_01   = 2;
    g_ActorSlots[slot].unk_02   = 0;
    g_ActorSlots[slot].unk_03   = 0;

    i = 0;
    do {
        slot                      = Actor_FindFreeSlot();
        g_ActorSlots[slot].unk_04 = i;
        i++;
        g_ActorSlots[slot].flags_00 = 1;
        g_ActorSlots[slot].type     = 0x69;
        g_ActorSlots[slot].unk_01   = 2;
        g_ActorSlots[slot].unk_02   = 1;
        g_ActorSlots[slot].unk_03   = 0;
    } while (i < 4);

    i = 0;
    do {
        slot                      = Actor_FindFreeSlot();
        g_ActorSlots[slot].unk_04 = i;
        i++;
        g_ActorSlots[slot].flags_00 = 1;
        g_ActorSlots[slot].type     = 0x69;
        g_ActorSlots[slot].unk_01   = 2;
        g_ActorSlots[slot].unk_02   = 2;
        g_ActorSlots[slot].unk_03   = 0;
    } while (i < 4);

    g_SpadWork->ticker = 0;
    g_SpadWork->unk_01++;
    SND_PlayCue(EMI_CUE_ID(2, 3));
}

/* func_801D0E64 */
MATCH void Scene_EffectEnd(void) { /* func_801D0E64 */
    if (g_SpadWork->ticker == 9) {
        Actor_Clear();
    }
}

/* func_801D0E9C */
MATCH void Scene_EffectRunState(void) { /* func_801D0E9C */
    D_801D2708[g_SpadWork->state]();
}

/* func_801D0EE0 */
MATCH void Scene_EffectSetMatrix(void) { /* func_801D0EE0 */
    SceneBandEffect* scratch;
    SVECTOR          vertex;
    SVECTOR          rotation;
    MATRIX           matrix;
    long             flag;

    PushMatrix();

    scratch = g_SpadWork;

    rotation.vx = 0;
    rotation.vy = 0;
    rotation.vz = ONE / 4;
    if ((scratch->flags & 1u) != 0u) {
        rotation.vz = 0;
    }

    vertex.vx = (s16)(scratch->proj_x >> 9) - 0x4000;
    vertex.vy = (s16)(scratch->proj_y >> 9) - 0x4000;
    vertex.vz = (s16)(-scratch->proj_z / 2);

    RotTrans(&vertex, (VECTOR*)&matrix.t, &flag);
    RotMatrix(&rotation, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

MATCH void func_801D0FAC(void) {
    D_801D2714[g_SpadWork->step_index]();
    func_801D2658();
    if (g_SpadWork->step_index != 0) {
        Scene_EffectSetMatrix();
        Scene_DrawBands(0x60, 0x20, 7);
        PopMatrix();
    }
}

MATCH void func_801D1034(void) {
    SceneBandEffect* source;
    SceneBandEffect* work;
    SceneBandEffect* scratch;
    s32              coord_y;
    s16              distance;

    g_SpadWork->ticker = (u8)(RANDOM_MASK(0xF));
    g_SpadWork->timer  = 0;
    g_SpadWork->band   = 0;

    source       = D_801D2744;
    work         = g_SpadWork;
    work->proj_x = source->proj_x;
    coord_y      = source->proj_y;
    work->proj_y = coord_y;
    distance     = Area_SampleHeight(work->proj_x, coord_y);

    scratch = g_SpadWork;
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
    work = g_SpadWork;
    work->ticker++;
    work = g_SpadWork;
    work->timer--;
    if (work->timer == 0) {
        work = g_SpadWork;
        work->step_index++;
    }
}

MATCH void func_801D11A0(void) {
    SceneBandEffect* work;
    u8               count;

    /* A store through the pointer may alias the cell, so each step reloads
     * it. */
    work = g_SpadWork;
    work->ticker++;
    work       = g_SpadWork;
    count      = work->band - 1;
    work->band = count;
    if (count == 0) {
        D_801D2744->ticker++;
        Actor_Clear();
    }
}

MATCH void func_801D1218(void) {
    SceneBandEffect* work;

    work = g_SpadWork;
    D_801D2724[work->step_index]();
    func_801D2658();
    if (g_SpadWork->step_index != 0) {
        Scene_EffectSetMatrix();
        Scene_DrawBands(0x20, 0x50, 0x1F);
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

    g_SpadWork->ticker = (u8)(RANDOM_MASK(0xF));
    g_SpadWork->timer  = 0;
    g_SpadWork->band   = 0;

    work                          = g_SpadWork;
    counter                       = work->orbit_seed << 5;
    VOL(s32, work->orbit_counter) = counter;
    angle                         = SCE10EFF_ORBIT_ANGLE(counter);
    angle_cell                    = &D_1F800004;
    *angle_cell                   = angle;
    D_1F800000                    = 0x20;

    velocity     = rcos(angle) * D_1F800000;
    work         = g_SpadWork;
    work->proj_x = D_801D2744->proj_x + velocity;

    velocity        = rsin(*angle_cell) * D_1F800000;
    source          = D_801D2744;
    scratch         = g_SpadWork;
    scratch->proj_y = source->proj_y + velocity;
    scratch->proj_z = (u16)source->proj_z;
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

    g_SpadWork->ticker++;

    work                          = g_SpadWork;
    counter                       = work->orbit_counter + 1;
    VOL(s32, work->orbit_counter) = counter;
    angle                         = SCE10EFF_ORBIT_ANGLE(counter);
    angle_cell                    = &D_1F800004;
    *angle_cell                   = angle;
    D_1F800000                    = 0x20;

    velocity     = rcos(angle) * D_1F800000;
    work         = g_SpadWork;
    work->proj_x = D_801D2744->proj_x + velocity;

    velocity           = rsin(*angle_cell) * D_1F800000;
    g_SpadWork->proj_y = D_801D2744->proj_y + velocity;

    if (TIMER_EXPIRED(g_SpadWork->band)) {
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
    work        = g_SpadWork;
    depth_cell  = &D_1F800000;
    prev        = &D_1F800014[2];
    quad        = prev - 2;
    *depth_cell = 0x10;
    D_1F800004  = (work->ticker & 0xF) << 8;
    D_1F800008  = work->band * 7;
    shade       = work->band * 13;
    quad[0].vz  = 0;
    quad[0].vy  = FIXED_MUL(rsin((work->ticker & 0xF) << 8), (*depth_cell));
    tpage       = (GetGraphType() != 1) ? ((GetGraphType() == 2) ? (0xA5) : (0x35)) : (0xA5);
    i           = 1;
    cell        = &D_1F800004;
    ramp        = cell + 1;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, 0x0C);
    radius_base = (s16)radius;
    do {
        work    = g_SpadWork;
        cell[0] = ((work->ticker + i) & 0xF) << 8;
        if (RANDOM_MASK(1)) {
            new_var  = (s16)jitter_mask;
            cell[-1] = radius_base + (rand() & new_var);
        } else {
            cell[-1] = radius_base - (rand() & new_var);
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
        primitive  = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(primitive);
        PSX_SET_SEMI_TRANSPARENT(primitive);
        primitive->r0 = cell[1];
        primitive->g0 = cell[1];
        primitive->b0 = cell[1];
        primitive->r1 = shade;
        primitive->g1 = cell[1];
        primitive->b1 = 1;
        if (i == 1) {
            primitive->r2 = i;
            primitive->g2 = i;
            primitive->b2 = i;
            primitive->r3 = i;
            primitive->g3 = i;
            primitive->b3 = i;
        } else {
            primitive->r2 = cell[1];
            primitive->g2 = cell[1];
            primitive->b2 = cell[1];
            primitive->r3 = shade;
            primitive->g3 = cell[1];
            primitive->b3 = 1;
        }
        RotTransPers4(quad, quad + 1, prev, prev + 1, (long*)(((u8*)primitive) + 8), (long*)(((u8*)primitive) + 0x10),
                      (long*)(((u8*)primitive) + 0x18), (long*)(((u8*)primitive) + 0x20), &depth, &flag);
        if (primitive->y2 > 0) {
            GFX_AddPrim(2, 0x24);
            D_1F800014[0].vy -= band_height;
            D_1F800014[1].vy -= band_height;
            D_1F800014[2].vy -= band_height;
            D_1F800014[3].vy -= band_height;
            primitive = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(primitive);
            PSX_SET_SEMI_TRANSPARENT(primitive);
            primitive->r0 = shade;
            primitive->g0 = ramp[0];
            primitive->b0 = 1;
            primitive->r1 = 1;
            primitive->g1 = 1;
            primitive->b1 = 1;
            if (i == 1) {
                primitive->r2 = 1;
                primitive->g2 = 1;
                primitive->b2 = 1;
                primitive->r3 = 1;
                primitive->g3 = 1;
                primitive->b3 = 1;
            } else {
                primitive->r2 = shade;
                primitive->g2 = ramp[0];
                primitive->b2 = 1;
                primitive->r3 = 1;
                primitive->g3 = 1;
                primitive->b3 = 1;
            }
            RotTransPers4(quad, quad + 1, prev, prev + 1, (long*)(((u8*)primitive) + 8),
                          (long*)(((u8*)primitive) + 0x10), (long*)(((u8*)primitive) + 0x18),
                          (long*)(((u8*)primitive) + 0x20), &depth, &flag);
            GFX_AddPrim(2, 0x24);
            D_1F800014[0].vy += ((s16)band_height) * 2;
            D_1F800014[1].vy += ((s16)band_height) * 2;
            D_1F800014[2].vy += ((s16)band_height) * 2;
            D_1F800014[3].vy += ((s16)band_height) * 2;
            primitive = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(primitive);
            PSX_SET_SEMI_TRANSPARENT(primitive);
            primitive->r0 = shade;
            primitive->g0 = ramp[0];
            primitive->b0 = 1;
            primitive->r1 = ramp[0];
            primitive->g1 = ramp[0];
            primitive->b1 = ramp[0];
            if (i == 1) {
                primitive->r2 = 1;
                primitive->g2 = 1;
                primitive->b2 = 1;
                primitive->r3 = 1;
                primitive->g3 = 1;
                primitive->b3 = 1;
            } else {
                primitive->r2 = shade;
                primitive->g2 = ramp[0];
                primitive->b2 = 1;
                primitive->r3 = ramp[0];
                primitive->g3 = ramp[0];
                primitive->b3 = ramp[0];
            }
            RotTransPers4(quad, quad + 1, prev, prev + 1, (long*)(((u8*)primitive) + 8),
                          (long*)(((u8*)primitive) + 0x10), (long*)(((u8*)primitive) + 0x18),
                          (long*)(((u8*)primitive) + 0x20), &depth, &flag);
            GFX_AddPrim(2, 0x24);
            D_1F800014[0].vy += band_height;
            D_1F800014[1].vy += band_height;
            D_1F800014[2].vy += band_height;
            D_1F800014[3].vy += band_height;
            primitive = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(primitive);
            PSX_SET_SEMI_TRANSPARENT(primitive);
            primitive->r0 = 1;
            primitive->g0 = 1;
            primitive->b0 = 1;
            primitive->r1 = shade;
            primitive->g1 = ramp[0];
            primitive->b1 = 1;
            if (i == 1) {
                primitive->r2 = 1;
                primitive->g2 = 1;
                primitive->b2 = 1;
                primitive->r3 = 1;
                primitive->g3 = 1;
                primitive->b3 = 1;
            } else {
                primitive->r2 = 1;
                primitive->g2 = 1;
                primitive->b2 = 1;
                primitive->r3 = shade;
                primitive->g3 = ramp[0];
                primitive->b3 = 1;
            }
            RotTransPers4(quad, quad + 1, prev, prev + 1, (long*)(((u8*)primitive) + 8),
                          (long*)(((u8*)primitive) + 0x10), (long*)(((u8*)primitive) + 0x18),
                          (long*)(((u8*)primitive) + 0x20), &depth, &flag);
            GFX_AddPrim(2, 0x24);
            D_1F800014[0].vy -= ((s16)band_height) * 2;
        }
        i++;
    } while (i < 18);
}
#else
/* The draft keeps the radius, angle and ramp in the scratchpad cells D_1F800000, D_1F800004 and D_1F800008 and its score is not measured; the next lift measures it first. */
INCLUDE_ASM(Scene_DrawBands);
#endif

MATCH void func_801D1D58(void) {
    D_801D2734[g_SpadWork->step_index]();
    func_801D2658();
    if (g_SpadWork->step_index != 0) {
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

    g_SpadWork->ticker = (u8)(RANDOM_MASK(0xF));
    g_SpadWork->timer  = 0;
    g_SpadWork->band   = 0;

    work                          = g_SpadWork;
    counter                       = (work->orbit_seed << 5) + 0x10;
    angle                         = SCE10EFF_ORBIT_ANGLE(counter);
    VOL(s32, work->orbit_counter) = counter;
    angle_cell                    = &D_1F800004;
    *angle_cell                   = angle;
    D_1F800000                    = 0x18;

    velocity           = rcos(angle) * D_1F800000;
    g_SpadWork->proj_x = D_801D2744->proj_x + velocity;

    velocity           = rsin(*angle_cell) * D_1F800000;
    g_SpadWork->proj_y = D_801D2744->proj_y + velocity;

    g_SpadWork->proj_z = (u16)D_801D2744->proj_z;
    g_SpadWork->step_index++;
}
