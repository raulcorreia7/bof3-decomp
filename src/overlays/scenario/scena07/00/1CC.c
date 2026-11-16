#include "scena07_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801F6E10(void) {
    SYS_DISPATCH_TASK(D_801FDD3C, 2, g_Task);
}

MATCH void func_801F6E54(void) {
    void* work;

    func_801F8358();
    work                   = SP_REF(void*, 0x44);
    FIELD(s32, work, 0xCu) = 0x40;
    FIELD(u8, work, 0x2u)  = (FIELD(u8, work, 0x2u) + 1);
}

MATCH void func_801F6E90(void) {
    FallingSpark* spark;

    if ((g_Task->vx & 0x7) == 0) {
        spark = func_801F8394();
        if (spark != NULL) {
            Scene_InitSpark(spark);
        }
    }
    func_801F85D8();
    if (--g_Task->vx == 0) {
        g_Task->header.step++;
    }
}

MATCH void func_801F6F14(void) {
    if (!(func_801F85D8() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F6F48(void) {
    SYS_DISPATCH_TASK(D_801FDD48, 2, g_Task);
}

MATCH void func_801F6F8C(void) {
    void* work;

    work                    = SP_REF(void*, 0x44);
    FIELD(s32, work, 0x10u) = -8;
    FIELD(u8, work, 0x2u)   = (FIELD(u8, work, 0x2u) + 1);
}

MATCH void func_801F6FB0(void) {
    func_801F3C3C(g_Task->vy);
    g_Task->vy += (g_FrameCount & 0xF) == 0;
    if (g_Task->vy == 0) {
        Actor_Clear();
    }
}

MATCH void func_801F700C(void) {
    SYS_DISPATCH_TASK(D_801FDD50, 2, g_Task);
}

MATCH void func_801F7050(void) {
    Actor* work;
    Actor* actor;
    u8     i;

    /* FAKE: the second pointer reproduces retail's copy of the scratch pointer (move into a2). */
    work       = g_Task;
    D_800E4C1E = 0xC0;
    actor      = work;
    actor->vz  = 0;
    for (i = 0; i < 16; i++) {
        actor->vz += 8388608;
        actor->pos.x.fixed += TO_COORD(1);
        actor->pos.y.fixed += 0; /* FAKE: retail reloads and stores y with no change. */
        actor->pos.z.fixed += actor->vz;
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
    g_Task->vz = -g_Task->vz;
    g_Task->header.step++;
}

MATCH void func_801F70F8(void) {
    func_801F88B8(SCENA07_PANEL_ROWS);
    func_801F8BE8(SCENA07_PANEL_ROWS);
    g_Task->pos.x.fixed -= TO_COORD(1);
    g_Task->pos.y.fixed += 0; /* FAKE: retail reloads and stores y with no change. */
    g_Task->pos.z.fixed += g_Task->vz;
    if (g_Task->vz != 0) {
        g_Task->vz += TO_COORD(128);
    }
    if (g_Task->pos.x.fixed == g_Task->vx && g_Task->pos.y.fixed == g_Task->vy) {
        g_Task->timer = 47;
        g_Task->header.step++;
    }
}

MATCH void func_801F71C0(void) {
    func_801F88B8(SCENA07_PANEL_ROWS);
    func_801F8BE8(SCENA07_PANEL_ROWS);
    if (--g_Task->timer == 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
        g_Task->timer = 32;
        g_Task->header.step++;
    }
}

MATCH void func_801F724C(void) {
    SCENA07_PANEL_BRIGHTEN_STEP();
}

MATCH void func_801F72E0(void) {
    SCENA07_PANEL_FADE_STEP();
}

MATCH void func_801F7364(void) {
    Scene_AdvanceActorStep();
}

MATCH void func_801F7384(void) {
    Scene_AdvanceActorStep();
}

MATCH void func_801F73A4(void) {
    Actor_Clear();
}

MATCH void func_801F73C4(void) {
    SYS_DISPATCH_TASK(D_801FDD70, 2, g_Task);
}

MATCH void func_801F7408(void) {
    /* FAKE: the retail frame holds 0x10 bytes no statement explains. */
    FAKE_STACK_PADS(u8, 0x10);

    g_Task->pos.z.fixed = TO_COORD(Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed));
    func_801F9DA8();
    g_Task->timer = 0;
    g_Task->vx    = 95;
    g_Task->header.step++;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 5));
}

MATCH void func_801F7480(void) {
    u8  i;
    u8* row;

    if ((g_Task->vx & D_801FDD7C[g_Task->timer]) == 0) {
        D_801FDFBC->unk_10 += D_801FDD84[g_Task->timer];
        for (i = 0; i < D_801FDD84[g_Task->timer]; i++) {
            row = func_801F9DD4();
            if (row != NULL) {
                func_801F9E10(row);
            }
        }
    }
    if ((g_Task->vx & 0xF) == 0) {
        g_Task->timer++;
    }
    func_801F9EFC();
    if (--g_Task->vx == 0) {
        g_Task->header.step++;
    }
}

MATCH void func_801F75C0(void) {
    if (!(func_801F9EFC() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F75F4(void) {
    SYS_DISPATCH_TASK(D_801FDD8C, 2, g_Task);
}

MATCH void func_801F7638(void) {
    Scena07Burst* burst;
    s32           y;

    /* FAKE: the retail frame holds 0x10 bytes no statement explains. */
    FAKE_STACK_PADS(u8, 0x10);

    g_Task->pos.z.fixed = TO_COORD(Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed));
    burst               = SCENA07_BURST_RECORD;
    burst->x            = g_Task->pos.x.fixed;
    y                   = g_Task->pos.y.fixed;
    D_801FDFBC          = burst;
    /* FAKE: the order lock keeps the y store after the pointer store; 33 of 38 instructions otherwise. */
    FAKE_ORDER_LOCK(burst->y = y);
    burst->z      = g_Task->pos.z.fixed;
    burst->unk_10 = 0;
    g_Task->timer = 0;
    g_Task->vx    = 95;
    g_Task->header.step++;
}

MATCH void func_801F76D0(void) {
    if ((g_Task->vx & D_801FDD9C[g_Task->timer]) == 0) {
        D_801FDFBC->unk_10 += D_801FDDA4[g_Task->timer];
    }
    if ((g_Task->vx & 0xF) == 0) {
        g_Task->timer++;
    }
    func_801F97E0(D_801FDFBC);
    if (--g_Task->vx == 0) {
        g_Task->vx = 0x10;
        g_Task->header.step++;
    }
}

MATCH void func_801F77AC(void) {
    D_801FDFBC->unk_10 += 4;
    func_801F97E0(D_801FDFBC);
    if (--g_Task->vx == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F7810(void) {
    D_801FDFBC->z += 0x1000000;
    func_801F97E0(D_801FDFBC);
    if (D_801FDFBC->z > 0xFFFFFFF) {
        func_80196070();
    }
}

MATCH void func_801F786C(void) {
    SYS_DISPATCH_TASK(D_801FDDAC, 2, g_Task);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F78B0(void) {
    Scena07BurstBuffer* buffer;

    /* FAKE: the retail frame holds 0x10 bytes no statement explains. */
    FAKE_STACK_PADS(u8, 0x10);

    g_Task->pos.z.fixed = TO_COORD(Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed));
    buffer              = MEM_PTR(Scena07BurstBuffer, AREA_WORK + 0x424);
    D_801FDFC0          = buffer;
    buffer->x           = g_Task->pos.x.fixed;
    buffer->y           = g_Task->pos.y.fixed;
    buffer->angle       = 0;
    buffer->z           = g_Task->pos.z.fixed + TO_COORD(0x200);
    func_801F90F4(MEM_PTR(Scena07BurstBuffer, AREA_WORK + 0x424));
    g_Task->vx = 0x28;
    g_Task->header.step++;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x09));
}
#else
INCLUDE_ASM(func_801F78B0);
#endif

MATCH void func_801F7960(void) {
    Scene_TurnBurst(64);
}

MATCH void func_801F79EC(void) {
    SYS_DISPATCH_TASK(D_801FDDB4, 2, g_Task);
}

MATCH void func_801F7A30(void) {
    /* FAKE: retail reserves 16 bytes of frame that no statement uses. */
    FAKE_STACK_PADS(u8, 0x10);
    Actor* work;

    Scene_PlaceAtLead();
    func_801F8358();
    work         = g_Task;
    work->unk_06 = 1;
    work->vx     = 40;
    g_Task->header.step += 1;
}

MATCH void func_801F7AB0(void) {
    FallingSpark* spark;

    func_801F9330(D_801FDFC0);
    if (g_Task->vx >= 9) {
        spark = func_801F8394();
        if (((g_Task->vx & 3) == 0) && (spark != NULL)) {
            func_801F8478(spark);
        }
    }
    func_801F85D8();
    if (--g_Task->vx == 0) {
        g_Task->header.step++;
    }
}

MATCH void func_801F7B68(void) {
    if (!(func_801F85D8() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F7B9C(void) {
    SYS_DISPATCH_TASK(D_801FDDC0, 2, g_Task);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F7BE0(void) {
    Scena07BurstBuffer* buffer;

    /* FAKE: the retail frame holds 0x10 bytes no statement explains. */
    FAKE_STACK_PADS(u8, 0x10);

    g_Task->pos.x.fixed = g_Game.members[0].pos.x.fixed;
    g_Task->pos.y.fixed = g_Game.members[0].pos.y.fixed;
    g_Task->pos.z.fixed = TO_COORD(Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed));
    buffer              = MEM_PTR(Scena07BurstBuffer, AREA_WORK + 0x424);
    buffer->x           = g_Task->pos.x.fixed;
    D_801FDFC0          = buffer;
    buffer->y           = g_Task->pos.y.fixed;
    buffer->angle       = 0x800;
    buffer->z           = g_Task->pos.z.fixed + TO_COORD(0x200);
    func_801F90F4(MEM_PTR(Scena07BurstBuffer, AREA_WORK + 0x424));
    g_Task->vx = 0x28;
    g_Task->header.step++;
}
#else
INCLUDE_ASM(func_801F7BE0);
#endif

MATCH void func_801F7C9C(void) {
    Scene_TurnBurst(-64);
}

MATCH void func_801F7D28(void) {
    SYS_DISPATCH_TASK(D_801FDDC8, 2, g_Task);
}

MATCH void func_801F7D6C(void) {
    /* FAKE: retail reserves 16 bytes of frame that no statement uses. */
    FAKE_STACK_PADS(u8, 0x10);

    Scene_PlaceAtLead();
    func_801FA01C();
    g_Task->vx = 120;
    g_Task->header.step += 1;
}

MATCH void func_801F7DDC(void) {
    func_801FA38C();
    g_Task->vx = g_Task->vx - 1;
    if (g_Task->vx == 0) {
        Actor_Clear();
    }
}

MATCH void func_801F7E24(void) {
    SYS_DISPATCH_TASK(D_801FDDD0, 2, g_Task);
}

MATCH void func_801F7E68(void) {
    u8 i;

    D_800E4C1E = 0xC0;
    for (i = 0; i < 32; i++) {
        func_801F88B8(SCENA07_PANEL_ROWS);
    }
    if (g_Task->unk_06 != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
    }
    g_Task->header.step++;
}

MATCH void func_801F7EF8(void) {
    func_801F88B8(SCENA07_PANEL_ROWS);
    func_801F8BE8(SCENA07_PANEL_ROWS);
    g_Task->pos.x.fixed += g_Task->vx;
    g_Task->pos.y.fixed += g_Task->vy;
    g_Task->pos.z.fixed += g_Task->vz;
    if (g_Task->pos.x.fixed == g_Task->unk_18 && g_Task->pos.y.fixed == g_Task->unk_1C) {
        g_Task->timer = 47;
        g_Task->header.step++;
    }
}

MATCH void func_801F7FA4(void) {
    func_801F88B8(SCENA07_PANEL_ROWS);
    func_801F8BE8(SCENA07_PANEL_ROWS);
    if (--g_Task->timer == 0) {
        if (g_Task->unk_06 == 0) {
            Actor_Clear();
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 4));
            g_Task->timer = 32;
            g_Task->header.step++;
        }
    }
}

MATCH void func_801F805C(void) {
    SCENA07_PANEL_BRIGHTEN_STEP();
}

MATCH void func_801F80F0(void) {
    SCENA07_PANEL_FADE_STEP();
}

MATCH void func_801F8174(void) {
    Scene_AdvanceActorStep();
}

MATCH void func_801F8194(void) {
    Scene_AdvanceActorStep();
}

MATCH void func_801F81B4(void) {
    Actor_Clear();
}

#include "shared/GFX_DrawProjectedDisc.h"

MATCH void func_801F81D4(FallingSpark* spark) {
    GFX_DRAW_PROJECTED_DISC(&spark->x, spark->fade, 0x20, 1);
}

MATCH void func_801F8358(void) {
    FallingSpark* spark;
    u8            i;

    spark = MEM_PTR(FallingSpark, AREA_WORK);
    i     = 0;
    do {
        spark->active = 0;
        i++;
        spark++;
    } while (i < 8);
    D_801FDFC4 = 0;
    D_801FDFC8 = 0;
}

MATCH FallingSpark* func_801F8394(void) {
    FallingSpark* spark;
    u8            i;

    spark = MEM_PTR(FallingSpark, AREA_WORK);
    for (i = 0; i < 8; i++) {
        if (spark->active == 0) {
            return spark;
        }
        spark++;
    }
    return NULL;
}

#include "overlays/scenario/Scene_InitSpark.h"

/* Starts a spark row at a random point of a sphere around the actor, raised 512 units. */
MATCH void func_801F8478(FallingSpark* spark) {
    u16 yaw;
    u16 pitch;
    s16 radius;

    spark->active      = 1;
    spark->kind        = 0;
    spark->life        = 8;
    spark->fade        = 0;
    spark->speed       = 0;
    spark->life_reload = 1;
    yaw                = rand() & 0x7FF;
    pitch              = rand() & 0xFFF;
    radius             = ((rand() % 2) << 12) | (rand() & 0xFFF);
    spark->x           = g_Task->pos.x.fixed + ((radius * ((rsin(yaw) * rcos(pitch)) >> 12)) >> 8);
    spark->y           = g_Task->pos.y.fixed + ((radius * ((rsin(yaw) * rsin(pitch)) >> 12)) >> 8);
    spark->z           = g_Task->pos.z.fixed + radius * rcos(yaw) + TO_COORD(512);
}

MATCH u8 func_801F85D8(void) {
    u8            active;
    FallingSpark* spark;
    s32           i;
    MATRIX        matrix;

    active = 0;
    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, FONT_TPAGE_X, FONT_TPAGE_Y));
    Area_SetCameraMatrix(&matrix);
    spark = MEM_PTR(FallingSpark, AREA_WORK);
    i     = 0;
    do {
        if (spark->active != 0) {
            D_801FDDF0[spark->kind](spark);
            active = 1;
            func_801F81D4(spark);
        }
        i++;
        spark++;
    } while ((u32)(i & BYTE_MASK) < 8);
    return active;
}

MATCH void func_801F86BC(FallingSpark* spark) {
    u8 next;

    spark->fade += 6;
    if (--spark->life == 0) {
        next        = spark->kind + 1;
        spark->life = spark->life_reload;
        spark->kind = next;
        if (D_801FDFC4 == 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
            D_801FDFC4 = 1;
        }
    }
}

#include "overlays/scenario/Actor_Wait.h"

MATCH void func_801F8764(FallingSpark* spark) {
    u8  life;
    s32 speed;

    if (D_801FDFC8 == 0) {
        if (g_Task->unk_06 == 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 1));
        }
        D_801FDFC8 = 1;
    }
    life         = spark->life - 1;
    spark->life  = life;
    speed        = spark->speed + TO_COORD(4);
    spark->speed = speed;
    spark->z += speed;
    spark->fade += 6;
    if (life == 0) {
        spark->active = 0;
    }
}

