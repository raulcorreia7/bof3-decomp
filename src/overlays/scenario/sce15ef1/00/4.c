#include "sce15ef1_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"
#include "overlays/scenario/shared/Scene_AppendTrailDots.h"

MATCH void func_801D0C48(void) {
    Actor* work;

    work           = TASK(Actor);
    work->angle_x  = g_Game.members[0].pos.x.fixed;
    work->angle_y  = g_Game.members[0].pos.y.fixed;
    work->angle_z  = g_Game.members[0].pos.z.fixed + TO_COORD(128);
    work->timer    = 8;
    work->screen_x = 0;
    TASK(Actor)->header.mode += 1;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 11));
}

MATCH void func_801D0CC0(void) {
    u16 screen_x;
    u8  mode;

    screen_x              = TASK(Actor)->screen_x + 0x20;
    TASK(Actor)->screen_x = screen_x;
    GFX_DrawColorFan(&TASK(Actor)->angle_x, (s16)screen_x, 6);
    mode               = TASK(Actor)->timer - 1;
    TASK(Actor)->timer = mode;
    if (!(mode & BYTE_MASK)) {
        TASK(Actor)->timer = 64;
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801D0D54(void) {
    u8 mode;

    GFX_DrawColorFan(&TASK(Actor)->angle_x, (s16)TASK(Actor)->screen_x, 6);
    mode               = TASK(Actor)->timer - 1;
    TASK(Actor)->timer = mode;
    if (!(mode & BYTE_MASK)) {
        TASK(Actor)->timer = 32;
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801D0DD8(void) {
    SpinEffect* spin;
    u8          timer;
    u8          i;

    TASK(Actor)->angle_z += TO_COORD(12);
    TASK(Actor)->screen_x -= 6;
    GFX_DrawColorFan(&TASK(Actor)->angle_x, (s16)TASK(Actor)->screen_x, 6);
    timer              = TASK(Actor)->timer - 1;
    TASK(Actor)->timer = timer;
    if ((timer & BYTE_MASK) == 0) {
        TASK(Actor)->timer  = 32;
        TASK(Actor)->unk_06 = 0;
        TASK(Actor)->header.mode++;
        func_801D199C();
        TASK(Actor)->pos.x.fixed = TASK(Actor)->angle_x;
        TASK(Actor)->pos.y.fixed = TASK(Actor)->angle_y;
        TASK(Actor)->pos.z.fixed = TASK(Actor)->angle_z;
        spin                     = g_WorldSpins;
        i                        = 0;
        do {
            Area_InitSpin(spin);
            i++;
            spin++;
        } while (i < 16);
        while (i < 32) {
            spin->scale = 0;
            spin->fade  = 0;
            spin++;
            i++;
        }
    }
}

MATCH void func_801D0F10(void) {
    s32 origin_x;
    s32 origin_y;
    s32 origin_z;
    u8  mode;

    if ((TASK(Actor)->unk_06++ & 0x3) == 0) {
        func_801D19C8();
    }
    func_801D2088();
    func_801D1A60();
    if (g_ScriptVars[0] == 0x14) {
        origin_x = TASK(Actor)->angle_x;
        origin_y = TASK(Actor)->angle_y;
        origin_z = TASK(Actor)->angle_z;
        mode     = TASK(Actor)->header.mode + 1;
        setVector(TASK(Actor), 0, 0, 0);
        TASK(Actor)->unk_18      = origin_x;
        TASK(Actor)->unk_1C      = origin_y;
        TASK(Actor)->gravity     = origin_z;
        TASK(Actor)->angle_x     = (0x2F8000 - TASK(Actor)->angle_x) >> 7;
        TASK(Actor)->angle_y     = (0x278000 - TASK(Actor)->angle_y) >> 7;
        TASK(Actor)->angle_z     = (TO_COORD(3840) - TASK(Actor)->angle_z) >> 7;
        TASK(Actor)->header.mode = mode;
    }
}

MATCH void func_801D0FEC(void) {
    if ((TASK(Actor)->unk_06++ & 0x3) == 0) {
        func_801D19C8();
    }
    func_801D2088();
    func_801D1A60();
    TASK(Actor)->timer = 32;
    TASK(Actor)->header.mode += 1;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x09));
}

MATCH void func_801D106C(void) {
    Actor*      work;
    SpinEffect* spin;
    u8          timer;
    u8          i;

    if ((TASK(Actor)->unk_06++ & 0x3) == 0) {
        func_801D19C8();
    }
    func_801D1A60();
    func_801D2088();
    func_801D1678(&TASK(Actor)->unk_18, &TASK(Actor)->pos.x, 0x40);

    work = TASK(Actor);
    work->vx += work->angle_x;
    work->vy += work->angle_y;
    work->vz += work->angle_z;
    work->unk_18 += work->vx;
    work->unk_1C += work->vy;
    work->gravity += work->vz;
    if (work->unk_18 <= 0x2F7FFF) {
        work->unk_18  = 0x2F8000;
        work->unk_1C  = 0x278000;
        work->gravity = TO_COORD(3840);
    }

    TASK(Actor)->unk_03 -= 4;
    timer              = TASK(Actor)->timer - 1;
    TASK(Actor)->timer = timer;
    if (timer == 0) {
        func_801D2138(&TASK(Actor)->pos.x.fixed, &TASK(Actor)->unk_18);
        func_801D2138(&TASK(Actor)->pos.y.fixed, &TASK(Actor)->unk_1C);
        func_801D2138(&TASK(Actor)->pos.z.fixed, &TASK(Actor)->gravity);
        spin = &g_WorldSpins[16];
        i    = 16;
        do {
            Area_InitSpin(spin);
            i++;
            spin++;
        } while (i < 32);
        func_801D2138(&TASK(Actor)->pos.x.fixed, &TASK(Actor)->unk_18);
        func_801D2138(&TASK(Actor)->pos.y.fixed, &TASK(Actor)->unk_1C);
        func_801D2138(&TASK(Actor)->pos.z.fixed, &TASK(Actor)->gravity);
        TASK(Actor)->timer = 0x80;
        TASK(Actor)->header.mode++;
    }
}

MATCH void func_801D12A0(void) {
    if ((TASK(Actor)->unk_06++ & 0x3) == 0) {
        func_801D19C8();
        func_801D2138(&TASK(Actor)->pos.x.fixed, &TASK(Actor)->unk_18);
        func_801D2138(&TASK(Actor)->pos.y.fixed, &TASK(Actor)->unk_1C);
        func_801D2138(&TASK(Actor)->pos.z.fixed, &TASK(Actor)->gravity);
        func_801D19C8();
        func_801D2138(&TASK(Actor)->pos.x.fixed, &TASK(Actor)->unk_18);
        func_801D2138(&TASK(Actor)->pos.y.fixed, &TASK(Actor)->unk_1C);
        func_801D2138(&TASK(Actor)->pos.z.fixed, &TASK(Actor)->gravity);
    }
    func_801D1A60();
    func_801D2088();
    func_801D1678(&TASK(Actor)->unk_18, &TASK(Actor)->pos.x, 0x40);
    if (g_ScriptVars[0] == 0x17) {
        TASK(Actor)->unk_03 = 0x80;
        TASK(Actor)->timer  = 8;
        TASK(Actor)->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x0A));
    }
}

