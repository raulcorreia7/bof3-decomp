#include "sce15ef1_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801D0C48(void) {
    Actor* work;

    work           = g_Task;
    work->unk_64   = g_Game.members[0].pos.x.fixed;
    work->unk_68   = g_Game.members[0].pos.y.fixed;
    work->unk_6C   = g_Game.members[0].pos.z.fixed + TO_COORD(128);
    work->timer    = 8;
    work->screen_x = 0;
    g_Task->header.mode += 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 11));
}

MATCH void func_801D0CC0(void) {
    u16 screen_x;
    u8  mode;

    screen_x         = g_Task->screen_x + 0x20;
    g_Task->screen_x = screen_x;
    func_801D147C(&g_Task->unk_64, (s16)screen_x, 6);
    mode          = g_Task->timer - 1;
    g_Task->timer = mode;
    if (!(mode & BYTE_MASK)) {
        g_Task->timer = 64;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D0D54(void) {
    u8 mode;

    func_801D147C(&g_Task->unk_64, (s16)g_Task->screen_x, 6);
    mode          = g_Task->timer - 1;
    g_Task->timer = mode;
    if (!(mode & BYTE_MASK)) {
        g_Task->timer = 32;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D0DD8(void) {
    WorldSpin* spin;
    u8         timer;
    u8         i;

    g_Task->unk_6C += TO_COORD(12);
    g_Task->screen_x -= 6;
    func_801D147C(&g_Task->unk_64, (s16)g_Task->screen_x, 6);
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if ((timer & BYTE_MASK) == 0) {
        g_Task->timer  = 32;
        g_Task->unk_06 = 0;
        g_Task->header.mode++;
        func_801D199C();
        g_Task->pos.x.fixed = g_Task->unk_64;
        g_Task->pos.y.fixed = g_Task->unk_68;
        g_Task->pos.z.fixed = g_Task->unk_6C;
        spin                = g_WorldSpins;
        i                   = 0;
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

INCLUDE_ASM(func_801D0F10);

MATCH void func_801D0FEC(void) {
    if ((g_Task->unk_06++ & 0x3) == 0) {
        func_801D19C8();
    }
    func_801D2088();
    func_801D1A60();
    g_Task->timer = 32;
    g_Task->header.mode += 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x09));
}

INCLUDE_ASM(func_801D106C);

MATCH void func_801D12A0(void) {
    if ((g_Task->unk_06++ & 0x3) == 0) {
        func_801D19C8();
        func_801D2138(&g_Task->pos.x.fixed, &g_Task->unk_18);
        func_801D2138(&g_Task->pos.y.fixed, &g_Task->unk_1C);
        func_801D2138(&g_Task->pos.z.fixed, &g_Task->gravity);
        func_801D19C8();
        func_801D2138(&g_Task->pos.x.fixed, &g_Task->unk_18);
        func_801D2138(&g_Task->pos.y.fixed, &g_Task->unk_1C);
        func_801D2138(&g_Task->pos.z.fixed, &g_Task->gravity);
    }
    func_801D1A60();
    func_801D2088();
    func_801D1678(&g_Task->unk_18, &g_Task->pos.x, 0x40);
    if (g_ScriptVars[0] == 0x17) {
        g_Task->unk_03 = 0x80;
        g_Task->timer  = 8;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x0A));
    }
}

MATCH void func_801D13F4(void) {
    u8 remaining;

    g_Task->screen_x -= 0x10;
    g_Task->unk_03 -= 8;
    func_801D1A60();
    func_801D1678(&g_Task->unk_18, &g_Task->pos.x, g_Task->unk_03);
    remaining     = g_Task->timer - 1;
    g_Task->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801D147C(s32* pos, s16 origin, s32 flags) {
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

INCLUDE_ASM(func_801D1678);

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
            slot->active  = 1;
            slot->unk_01  = 0;
            slot->life_02 = 16;
            actor         = g_Task;
            WorldPos_Copy(&slot->pos, &actor->pos);
            slot->radius_14     = 256;
            slot->core_shade_16 = 96;
            slot->rim_shade_17  = 0;
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
    Area_SetCameraMatrix(&matrix);
    slot = D_801D39A8;
    for (i = 0; i < EFFECT_SLOT_COUNT; slot++, i++) {
        if (slot->active != 0) {
            alive = 1;
            slot->radius_14 -= 0x10;
            if (--slot->life_02 == 0) {
                slot->active = 0;
            }
            Area_DrawSpawnSlot(slot);
        }
    }
    return alive;
}

#include "shared/Area_DrawSpawnSlot.h"

MATCH void func_801D1CD4(const void* spin) {
    WorldSpin* work;
    POLY_G3*   primitive;
    s32        point[3];
    s16        fade;
    s16        tmp;
    s16        shade;

    work      = (WorldSpin*)spin;
    primitive = (POLY_G3*)g_GfxPrimCursor;

    SetPolyG3(primitive);
    SetSemiTrans(primitive, 1);
    Area_ProjectPoint(&work->origin.x, POLY_XY(primitive, 0));

    point[0] = ((rcos(work->spin_angle) * work->vertex_a.vx - rsin(work->spin_angle) * work->vertex_a.vy) >> 8) * work->scale;
    point[1] = ((rsin(work->spin_angle) * work->vertex_a.vx + rcos(work->spin_angle) * work->vertex_a.vy) >> 8) * work->scale;
    point[2] = (work->vertex_a.vz << 12) * work->scale;
    point[0] += work->origin.x;
    point[1] += work->origin.y;
    point[2] += work->origin.z;
    Area_ProjectPoint(point, POLY_XY(primitive, 1));

    point[0] = ((rcos(work->spin_angle) * work->vertex_b.vx - rsin(work->spin_angle) * work->vertex_b.vy) >> 8) * work->scale;
    point[1] = ((rsin(work->spin_angle) * work->vertex_b.vx + rcos(work->spin_angle) * work->vertex_b.vy) >> 8) * work->scale;
    point[2] = (work->vertex_b.vz << 12) * work->scale;
    point[0] += work->origin.x;
    point[1] += work->origin.y;
    point[2] += work->origin.z;
    Area_ProjectPoint(point, POLY_XY(primitive, 2));

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

    GFX_AddPrim(2u, sizeof(POLY_G3));
}

#include "shared/Area_InitSpin.h"

MATCH void func_801D2088(void) {
    MATRIX     matrix;
    WorldSpin* spin;
    u16*       angle;
    s32        i;

    GFX_AddDitheredDrawMode(2, GetTPage(0, 1, 0x380, 0x100));
    Area_SetCameraMatrix(&matrix);
    spin  = g_WorldSpins;
    i     = 0;
    angle = &spin->spin_angle;
    do {
        func_801D1CD4(spin);
        spin += 1;
        *angle += 16;
        i += 1;
        angle += sizeof(WorldSpin) / sizeof(*angle);
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
    SpawnedActor* row;
    Actor*        actor;
    Actor*        parent;

    slot = Actor_FindFreeSpawned();
    if (slot != GAME_NONE) {
        D_801D40AC = 1;
        row        = &g_SpawnedActors[slot];
        GFX_ClearRect(0x340, 0x100, 0x80, 0x100);
        *row                = *(SpawnedActor*)g_Task->unk_4C;
        actor               = (Actor*)row;
        actor->header.flags = 1;
        actor->header.mode  = 2;
        actor->header.step  = 0;
        actor->unk_05       = 0x3A;
        actor->screen_x     = D_801D393C[D_801D40AC].x;
        actor->screen_y     = D_801D393C[D_801D40AC].y;
        if (actor->active_flags & 1) {
            actor->unk_25 = GetTPage(0, 0, 0x340, 0x100);
            actor->unk_26 = 0x80;
        }
        actor->active_flags |= 0x88;
        parent = g_Task;
        g_Task = actor;
        if (actor->active_flags & 1) {
            if (actor->unk_2C == 0) {
                Actor_BeginScript(0x4D, 0x1C);
                g_Task->unk_2A = 0;
            } else {
                Actor_BeginScript(0x50, 0x24);
            }
        }
        func_8014D290();
        func_80196070();
        g_Task        = parent;
        parent->timer = 2;
    }
    g_Task->header.mode += 1;
}

MATCH void func_801D23A0(void) {
    u8     mode;
    RECT   rect;
    Actor* actor;

    actor        = g_Task;
    mode         = actor->timer - 1;
    actor->timer = mode;
    if (!(mode & BYTE_MASK)) {
        rect.x = 832;
        rect.y = 256;
        rect.w = D_801D393C[D_801D40AC].w;
        rect.h = D_801D393C[D_801D40AC].h;
        StoreImage(&rect, (u32*)AREA_WORK);
        D_801D40B0    = AREA_WORK;
        D_801D40B4    = AREA_WORK + 0x5A00;
        D_801D40A8    = 0;
        g_Task->timer = 0;
        g_Task->header.mode++;
    }
}

INCLUDE_ASM(func_801D2474);

INCLUDE_ASM(func_801D26BC);

INCLUDE_ASM(func_801D2934);

MATCH void func_801D2B44(void) {
    Actor_Clear();
}

MATCH void func_801D2B64(void) {
    SYS_DISPATCH_TASK(D_801D396C, 1, g_Task);
}

MATCH void func_801D2BA8(void) {
    Actor* work;

    work         = g_Task;
    work->timer  = 20;
    work->vx     = 0;
    work->vy     = 0;
    work->unk_18 = 0;
    work->unk_1C = 0;
    g_Task->header.mode++;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 8));
}

MATCH void func_801D2C00(void) {
    Actor* work;
    u8     timer;

    work = g_Task;
    work->unk_18 += 0x200;
    work->unk_1C += 0x100;
    work->vx += work->unk_18;
    work->vy += work->unk_1C;
    func_801D36BC(&work->pos.x.fixed, work->vx, work->vy);
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801D2C94);

MATCH void func_801D2D5C(void) {
    Actor* work;
    Actor* work2;
    u8     timer;

    work = g_Task;
    func_801D36BC(&work->pos.x.fixed, work->vx, work->vy);
    work2        = g_Task;
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
    SpawnedActor* row;
    Actor*        actor;
    Actor*        parent;

    if (g_ScriptVars[0] == 0x29) {
        slot = Actor_FindFreeSpawned();
        if (slot != GAME_NONE) {
            D_801D40AC = 1;
            row        = &g_SpawnedActors[slot];
            GFX_ClearRect(0x340, 0x100, 0x80, 0x100);
            *row                = *(SpawnedActor*)g_Task->unk_4C;
            actor               = (Actor*)row;
            actor->header.flags = 1;
            actor->header.mode  = 2;
            actor->header.step  = 0;
            actor->unk_05       = 0x3A;
            actor->screen_x     = D_801D393C[D_801D40AC].x;
            actor->screen_y     = D_801D393C[D_801D40AC].y;
            actor->unk_25       = GetTPage(0, 0, 0x340, 0x100);
            actor->unk_26       = 0x80;
            actor->active_flags |= 0x88;
            parent = g_Task;
            g_Task = actor;
            Actor_SelectScript(7);
            func_8014D290();
            func_80196070();
            g_Task        = parent;
            parent->timer = 2;
        }
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D2FD8(void) {
    u8     mode;
    RECT   rect;
    Actor* actor;

    actor        = g_Task;
    mode         = actor->timer - 1;
    actor->timer = mode;
    if (!(mode & BYTE_MASK)) {
        rect.x = 832;
        rect.y = 256;
        rect.w = D_801D393C[D_801D40AC].w;
        rect.h = D_801D393C[D_801D40AC].h;
        StoreImage(&rect, (u32*)AREA_WORK);
        D_801D40B0    = AREA_WORK;
        D_801D40B4    = AREA_WORK + 0x5A00;
        D_801D40A8    = 0;
        g_Task->timer = 0;
        g_Task->header.mode++;
    }
}

INCLUDE_ASM(func_801D30AC);

INCLUDE_ASM(func_801D32F4);

/* Step the dot trail: move and draw each live dot, then advance when the countdown ends. */
MATCH void func_801D34F0(void) {
    SceneDot* dot;
    u16       i;
    TILE_1*   tile;

    ((Actor*)g_Task->unk_4C)->header.flags |= ACTOR_FLAG_HIDDEN;
    dot = MEM_PTR(SceneDot, AREA_WORK + 0x5A00);
    for (i = 0; i < D_801D40A8; dot++, i++) {
        if (dot->active) {
            if (dot->life != 0) {
                dot->x -= dot->dx;
                dot->y -= dot->dy;
                dot->life--;
            }
            tile = (TILE_1*)g_GfxPrimCursor;
            SetTile1(tile);
            tile->x0 = dot->x;
            tile->y0 = dot->y;
            tile->r0 = (dot->color & 0x1F) << 3;
            tile->g0 = (dot->color & 0x3E0) >> 2;
            tile->b0 = (dot->color & 0x7C00) >> 7;
            GFX_AddPrim(2, sizeof(TILE_1));
        }
        dot->active ^= 1;
    }
    if (--g_Task->timer == 0) {
        g_ScriptVars[0] = 43;
        g_Task->header.mode++;
    }
}

MATCH void func_801D369C(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801D36BC);