MATCH void func_801F8804(u8 shade) {
    TILE* tile;

    GFX_AddDitheredDrawMode(1, GetTPage(0, 2, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    setXY0(tile, 0, 0);
    setWH(tile, 320, 240);
    setRGB0(tile, shade, shade, shade);
    GFX_AddPrim(1, sizeof(TILE));
}

INCLUDE_ASM(func_801F88B8);

INCLUDE_ASM(func_801F8BE8);

#include "shared/MATH_AverageAngle.h"

#include "shared/GFX_DrawFan.h"

MATCH void func_801F90F4(Scena07BurstBuffer* buffer) {
    s32    dir[3];
    s32    pos[3];
    MATRIX camera;
    u16    phase;
    s8     i;
    s8     row;
    s32    light;

    Area_SetCameraMatrix(&camera);
    buffer->unk_514 = 0;
    buffer->unk_518 = 0x1000;
    buffer->unk_51C = 0x1000;
    VectorNormal(&buffer->unk_514, &buffer->unk_514);
    phase = 0;
    for (i = 0; i < 32; i++) {
        dir[0] = (rsin(buffer->angle) * rcos(phase)) >> 12;
        dir[1] = (rsin(buffer->angle) * rsin(phase)) >> 12;
        dir[2] = rcos(buffer->angle);
        light  = buffer->unk_514 * dir[0] + buffer->unk_518 * dir[1] + buffer->unk_51C * dir[2];
        if (light <= 0) {
            buffer->shade[0][i] = 0x70;
        } else {
            light = SquareRoot0(light);
            if (light >= 0x1000) {
                light = 0xFFF;
            }
            buffer->shade[0][i] = ((light & 0xF00) >> 5) + 7;
        }
        pos[0] = buffer->x + (dir[0] << 5);
        pos[1] = buffer->y + (dir[1] << 5);
        pos[2] = buffer->z + (dir[2] << 13);
        Area_ProjectPoint(pos, &buffer->points[0][i]);
        for (row = 1; row < 8; row++) {
            buffer->points[row][i] = buffer->points[0][i];
            buffer->shade[row][i]  = buffer->shade[0][i];
        }
        phase += 0x80;
    }
}

INCLUDE_ASM(func_801F9330);

INCLUDE_ASM(func_801F97E0);

MATCH s32 func_801F9A80(SceneEffectRow* row) {
    POLY_F4* poly;
    s32      point[3];
    DVECTOR  screen;
    s32      landed;

    poly = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(poly);
    SetSemiTrans(poly, 1);
    point[0] = row->x;
    point[1] = row->y;
    point[2] = row->unk_C + (row->unk_14 << 8);
    Area_ProjectPoint(point, &screen);
    poly->x0 = screen.vx - 1;
    poly->y0 = screen.vy;
    poly->x1 = screen.vx + 1;
    poly->y1 = screen.vy;
    point[0] = row->x;
    point[1] = row->y;
    point[2] = row->unk_C - (row->unk_14 << 8);
    landed   = 0;
    if (point[2] < row->unk_1C) {
        point[2] = row->unk_1C;
        landed   = 1;
    }
    Area_ProjectPoint(point, &screen);
    poly->x2 = screen.vx - 1;
    poly->y2 = screen.vy;
    poly->x3 = screen.vx + 1;
    poly->y3 = screen.vy;
    setRGB0(poly, 0x40, 0x40, 0x40);
    GFX_AddPrim(1, sizeof(POLY_F4));
    return landed;
}

/* Draw a ring of 16 translucent triangles around the row, on the ground below it. */
MATCH void func_801F9BDC(SceneEffectRow* row) {
    DVECTOR  center;
    DVECTOR  edge;
    s32      pos[3];
    POLY_G3* prim;
    u8       i;
    u16      angle;

    pos[0] = row->x;
    pos[1] = row->y;
    pos[2] = Area_SampleHeight(row->x, row->y) << 16;
    Area_ProjectPoint(pos, &center);
    angle  = 0;
    i      = 0;
    pos[0] = row->x + (rcos(0) << 2);
    pos[1] = row->y + (rsin(0) << 2);
    pos[2] = Area_SampleHeight(row->x, row->y) << 16;
    Area_ProjectPoint(pos, &edge);
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = center.vx;
        prim->y0 = center.vy;
        angle += 256;
        prim->x1 = edge.vx;
        prim->y1 = edge.vy;
        pos[0]   = row->x + (rcos(angle) << 2);
        pos[1]   = row->y + (rsin(angle) << 2);
        i++;
        pos[2] = Area_SampleHeight(row->x, row->y) << 16;
        Area_ProjectPoint(pos, &edge);
        prim->x2 = edge.vx;
        prim->y2 = edge.vy;
        setRGB0(prim, 64, 64, 64);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        GFX_AddPrim(1, sizeof(POLY_G3));
    } while (i < 16);
}

MATCH void func_801F9DA8(void) {
    s32 index;
    s8* row;

    row   = (s8*)(AREA_WORK + 0x95C);
    index = 0;
    do {
        *row = 0;
        index += 1;
        row += 32;
    } while ((index & BYTE_MASK) < 0x40U);
}

MATCH u8* func_801F9DD4(void) {
    u8* row;
    u8  i;

    row = MEM_PTR(u8, AREA_WORK + 0x95C);
    for (i = 0; i < 64; i++) {
        if (row[0] == 0) {
            return row;
        }
        row += 32;
    }
    return NULL;
}

/* Starts a burst row at a random distance and angle around the actor, on the ground. */
MATCH void func_801F9E10(u8* row) {
    s32  radius;
    u32  angle;
    s32* cell;
    /* FAKE: the retail frame holds 16 bytes no statement explains. */
    FAKE_STACK_PADS(u8, 16);

    cell    = (s32*)row;
    row[0]  = 1;
    row[1]  = 0;
    row[2]  = 16;
    cell[6] = 0;
    cell[5] = 0;
    radius  = ((rand() % 2) << 16) | ((rand() & BYTE_MASK) << 8);
    angle   = rand() & 0xFC0;
    cell[1] = g_Task->pos.x.fixed + ((radius * rcos(angle)) >> 12);
    cell[2] = g_Task->pos.y.fixed + ((radius * rsin(angle)) >> 12);
    cell[7] = Area_SampleHeight(cell[1], cell[2]) << 16;
    cell[3] = cell[7];
}

INCLUDE_ASM(func_801F9EFC);

#ifdef NON_MATCHING
NON_MATCHING void func_801FA01C(void) {
    s16* vertex;
    s16* depth;
    u16* quad;
    u16* tail;
    u16* edge;
    s32  row;
    s32  below;
    u8*  shade;
    u16  ring;
    u16  col;
    u16  phase;
    s32  angle;
    s32  next;
    s32  dot;
    s32  root;

    D_800E595C = 0;
    D_800E595E = 0;
    D_800E5960 = 0x1000;
    vertex     = MEM_PTR(s16, AREA_WORK + 0x1164);
    angle      = 0;
    for (ring = 0; ring < 15; ring++) {
        angle += 0x80;
        depth = vertex + 2;
        for (col = 0, phase = 0; col < 32; col++, phase += 0x80) {
            vertex[0] = (rsin((u16)angle) * rcos(phase)) >> 12;
            depth[-1] = (rsin((u16)angle) * rsin(phase)) >> 12;
            depth[0]  = rcos((u16)angle);
            vertex += 4;
            depth += 4;
        }
    }
    angle -= 0x80;
    vertex[0] = 0;
    vertex[1] = 0;
    vertex[2] = -0x1000;

    quad = MEM_PTR(u16, AREA_WORK + 0x27F4);
    tail = MEM_PTR(u16, AREA_WORK + 0x27FA);
    for (col = 0; col < 32;) {
        next = col + 1;
        if ((u16)col + 1 >= 32) {
            next = 0;
        }
        tail[-2] = 0;
        quad[0]  = 0;
        tail[-1] = col + 1;
        tail[0]  = next + 1;
        tail += 4;
        col = col + 1;
        quad += 4;
    }
    for (ring = 0, col = 0; ring < 14; ring++) {
        row   = ring * 32;
        below = (ring + 1) * 32;
        edge  = quad + 3;
        for (; col < 32; col++) {
            next = col + 1;
            if ((u16)col + 1 >= 32) {
                next = 0;
            }
            quad[0]  = col + row + 1;
            edge[-2] = next + row + 1;
            edge[-1] = col + below + 1;
            edge[0]  = next + below + 1;
            edge += 4;
            quad += 4;
        }
        col = 0;
    }
    row  = ring * 32;
    edge = quad + 2;
    for (col = 0; col < 32; col++) {
        next = col + 1;
        if ((u16)col + 1 >= 32) {
            next = 0;
        }
        quad[0]  = col + row + 1;
        edge[-1] = next + row + 1;
        edge[0]  = 0x1E1;
        edge[1]  = 0x1E1;
        edge += 4;
        quad += 4;
    }

    D_800E81D8 = 0;
    D_800E81DC = 0x1000;
    D_800E81E0 = 0x1000;
    VectorNormal(MEM_PTR(s32, AREA_WORK + 0x39D8), MEM_PTR(s32, AREA_WORK + 0x39D8));
    shade  = MEM_PTR(u8, AREA_WORK + 0x37F4);
    vertex = MEM_PTR(s16, AREA_WORK + 0x115C);
    depth  = MEM_PTR(s16, AREA_WORK + 0x1160);
    for (col = 0; col < 482; col++) {
        dot = D_800E81D8 * vertex[0] + D_800E81DC * depth[-1] + D_800E81E0 * depth[0];
        if (dot <= 0) {
            *shade = 0;
        } else {
            root = SquareRoot0(dot);
            if (root >= 0x1000) {
                root = 0xFFF;
            }
            *shade = root >> 7;
        }
        depth += 4;
        vertex += 4;
        shade++;
    }
}
#else
INCLUDE_ASM(func_801FA01C);
#endif

MATCH void func_801FA38C(void) {
    s32      pos[3];
    MATRIX   camera;
    u16      i;
    u8       tone;
    POLY_G4* poly;
    u8*      shade;
    u16*     quad;
    DVECTOR* screen;
    s16*     vertex;
    s16*     depth;

    Area_SetCameraMatrix(&camera);
    screen = MEM_PTR(DVECTOR, AREA_WORK + 0x206C);
    vertex = MEM_PTR(s16, AREA_WORK + 0x115C);
    for (i = 0, depth = MEM_PTR(s16, AREA_WORK + 0x1160); i < 482; i++) {
        pos[0] = g_Task->pos.x.fixed + (vertex[0] << 5);
        pos[1] = g_Task->pos.y.fixed + (depth[-1] << 5);
        pos[2] = g_Task->pos.z.fixed + (depth[0] << 13) + TO_COORD(0x200);
        Area_ProjectPoint(pos, screen);
        vertex += 4;
        depth += 4;
        screen++;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 960, 0), 0);
    GFX_AddPrim(1, sizeof(DR_MODE));
    quad   = MEM_PTR(u16, AREA_WORK + 0x27F4);
    shade  = MEM_PTR(u8, AREA_WORK + 0x37F4);
    screen = MEM_PTR(DVECTOR, AREA_WORK + 0x206C);
    for (i = 0; i < 512; i++) {
        poly = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        poly->x0 = screen[quad[0]].vx;
        poly->y0 = screen[quad[0]].vy;
        poly->x1 = screen[quad[1]].vx;
        poly->y1 = screen[quad[1]].vy;
        poly->x2 = screen[quad[2]].vx;
        poly->y2 = screen[quad[2]].vy;
        poly->x3 = screen[quad[3]].vx;
        poly->y3 = screen[quad[3]].vy;
        tone     = shade[quad[0]];
        poly->r0 = poly->g0 = poly->b0 = tone;
        tone                           = shade[quad[1]];
        poly->r1 = poly->g1 = poly->b1 = tone;
        tone                           = shade[quad[2]];
        poly->r2 = poly->g2 = poly->b2 = tone;
        tone                           = shade[quad[3]];
        poly->r3 = poly->g3 = poly->b3 = tone;
        quad += 4;
        GFX_AddPrim(1, sizeof(POLY_G4));
    }
}