MATCH void func_801D13F4(void) {
    u8 remaining;

    TASK(Actor)->screen_x -= 0x10;
    TASK(Actor)->unk_03 -= 8;
    func_801D1A60();
    func_801D1678(&TASK(Actor)->unk_18, &TASK(Actor)->pos.x, TASK(Actor)->unk_03);
    remaining          = TASK(Actor)->timer - 1;
    TASK(Actor)->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        Actor_Clear();
    }
}

/* Draws a fan of colored triangles. */
/* func_801D147C */
MATCH void GFX_DrawColorFan(s32* pos, s16 origin, s32 flags) {
    DVECTOR  screen;
    DVECTOR  point;
    DVECTOR  size;
    DVECTOR  scale;
    MATRIX   camera;
    POLY_G3* primitive;
    s32      angle;
    s32      i;

    GFX_AddDitheredDrawMode(2u, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x2C0, 0x100));
    Camera_SetMatrix(&camera);
    Camera_ProjectPoint(pos, &screen);
    size.vx = size.vy = origin;
    Game_ProjectWorldPoint(pos, &size, &scale);
    scale.vx += g_FrameCount & 1;
    point.vx = screen.vx + scale.vx;
    point.vy = screen.vy;
    angle    = 0;
    i        = 0;
    do {
        primitive = GFX_BeginPolyG3(1);
        setXY2(primitive, screen.vx, screen.vy, point.vx, point.vy);
        angle += 128;
        point.vx      = screen.vx + (((s16)scale.vx * rcos((u16)angle)) >> 0xC);
        point.vy      = screen.vy + (((s16)scale.vx * rsin((u16)angle)) >> 0xC);
        primitive->x2 = point.vx;
        primitive->y2 = point.vy;
        setRGB0(primitive, (flags & 4) << 5, (flags & 2) << 6, (flags & 1) << 7);
        setRGB1(primitive, 0, 0, 0);
        setRGB2(primitive, 0, 0, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G3));
        i += 1;
    } while ((i & BYTE_MASK) < 32U);
}

MATCH void func_801D1678(s32* from, s32* to, u8 intensity) {
    POLY_G4* prim;
    TILE*    segment;
    VECTOR   current;
    VECTOR   step;
    DVECTOR  projected;
    s32      phase;

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    Camera_ProjectPoint(from, &projected);
    setXY2(prim, projected.vx + 1, projected.vy - 1, projected.vx, projected.vy);
    Camera_ProjectPoint(to, &projected);
    prim->x2 = projected.vx + 1;
    prim->y2 = projected.vy - 1;
    prim->x3 = projected.vx;
    prim->y3 = projected.vy;
    setRGB0(prim, 0, 0, 0);
    setRGB1(prim, intensity, intensity, 0);
    setRGB2(prim, 0, 0, 0);
    setRGB3(prim, intensity, intensity, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    Camera_ProjectPoint(from, &projected);
    setXY2(prim, projected.vx, projected.vy, projected.vx - 1, projected.vy + 1);
    Camera_ProjectPoint(to, &projected);
    prim->x2 = projected.vx;
    prim->y2 = projected.vy;
    prim->x3 = projected.vx - 1;
    prim->y3 = projected.vy + 1;
    setRGB0(prim, intensity, intensity, 0);
    setRGB1(prim, 0, 0, 0);
    setRGB2(prim, intensity, intensity, 0);
    setRGB3(prim, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));

    setVector(&step, TASK(Actor)->angle_x, TASK(Actor)->angle_y, TASK(Actor)->angle_z);
    phase = g_FrameCount & 0xF;
    setVector(&current, to[0] + step.vx * phase, to[1] + step.vy * phase, to[2] + step.vz * phase);
    while (from[0] < current.vx) {
        Camera_ProjectPoint(&current.vx, &projected);
        segment = (TILE*)g_GfxPrimCursor;
        SetTile1(segment);
        SetSemiTrans(segment, 1);
        setXY0(segment, projected.vx, projected.vy);
        setRGB0(segment, intensity, intensity, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, 12);
        current.vx += TASK(Actor)->angle_x << 4;
        current.vy += TASK(Actor)->angle_y << 4;
        current.vz += TASK(Actor)->angle_z << 4;
    }
}

MATCH void func_801D199C(void) {
    u8             i;
    AreaSpawnSlot* slot;

    slot = D_801D39A8;
    for (i = 0; i < EFFECT_SLOT_COUNT; i++, slot++) {
        slot->active = 0;
    }
}

MATCH void func_801D19C8(void) {
    u8             i;
    AreaSpawnSlot* slot;
    Actor*         actor;

    slot = D_801D39A8;
    for (i = 0; i < EFFECT_SLOT_COUNT; slot++, i++) {
        if (slot->active == 0) {
            slot->active = 1;
            slot->unk_01 = 0;
            slot->life   = 16;
            actor        = TASK(Actor);
            WorldPos_Copy(&slot->pos, &actor->pos);
            slot->radius     = 256;
            slot->core_shade = 96;
            slot->rim_shade  = 0;
            return;
        }
    }
}

MATCH s32 func_801D1A60(void) {
    MATRIX         matrix;
    u8             i;
    s32            alive;
    AreaSpawnSlot* slot;

    alive = 0;
    Camera_SetMatrix(&matrix);
    slot = D_801D39A8;
    for (i = 0; i < EFFECT_SLOT_COUNT; slot++, i++) {
        if (slot->active != 0) {
            alive = 1;
            slot->radius -= 0x10;
            if (--slot->life == 0) {
                slot->active = 0;
            }
            Area_DrawSpawnSlot(slot);
        }
    }
    return alive;
}

#include "shared/Area_DrawSpawnSlot.h"