MATCH void func_801FA65C(void) {
    SYS_DISPATCH_BYTE(D_801FDE10, D_80146872);
}

MATCH void func_801FA698(void) {
    D_80144EC0 = 0;
    D_80146872 = 1;
}

INCLUDE_ASM(func_801FA6B4);

MATCH void func_801FAA2C(void) {
    SYS_DISPATCH_BYTE(D_801FDE1C, g_SceneState.state_04);
}

MATCH void func_801FAA68(void) {
}

MATCH void func_801FAA70(void) {
    u8* step = &g_SceneState.step_05;

    switch (*step) {
        case 0:
            if (g_UiWindowEffectBusy == 0) {
                Message_StartAreaMessage(1);
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
                *step            = 1;
            }
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                UI_SetMode(1);
                g_AreaScrollTargetX = 0x2D8000;
                g_AreaScrollTargetY = 0x5D0000;
                func_80153DE8();
                g_AreaDrawFlags = 0x1F;
                *step           = 2;
            }
            break;
        case 2:
            if (g_UiWindowEffectBusy == 0) {
                *g_ScriptVars = 1;
                *step         = 3;
            }
            break;
        case 3:
            if (*g_ScriptVars == 0x15) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0);
                *g_ScriptVars         = 0;
                g_SceneState.state_04 = 0;
                *step                 = 0;
            }
            break;
    }
}

INCLUDE_ASM(func_801FABD8);