MATCH void func_801D1CD4(const SpinEffect* spin) {
    SpinEffect* work;
    POLY_G3*    primitive;
    s32         point[3];
    s16         fade;
    s16         tmp;
    s16         shade;

    work      = (SpinEffect*)spin;
    primitive = (POLY_G3*)g_GfxPrimCursor;

    SetPolyG3(primitive);
    SetSemiTrans(primitive, 1);
    Camera_ProjectPoint(&work->origin.x, POLY_XY(primitive, 0));

    point[0] = ((rcos(work->spin_angle) * work->vertex_a.vx - rsin(work->spin_angle) * work->vertex_a.vy) >> 8) * work->scale;
    point[1] = ((rsin(work->spin_angle) * work->vertex_a.vx + rcos(work->spin_angle) * work->vertex_a.vy) >> 8) * work->scale;
    point[2] = (work->vertex_a.vz << 12) * work->scale;
    point[0] += work->origin.x;
    point[1] += work->origin.y;
    point[2] += work->origin.z;
    Camera_ProjectPoint(point, POLY_XY(primitive, 1));

    point[0] = ((rcos(work->spin_angle) * work->vertex_b.vx - rsin(work->spin_angle) * work->vertex_b.vy) >> 8) * work->scale;
    point[1] = ((rsin(work->spin_angle) * work->vertex_b.vx + rcos(work->spin_angle) * work->vertex_b.vy) >> 8) * work->scale;
    point[2] = (work->vertex_b.vz << 12) * work->scale;
    point[0] += work->origin.x;
    point[1] += work->origin.y;
    point[2] += work->origin.z;
    Camera_ProjectPoint(point, POLY_XY(primitive, 2));

    fade = work->fade;
    tmp  = fade;
    if (fade < 0) {
        shade = 0;
    } else {
        shade = tmp;
        if (fade >= 256) {
            shade = 0xFF;
        }
    }

    setRGB0(primitive, shade, shade, 0);
    setRGB1(primitive, 0, 0, 0);
    setRGB2(primitive, 0, 0, 0);

    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G3));
}

#include "shared/Area_InitSpin.h"

MATCH void func_801D2088(void) {
    MATRIX      matrix;
    SpinEffect* spin;
    u16*        angle;
    s32         i;

    GFX_AddDitheredDrawMode(2, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    Camera_SetMatrix(&matrix);
    spin  = g_WorldSpins;
    i     = 0;
    angle = &spin->spin_angle;
    do {
        func_801D1CD4(spin);
        spin += 1;
        *angle += 16;
        i += 1;
        angle += sizeof(SpinEffect) / sizeof(*angle);
    } while ((i & BYTE_MASK) < 0x20U);
}

MATCH void func_801D2138(s32* first, s32* second) {
    s32 folded;
    s32 swapped;

    folded  = *first ^ *second;
    *first  = folded;
    swapped = *second ^ folded;
    *second = swapped;
    *first ^= swapped;
}

MATCH void func_801D2170(void) {
    SYS_DISPATCH_TASK(D_801D3954, 1, g_Task);
}

/* Spawn an actor from the current one's record, start its script when it is drawn, and advance the mode. */
MATCH void func_801D21B4(void) {
    u8            slot;
    SpawnedActor* spawned_actor;
    Actor*        actor;
    Actor*        parent;

    slot = Actor_FindFreeSpawned();
    if (slot != GAME_NONE) {
        D_801D40AC    = 1;
        spawned_actor = &g_SpawnedActors[slot];
        GFX_ClearRect(0x340, 0x100, 0x80, 0x100);
        *spawned_actor      = *(SpawnedActor*)TASK(Actor)->unk_4C;
        actor               = (Actor*)spawned_actor;
        actor->header.flags = 1;
        actor->header.mode  = 2;
        actor->header.step  = 0;
        actor->unk_05       = 0x3A;
        actor->screen_x     = D_801D393C[D_801D40AC].x;
        actor->screen_y     = D_801D393C[D_801D40AC].y;
        if (actor->active_flags & 1) {
            actor->sheet_page = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 0x340, 0x100);
            actor->sheet_row  = 0x80;
        }
        actor->active_flags |= 0x88;
        parent = TASK(Actor);
        g_Task = actor;
        if (actor->active_flags & 1) {
            if (actor->unk_2C == 0) {
                Script_Begin(0x4D, 0x1C);
                TASK(Actor)->mirror = 0;
            } else {
                Script_Begin(0x50, 0x24);
            }
        }
        Area_AddGridActor();
        func_80196070();
        g_Task        = parent;
        parent->timer = 2;
    }
    TASK(Actor)->header.mode += 1;
}

MATCH void func_801D23A0(void) {
    u8     mode;
    RECT   rect;
    Actor* actor;

    actor        = TASK(Actor);
    mode         = actor->timer - 1;
    actor->timer = mode;
    if (!(mode & BYTE_MASK)) {
        setRECT(&rect, 832, 256, D_801D393C[D_801D40AC].w, D_801D393C[D_801D40AC].h);
        StoreImage(&rect, (u32*)AREA_WORK);
        D_801D40B0         = (u16*)AREA_WORK;
        D_801D40B4         = (TrailDot*)(AREA_WORK + 0x5A00);
        D_801D40A8         = 0;
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.mode++;
    }
}

MATCH void func_801D2474(void){SCENE_APPEND_TRAIL_DOTS()}

MATCH void func_801D26BC(void) {
    u8        order[16];
    u16       i;
    u16       j;
    u8        a;
    u8        b;
    u8        tmp;
    TrailDot* dot;

    for (i = 0; i < 16; i++) {
        order[i] = i & 1;
    }

    dot = MEM_PTR(TrailDot, AREA_WORK + 0x5A00);
    j   = 0;
    for (i = 0; i < D_801D40A8; i++) {
        if ((i & 0xF) == 0) {
            j = 0;
            do {
                a = rand() & 0xF;
                j++;
                b        = rand() & 0xF;
                tmp      = order[b];
                order[b] = order[a];
                order[a] = tmp;
            } while (j < 16);
            j = 0;
        }

        dot->active = order[j++];
        if (TASK(Actor)->param.unk_0B == 0) {
            dot->dx = (rand() & 0x1F) - 16;
            dot->dy = (rand() & 0x1F) - 16;
        } else {
            dot->dx = rand() & 0xF;
            dot->dy = rand() & 0xF;
            if (dot->dx < dot->dy) {
                dot->dx ^= dot->dy;
                dot->dy ^= dot->dx;
                dot->dx ^= dot->dy;
            }
            dot->dy = -dot->dy;
        }
        if (TASK(Actor)->unk_06 == 0) {
            dot->life = (rand() & 0x1E) + 10;
            dot->x -= dot->dx * dot->life;
            dot->y -= dot->dy * dot->life;
        } else {
            dot->life = 40 - (rand() & 0x1E);
        }
        dot++;
    }

    TASK(Actor)->timer = 80;
    TASK(Actor)->header.mode++;
    SND_SEPlay(0x20C);
}

MATCH void func_801D2934(void) {
    Actor*    actor;
    TrailDot* dot;
    TILE_1*   tile;
    u16       i;
    u8        timer;

    actor = (Actor*)TASK(Actor)->unk_4C;
    actor->header.flags |= ACTOR_FLAG_HIDDEN;
    dot = MEM_PTR(TrailDot, AREA_WORK + 0x5A00);
    for (i = 0; i < D_801D40A8; dot++, i++) {
        if (dot->active != 0) {
            if (TASK(Actor)->unk_06 == 0) {
                if (dot->life != 0) {
                    dot->x += dot->dx;
                    dot->y += dot->dy;
                    dot->life--;
                }
            } else if (dot->life != 0) {
                dot->life--;
            } else {
                dot->x += dot->dx;
                dot->y += dot->dy;
            }
            tile = (TILE_1*)g_GfxPrimCursor;
            SetTile1(tile);
            setXY0(tile, dot->x, dot->y);
            setRGB0(tile, (dot->color & 0x1F) << 3, (dot->color & 0x3E0) >> 2, (dot->color & 0x7C00) >> 7);
            GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(TILE_1));
        }
        dot->active ^= 1;
    }
    timer              = TASK(Actor)->timer - 1;
    TASK(Actor)->timer = timer;
    if (timer == 0) {
        TASK(Actor)->header.mode++;
    }
}

MATCH void func_801D2B44(void) {
    Actor_Clear();
}

MATCH void func_801D2B64(void) {
    SYS_DISPATCH_TASK(D_801D396C, 1, g_Task);
}

MATCH void func_801D2BA8(void) {
    Actor* work;

    work         = TASK(Actor);
    work->timer  = 20;
    work->vx     = 0;
    work->vy     = 0;
    work->unk_18 = 0;
    work->unk_1C = 0;
    TASK(Actor)->header.mode++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 8));
}

MATCH void func_801D2C00(void) {
    Actor* work;
    u8     timer;

    work = TASK(Actor);
    work->unk_18 += 0x200;
    work->unk_1C += 0x100;
    work->vx += work->unk_18;
    work->vy += work->unk_1C;
    func_801D36BC(&work->pos.x.fixed, work->vx, work->vy);
    timer              = TASK(Actor)->timer - 1;
    TASK(Actor)->timer = timer;
    if (timer == 0) {
        Actor_Clear();
    }
}

/* Runs the actor's speed up over 20 steps, then reverses the accumulated speed
 * and hands over to the next mode. */
MATCH void func_801D2C94(void) {
    Actor* work;
    Actor* actor;
    Actor* arm;
    Actor* state;
    s32*   pairs;
    u8     i;

    work         = TASK(Actor);
    work->vx     = 0;
    work->vy     = 0;
    work->unk_18 = 0;
    work->unk_1C = 0;
    actor        = work;
    for (i = 0; i < 20; i++) {
        actor->unk_18 += 0x100;
        actor->unk_1C += 0x200;
        actor->vx += actor->unk_18;
        actor->vy += actor->unk_1C;
    }
    arm        = TASK(Actor);
    arm->timer = 20;
    pairs      = &arm->vx;
    pairs[0]   = -pairs[0];
    pairs[1]   = -pairs[1];
    state      = TASK(Actor);
    state->header.mode++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 8));
}

MATCH void func_801D2D5C(void) {
    Actor* work;
    Actor* work2;
    u8     timer;

    work = TASK(Actor);
    func_801D36BC(&work->pos.x.fixed, work->vx, work->vy);
    work2        = TASK(Actor);
    timer        = work2->timer - 1;
    work2->timer = timer;
    work2->vx += work2->unk_18;
    work2->vy += work2->unk_1C;
    work2->unk_18 -= 0x100;
    work2->unk_1C -= 0x200;
    if (timer == 0) {
        Actor_Clear();
    }
}

MATCH void func_801D2DEC(void) {
    SYS_DISPATCH_TASK(D_801D397C, 1, g_Task);
}

/* At script value 0x29 spawn an actor from the current one's record and run its script, then advance the mode. */
MATCH void func_801D2E30(void) {
    u8            slot;
    SpawnedActor* spawned_actor;
    Actor*        actor;
    Actor*        parent;

    if (g_ScriptVars[0] == 0x29) {
        slot = Actor_FindFreeSpawned();
        if (slot != GAME_NONE) {
            D_801D40AC    = 1;
            spawned_actor = &g_SpawnedActors[slot];
            GFX_ClearRect(0x340, 0x100, 0x80, 0x100);
            *spawned_actor      = *(SpawnedActor*)TASK(Actor)->unk_4C;
            actor               = (Actor*)spawned_actor;
            actor->header.flags = 1;
            actor->header.mode  = 2;
            actor->header.step  = 0;
            actor->unk_05       = 0x3A;
            actor->screen_x     = D_801D393C[D_801D40AC].x;
            actor->screen_y     = D_801D393C[D_801D40AC].y;
            actor->sheet_page   = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 0x340, 0x100);
            actor->sheet_row    = 0x80;
            actor->active_flags |= 0x88;
            parent = TASK(Actor);
            g_Task = actor;
            Script_Select(7);
            Area_AddGridActor();
            func_80196070();
            g_Task        = parent;
            parent->timer = 2;
        }
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801D2FD8(void) {
    u8     mode;
    RECT   rect;
    Actor* actor;

    actor        = TASK(Actor);
    mode         = actor->timer - 1;
    actor->timer = mode;
    if (!(mode & BYTE_MASK)) {
        setRECT(&rect, 832, 256, D_801D393C[D_801D40AC].w, D_801D393C[D_801D40AC].h);
        StoreImage(&rect, (u32*)AREA_WORK);
        D_801D40B0         = (u16*)AREA_WORK;
        D_801D40B4         = (TrailDot*)(AREA_WORK + 0x5A00);
        D_801D40A8         = 0;
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.mode++;
    }
}

MATCH void func_801D30AC(void){SCENE_APPEND_TRAIL_DOTS()}

MATCH void func_801D32F4(void) {
    u8        order[16];
    u16       i;
    u16       j;
    u8        a;
    u8        b;
    u8        tmp;
    TrailDot* dot;

    for (i = 0; i < 16; i++) {
        order[i] = i & 1;
    }

    dot = MEM_PTR(TrailDot, AREA_WORK + 0x5A00);
    j   = 0;
    for (i = 0; i < D_801D40A8; i++) {
        if ((i & 0xF) == 0) {
            j = 0;
            do {
                a = rand() & 0xF;
                j++;
                b        = rand() & 0xF;
                tmp      = order[b];
                order[b] = order[a];
                order[a] = tmp;
            } while (j < 16);
            j = 0;
        }

        dot->active = order[j++];
        dot->dx     = rand() & 0xF;
        dot->dy     = rand() & 0xF;
        if (dot->dx < dot->dy) {
            dot->dx ^= dot->dy;
            dot->dy ^= dot->dx;
            dot->dx ^= dot->dy;
        }
        dot->dy   = -dot->dy;
        dot->life = (rand() & 0x1E) + 10;
        dot->x += dot->dx * dot->life;
        dot->y += dot->dy * dot->life;
        dot++;
    }

    TASK(Actor)->timer = 80;
    TASK(Actor)->header.mode++;
    SND_SEPlay(0x20C);
}

/* Step the dot trail: move and draw each live dot, then advance when the countdown ends. */
MATCH void func_801D34F0(void) {
    TrailDot* dot;
    u16       i;
    TILE_1*   tile;

    ((Actor*)TASK(Actor)->unk_4C)->header.flags |= ACTOR_FLAG_HIDDEN;
    dot = MEM_PTR(TrailDot, AREA_WORK + 0x5A00);
    for (i = 0; i < D_801D40A8; dot++, i++) {
        if (dot->active) {
            if (dot->life != 0) {
                dot->x -= dot->dx;
                dot->y -= dot->dy;
                dot->life--;
            }
            tile = (TILE_1*)g_GfxPrimCursor;
            SetTile1(tile);
            setXY0(tile, dot->x, dot->y);
            setRGB0(tile, (dot->color & 0x1F) << 3, (dot->color & 0x3E0) >> 2, (dot->color & 0x7C00) >> 7);
            GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(TILE_1));
        }
        dot->active ^= 1;
    }
    if (--TASK(Actor)->timer == 0) {
        g_ScriptVars[0] = 43;
        TASK(Actor)->header.mode++;
    }
}

MATCH void func_801D369C(void) {
    Actor_Clear();
}

MATCH void func_801D36BC(s32* point, s32 orange_radius, s32 black_radius) {
    VECTOR   vertex;
    DVECTOR  inner;
    DVECTOR  outer;
    MATRIX   camera;
    POLY_G4* prim;
    u16      tpage;
    s32      turn;
    u16      angle;
    u8       i;

    tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x2C0, 0x100);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, tpage);
    Camera_SetMatrix(&camera);
    setVector(&vertex, point[0] + (orange_radius << 4), point[1], point[2]);
    Camera_ProjectPoint(&vertex.vx, &inner);
    vertex.vx = point[0] + (black_radius << 4);
    Camera_ProjectPoint(&vertex.vx, &outer);
    turn = 0;
    i    = 0;
    do {
        prim = GFX_BeginPolyG4(1);
        setXY2(prim, inner.vx, inner.vy, outer.vx, outer.vy);
        turn += 0x80;
        angle     = turn;
        vertex.vx = point[0] + ((orange_radius * rcos(angle)) >> 8);
        vertex.vy = point[1] + ((orange_radius * rsin(angle)) >> 8);
        Camera_ProjectPoint(&vertex.vx, &inner);
        vertex.vx = point[0] + ((black_radius * rcos(angle)) >> 8);
        vertex.vy = point[1] + ((black_radius * rsin(angle)) >> 8);
        Camera_ProjectPoint(&vertex.vx, &outer);
        prim->x2 = inner.vx;
        prim->y2 = inner.vy;
        prim->x3 = outer.vx;
        prim->y3 = outer.vy;
        setRGB0(prim, 0xFF, 0x7F, 0);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0xFF, 0x7F, 0);
        setRGB3(prim, 0, 0, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));
        i++;
    } while (i < 32);
}
