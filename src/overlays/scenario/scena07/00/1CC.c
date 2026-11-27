#include "scena07_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F6E10(void) {
    SYS_DISPATCH_TASK(D_801FDD3C, 2, g_Self);
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

    if ((SELF(Actor)->vx & 0x7) == 0) {
        spark = func_801F8394();
        if (spark != NULL) {
            Scene_InitSpark(spark);
        }
    }
    func_801F85D8();
    if (--SELF(Actor)->vx == 0) {
        SELF(Actor)->header.step++;
    }
}

MATCH void func_801F6F14(void) {
    if (!(func_801F85D8() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F6F48(void) {
    SYS_DISPATCH_TASK(D_801FDD48, 2, g_Self);
}

MATCH void func_801F6F8C(void) {
    void* work;

    work                    = SP_REF(void*, 0x44);
    FIELD(s32, work, 0x10u) = -8;
    FIELD(u8, work, 0x2u)   = (FIELD(u8, work, 0x2u) + 1);
}

MATCH void func_801F6FB0(void) {
    func_801F3C3C(SELF(Actor)->vy);
    SELF(Actor)->vy += (g_FrameCount & 0xF) == 0;
    if (SELF(Actor)->vy == 0) {
        Actor_Clear();
    }
}

MATCH void func_801F700C(void) {
    SYS_DISPATCH_TASK(D_801FDD50, 2, g_Self);
}

MATCH void func_801F7050(void) {
    Actor* work;
    Actor* actor;
    u8     i;

    /* FAKE: the second pointer reproduces retail's copy of the scratch pointer (move into a2). */
    work       = SELF(Actor);
    D_800E4C1E = 0xC0;
    actor      = work;
    actor->vz  = 0;
    for (i = 0; i < 16; i++) {
        actor->vz += 8388608;
        actor->pos.x.fixed += TO_COORD(1);
        actor->pos.y.fixed += 0; /* FAKE: retail reloads and stores y with no change. */
        actor->pos.z.fixed += actor->vz;
    }
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
    SELF(Actor)->vz = -SELF(Actor)->vz;
    SELF(Actor)->header.step++;
}

MATCH void func_801F70F8(void) {
    Trail_Update(SCENA07_TRAIL);
    Trail_Draw(SCENA07_TRAIL);
    SELF(Actor)->pos.x.fixed -= TO_COORD(1);
    SELF(Actor)->pos.y.fixed += 0; /* FAKE: retail reloads and stores y with no change. */
    SELF(Actor)->pos.z.fixed += SELF(Actor)->vz;
    if (SELF(Actor)->vz != 0) {
        SELF(Actor)->vz += TO_COORD(128);
    }
    if (SELF(Actor)->pos.x.fixed == SELF(Actor)->vx && SELF(Actor)->pos.y.fixed == SELF(Actor)->vy) {
        SELF(Actor)->timer = 47;
        SELF(Actor)->header.step++;
    }
}

MATCH void func_801F71C0(void) {
    Trail_Update(SCENA07_TRAIL);
    Trail_Draw(SCENA07_TRAIL);
    if (--SELF(Actor)->timer == 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
        SELF(Actor)->timer = 32;
        SELF(Actor)->header.step++;
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
    SYS_DISPATCH_TASK(D_801FDD70, 2, g_Self);
}

MATCH void func_801F7408(void) {
    {
        Coord sample_x = {SELF(Actor)->pos.x.fixed};
        Coord sample_y = {SELF(Actor)->pos.y.fixed};

        SELF(Actor)->pos.z.fixed = TO_COORD(Area_HeightSample(sample_x.fixed, sample_y.fixed));
    }
    func_801F9DA8();
    SELF(Actor)->timer = 0;
    SELF(Actor)->vx    = 95;
    SELF(Actor)->header.step++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 5));
}

MATCH void func_801F7480(void) {
    u8  i;
    u8* effect;

    if ((SELF(Actor)->vx & D_801FDD7C[SELF(Actor)->timer]) == 0) {
        D_801FDFBC->unk_10 += D_801FDD84[SELF(Actor)->timer];
        for (i = 0; i < D_801FDD84[SELF(Actor)->timer]; i++) {
            effect = func_801F9DD4();
            if (effect != NULL) {
                func_801F9E10(effect);
            }
        }
    }
    if ((SELF(Actor)->vx & 0xF) == 0) {
        SELF(Actor)->timer++;
    }
    func_801F9EFC();
    if (--SELF(Actor)->vx == 0) {
        SELF(Actor)->header.step++;
    }
}

MATCH void func_801F75C0(void) {
    if (!(func_801F9EFC() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F75F4(void) {
    SYS_DISPATCH_TASK(D_801FDD8C, 2, g_Self);
}

MATCH void func_801F7638(void) {
    Scena07Burst* burst;

    {
        Coord sample_x = {SELF(Actor)->pos.x.fixed};
        Coord sample_y = {SELF(Actor)->pos.y.fixed};

        SELF(Actor)->pos.z.fixed = TO_COORD(Area_HeightSample(sample_x.fixed, sample_y.fixed));
    }
    burst              = SCENA07_BURST_RECORD;
    burst->pos.vx      = SELF(Actor)->pos.x.fixed;
    D_801FDFBC         = burst;
    burst->pos.vy      = SELF(Actor)->pos.y.fixed;
    burst->pos.vz      = SELF(Actor)->pos.z.fixed;
    burst->unk_10      = 0;
    SELF(Actor)->timer = 0;
    SELF(Actor)->vx    = 95;
    SELF(Actor)->header.step++;
}

MATCH void func_801F76D0(void) {
    if ((SELF(Actor)->vx & D_801FDD9C[SELF(Actor)->timer]) == 0) {
        D_801FDFBC->unk_10 += D_801FDDA4[SELF(Actor)->timer];
    }
    if ((SELF(Actor)->vx & 0xF) == 0) {
        SELF(Actor)->timer++;
    }
    func_801F97E0(D_801FDFBC);
    if (--SELF(Actor)->vx == 0) {
        SELF(Actor)->vx = 0x10;
        SELF(Actor)->header.step++;
    }
}

MATCH void func_801F77AC(void) {
    D_801FDFBC->unk_10 += 4;
    func_801F97E0(D_801FDFBC);
    if (--SELF(Actor)->vx == 0) {
        SELF(Actor)->header.step += 1;
    }
}

MATCH void func_801F7810(void) {
    D_801FDFBC->pos.vz += 0x1000000;
    func_801F97E0(D_801FDFBC);
    if (D_801FDFBC->pos.vz > 0xFFFFFFF) {
        func_80196070();
    }
}

MATCH void func_801F786C(void) {
    SYS_DISPATCH_TASK(D_801FDDAC, 2, g_Self);
}

MATCH void func_801F78B0(void) {
    Scena07BurstBuffer* buffer;
    Coord               x = {SELF(Actor)->pos.x.fixed};
    Coord               y = {SELF(Actor)->pos.y.fixed};

    SELF(Actor)->pos.z.fixed = Area_HeightSample(x.fixed, y.fixed) << 16;
    buffer                   = MEM_PTR(Scena07BurstBuffer, AREA_WORK + 0x424);
    D_801FDFC0               = buffer;
    buffer->pos.vx           = SELF(Actor)->pos.x.fixed;
    buffer->pos.vy           = SELF(Actor)->pos.y.fixed;
    buffer->pos.vz           = SELF(Actor)->pos.z.fixed + TO_COORD(0x200);
    buffer->angle            = 0;
    func_801F90F4(MEM_PTR(Scena07BurstBuffer, AREA_WORK + 0x424));
    SELF(Actor)->vx = 0x28;
    SELF(Actor)->header.step++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 9));
}

MATCH void func_801F7960(void) {
    Scene_TurnBurst(64);
}

MATCH void func_801F79EC(void) {
    SYS_DISPATCH_TASK(D_801FDDB4, 2, g_Self);
}

MATCH void func_801F7A30(void) {
    Actor* work;

    Scene_PlaceAtLead();
    func_801F8358();
    work         = SELF(Actor);
    work->unk_06 = 1;
    work->vx     = 40;
    SELF(Actor)->header.step += 1;
}

MATCH void func_801F7AB0(void) {
    FallingSpark* spark;

    func_801F9330(D_801FDFC0);
    if (SELF(Actor)->vx >= 9) {
        spark = func_801F8394();
        if (((SELF(Actor)->vx & 3) == 0) && (spark != NULL)) {
            func_801F8478(spark);
        }
    }
    func_801F85D8();
    if (--SELF(Actor)->vx == 0) {
        SELF(Actor)->header.step++;
    }
}

MATCH void func_801F7B68(void) {
    if (!(func_801F85D8() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F7B9C(void) {
    SYS_DISPATCH_TASK(D_801FDDC0, 2, g_Self);
}

MATCH void func_801F7BE0(void) {
    Scena07BurstBuffer* buffer;

    SELF(Actor)->pos.x.fixed = g_Game.members[0].pos.x.fixed;
    SELF(Actor)->pos.y.fixed = g_Game.members[0].pos.y.fixed;
    {
        Coord x = {SELF(Actor)->pos.x.fixed};
        Coord y = {SELF(Actor)->pos.y.fixed};

        SELF(Actor)->pos.z.fixed = TO_COORD(Area_HeightSample(x.fixed, y.fixed));
    }
    buffer         = MEM_PTR(Scena07BurstBuffer, AREA_WORK + 0x424);
    buffer->pos.vx = SELF(Actor)->pos.x.fixed;
    D_801FDFC0     = buffer;
    buffer->pos.vy = SELF(Actor)->pos.y.fixed;
    buffer->pos.vz = SELF(Actor)->pos.z.fixed + TO_COORD(0x200);
    buffer->angle  = 0x800;
    func_801F90F4(MEM_PTR(Scena07BurstBuffer, AREA_WORK + 0x424));
    SELF(Actor)->vx = 0x28;
    SELF(Actor)->header.step++;
}

MATCH void func_801F7C9C(void) {
    Scene_TurnBurst(-64);
}

MATCH void func_801F7D28(void) {
    SYS_DISPATCH_TASK(D_801FDDC8, 2, g_Self);
}

MATCH void func_801F7D6C(void) {
    Scene_PlaceAtLead();
    func_801FA01C();
    SELF(Actor)->vx = 120;
    SELF(Actor)->header.step += 1;
}

MATCH void func_801F7DDC(void) {
    func_801FA38C();
    SELF(Actor)->vx = SELF(Actor)->vx - 1;
    if (SELF(Actor)->vx == 0) {
        Actor_Clear();
    }
}

MATCH void func_801F7E24(void) {
    SYS_DISPATCH_TASK(D_801FDDD0, 2, g_Self);
}

MATCH void func_801F7E68(void) {
    u8 i;

    D_800E4C1E = 0xC0;
    for (i = 0; i < 32; i++) {
        Trail_Update(SCENA07_TRAIL);
    }
    if (SELF(Actor)->unk_06 != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
    }
    SELF(Actor)->header.step++;
}

MATCH void func_801F7EF8(void) {
    Trail_Update(SCENA07_TRAIL);
    Trail_Draw(SCENA07_TRAIL);
    SELF(Actor)->pos.x.fixed += SELF(Actor)->vx;
    SELF(Actor)->pos.y.fixed += SELF(Actor)->vy;
    SELF(Actor)->pos.z.fixed += SELF(Actor)->vz;
    if (SELF(Actor)->pos.x.fixed == SELF(Actor)->unk_18 && SELF(Actor)->pos.y.fixed == SELF(Actor)->unk_1C) {
        SELF(Actor)->timer = 47;
        SELF(Actor)->header.step++;
    }
}

MATCH void func_801F7FA4(void) {
    Trail_Update(SCENA07_TRAIL);
    Trail_Draw(SCENA07_TRAIL);
    if (--SELF(Actor)->timer == 0) {
        if (SELF(Actor)->unk_06 == 0) {
            Actor_Clear();
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
            SELF(Actor)->timer = 32;
            SELF(Actor)->header.step++;
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
    GFX_DRAW_PROJECTED_DISC(&spark->pos.vx, spark->header.shade, 0x20, 1);
}

MATCH void func_801F8358(void) {
    FallingSpark* spark;
    u8            i;

    spark = MEM_PTR(FallingSpark, AREA_WORK);
    i     = 0;
    do {
        spark->header.active = 0;
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
        if (spark->header.active == 0) {
            return spark;
        }
        spark++;
    }
    return NULL;
}

#include "overlays/scenario/shared/Scene_InitSpark.h"

/* Starts a spark row at a random point of a sphere around the actor, raised 512 units. */
MATCH void func_801F8478(FallingSpark* spark) {
    u16 yaw;
    u16 pitch;
    s16 radius;

    spark->header.active = 1;
    spark->header.type   = 0;
    spark->header.life   = 8;
    spark->header.shade  = 0;
    spark->speed         = 0;
    spark->life_reload   = 1;
    yaw                  = rand() & 0x7FF;
    pitch                = rand() & 0xFFF;
    radius               = ((rand() % 2) << 12) | (rand() & 0xFFF);
    spark->pos.vx        = SELF(Actor)->pos.x.fixed + ((radius * ((rsin(yaw) * rcos(pitch)) >> 12)) >> 8);
    spark->pos.vy        = SELF(Actor)->pos.y.fixed + ((radius * ((rsin(yaw) * rsin(pitch)) >> 12)) >> 8);
    spark->pos.vz        = SELF(Actor)->pos.z.fixed + radius * rcos(yaw) + TO_COORD(512);
}

MATCH u8 func_801F85D8(void) {
    u8            active;
    FallingSpark* spark;
    s32           i;
    MATRIX        matrix;

    active = 0;
    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Camera_SetMatrix(&matrix);
    spark = MEM_PTR(FallingSpark, AREA_WORK);
    i     = 0;
    do {
        if (spark->header.active != 0) {
            D_801FDDF0[spark->header.type](spark);
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

    spark->header.shade += 6;
    if (--spark->header.life == 0) {
        next               = spark->header.type + 1;
        spark->header.life = spark->life_reload;
        spark->header.type = next;
        if (D_801FDFC4 == 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
            D_801FDFC4 = 1;
        }
    }
}

#include "overlays/scenario/shared/Actor_Wait.h"

MATCH void func_801F8764(FallingSpark* spark) {
    u8  life;
    s32 speed;

    if (D_801FDFC8 == 0) {
        if (SELF(Actor)->unk_06 == 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
        }
        D_801FDFC8 = 1;
    }
    life               = spark->header.life - 1;
    spark->header.life = life;
    speed              = spark->speed + TO_COORD(4);
    spark->speed       = speed;
    spark->pos.vz += speed;
    spark->header.shade += 6;
    if (life == 0) {
        spark->header.active = 0;
    }
}

MATCH void func_801F8804(u8 shade) {
    TILE* tile;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    setXY0(tile, 0, 0);
    setWH(tile, SCREEN_WIDTH, SCREEN_HEIGHT);
    setRGB0(tile, shade, shade, shade);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));
}

#include "shared/Trail_Update.h"

#include "shared/Trail_Draw.h"

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

    Camera_SetMatrix(&camera);
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
        pos[0] = buffer->pos.vx + (dir[0] << 5);
        pos[1] = buffer->pos.vy + (dir[1] << 5);
        pos[2] = buffer->pos.vz + (dir[2] << 13);
        Camera_ProjectPoint(pos, &buffer->points[0][i]);
        for (row = 1; row < 8; row++) {
            buffer->points[row][i] = buffer->points[0][i];
            buffer->shade[row][i]  = buffer->shade[0][i];
        }
        phase += 0x80;
    }
}

/* Shifts the burst rings back one row, relights and reprojects the front ring, and draws the rings as a mesh that fades by row. */
MATCH void func_801F9330(Scena07BurstBuffer* buffer) {
    s32      dir[3];
    s32      pos[3];
    MATRIX   camera;
    u16      phase;
    POLY_G4* prim;
    s8       i;
    s8       row;
    s32      light;
    u8       shade;
    s8       next;

    for (row = 6; row >= 0; row--) {
        for (i = 0; i < 32; i++) {
            buffer->points[row + 1][i] = buffer->points[row][i];
        }
    }

    Camera_SetMatrix(&camera);
    phase = 0;
    for (row = 0; row < 32; row++) {
        dir[0] = (rsin(buffer->angle) * rcos(phase)) >> 12;
        dir[1] = (rsin(buffer->angle) * rsin(phase)) >> 12;
        dir[2] = rcos(buffer->angle);
        light  = buffer->unk_514 * dir[0] + buffer->unk_518 * dir[1] + buffer->unk_51C * dir[2];
        if (light <= 0) {
            buffer->shade[0][row] = 7;
        } else {
            light = SquareRoot0(light);
            if (light >= 0x1000) {
                light = 0xFFF;
            }
            buffer->shade[0][row] = ((light & 0xF00) >> 5) + 7;
        }
        pos[0] = buffer->pos.vx + (dir[0] << 5);
        pos[1] = buffer->pos.vy + (dir[1] << 5);
        pos[2] = buffer->pos.vz + (dir[2] << 13);
        Camera_ProjectPoint(pos, &buffer->points[0][row]);
        phase += 0x80;
    }

    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));

    for (row = 0; row < 7; row++) {
        for (i = 0; i < 32; i++) {
            next = (i + 1) & 0x1F;
            prim = GFX_BeginPolyG4(1);
            setXY0(prim, buffer->points[row][i].vx, buffer->points[row][i].vy);
            prim->x1 = buffer->points[row][next].vx;
            prim->y1 = buffer->points[row][next].vy;
            shade    = (buffer->shade[row][i] * (7 - row)) / 7;
            setRGB0(prim, shade, shade, shade);
            shade = (buffer->shade[row][next] * (7 - row)) / 7;
            setRGB1(prim, shade, shade, shade);
            prim->x2 = buffer->points[row + 1][i].vx;
            prim->y2 = buffer->points[row + 1][i].vy;
            prim->x3 = buffer->points[row + 1][next].vx;
            prim->y3 = buffer->points[row + 1][next].vy;
            shade    = (buffer->shade[row + 1][i] * (6 - row)) / 7;
            setRGB2(prim, shade, shade, shade);
            shade = (buffer->shade[row + 1][i] * (6 - row)) / 7;
            setRGB3(prim, shade, shade, shade);
            GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
        }
    }
}

/* Draws the burst: 32 semi-transparent Gouraud quads between a ring of radius 32 at its position and the ring 0x700 units higher, shaded by its size. */
MATCH void func_801F97E0(Scena07Burst* burst) {
    DVECTOR  low;
    DVECTOR  high;
    VECTOR   point;
    MATRIX   unused;
    POLY_G4* prim;
    s32      angle;
    u8       shade;
    u32      level;
    s8       i;

    angle = 0;
    setVector(&point, burst->pos.vx + (rcos(0) << 5), burst->pos.vy + (rsin(0) << 5), burst->pos.vz);
    Camera_ProjectPoint(&point, &low);
    point.vz = burst->pos.vz + TO_COORD(0x700);
    Camera_ProjectPoint(&point, &high);
    level = burst->unk_10;
    shade = 0x80;
    if (level >= 0x100) {
        level = 0xFF;
    }
    for (i = 0; i < 32; i++) {
        angle += 0x80;
        setVector(&point, burst->pos.vx + (rcos((u16)angle) << 5), burst->pos.vy + (rsin((u16)angle) << 5), burst->pos.vz);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
        Area_CellAddPrim(point.vx, point.vy, 0, sizeof(DR_MODE));
        prim = GFX_BeginPolyG4(1);
        setXY2(prim, low.vx, low.vy, high.vx, high.vy);
        setRGB0(prim, level, level, level);
        setRGB1(prim, level, level, level);
        Camera_ProjectPoint(&point, &low);
        point.vz = burst->pos.vz + TO_COORD(0x700);
        Camera_ProjectPoint(&point, &high);
        prim->x2 = low.vx;
        prim->y2 = low.vy;
        prim->x3 = high.vx;
        prim->y3 = high.vy;
        if ((u8)(i - 4) >= 16) {
            shade += 4;
        } else {
            shade -= 4;
        }
        level = (u16)(shade * burst->unk_10) >> 7;
        if (level >= 0x100) {
            level = 0xFF;
        }
        setRGB2(prim, level, level, level);
        setRGB3(prim, level, level, level);
        Area_CellAddPrim(point.vx, point.vy, 0, sizeof(POLY_G4));
    }
}

MATCH s32 func_801F9A80(SceneEffectRow* effect) {
    POLY_F4* poly;
    s32      point[3];
    DVECTOR  screen;
    s32      landed;

    poly = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(poly);
    SetSemiTrans(poly, 1);
    point[0] = effect->x;
    point[1] = effect->y;
    point[2] = effect->unk_C + (effect->unk_14 << 8);
    Camera_ProjectPoint(point, &screen);
    setXY2(poly, screen.vx - 1, screen.vy, screen.vx + 1, screen.vy);
    point[0] = effect->x;
    point[1] = effect->y;
    point[2] = effect->unk_C - (effect->unk_14 << 8);
    landed   = 0;
    if (point[2] < effect->unk_1C) {
        point[2] = effect->unk_1C;
        landed   = 1;
    }
    Camera_ProjectPoint(point, &screen);
    poly->x2 = screen.vx - 1;
    poly->y2 = screen.vy;
    poly->x3 = screen.vx + 1;
    poly->y3 = screen.vy;
    setRGB0(poly, 0x40, 0x40, 0x40);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_F4));
    return landed;
}

/* Draw a ring of 16 translucent triangles around the effect, on the ground below it. */
MATCH void func_801F9BDC(SceneEffectRow* effect) {
    DVECTOR  center;
    DVECTOR  edge;
    s32      pos[3];
    POLY_G3* prim;
    u8       i;
    u16      angle;

    pos[0] = effect->x;
    pos[1] = effect->y;
    pos[2] = Area_HeightSample(effect->x, effect->y) << 16;
    Camera_ProjectPoint(pos, &center);
    angle  = 0;
    i      = 0;
    pos[0] = effect->x + (rcos(0) << 2);
    pos[1] = effect->y + (rsin(0) << 2);
    pos[2] = Area_HeightSample(effect->x, effect->y) << 16;
    Camera_ProjectPoint(pos, &edge);
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, center.vx, center.vy);
        angle += 256;
        prim->x1 = edge.vx;
        prim->y1 = edge.vy;
        pos[0]   = effect->x + (rcos(angle) << 2);
        pos[1]   = effect->y + (rsin(angle) << 2);
        i++;
        pos[2] = Area_HeightSample(effect->x, effect->y) << 16;
        Camera_ProjectPoint(pos, &edge);
        prim->x2 = edge.vx;
        prim->y2 = edge.vy;
        setRGB0(prim, 64, 64, 64);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G3));
    } while (i < 16);
}

MATCH void func_801F9DA8(void) {
    s32 index;
    s8* effect;

    effect = (s8*)(AREA_WORK + 0x95C);
    index  = 0;
    do {
        *effect = 0;
        index += 1;
        effect += 32;
    } while ((index & BYTE_MASK) < 0x40U);
}

MATCH u8* func_801F9DD4(void) {
    u8* effect;
    u8  i;

    effect = MEM_PTR(u8, AREA_WORK + 0x95C);
    for (i = 0; i < 64; i++) {
        if (effect[0] == 0) {
            return effect;
        }
        effect += 32;
    }
    return NULL;
}

/* Starts a burst at a random distance and angle around the actor, on the ground. */
MATCH void func_801F9E10(u8* effect) {
    s32  radius;
    u32  angle;
    s32* cell;

    cell      = (s32*)effect;
    effect[0] = 1;
    effect[1] = 0;
    effect[2] = 16;
    cell[6]   = 0;
    cell[5]   = 0;
    radius    = ((rand() % 2) << 16) | ((rand() & BYTE_MASK) << 8);
    angle     = rand() & 0xFC0;
    cell[1]   = SELF(Actor)->pos.x.fixed + ((radius * rcos(angle)) >> 12);
    cell[2]   = SELF(Actor)->pos.y.fixed + ((radius * rsin(angle)) >> 12);
    {
        Coord sample_x = {cell[1]};
        Coord sample_y = {cell[2]};

        cell[7] = Area_HeightSample(sample_x.fixed, sample_y.fixed) << 16;
    }
    cell[3] = cell[7];
}

/* Advances the active effects: project, update and retire each. */
MATCH u8 func_801F9EFC(void) {
    SceneEffectRow* effect;
    MATRIX          matrix;
    s32             tpage;
    u8              i;
    u8              ran = 0;

    tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_UI, tpage & HALF_MASK);
    Camera_SetMatrix(&matrix);
    effect = (SceneEffectRow*)(AREA_WORK + 0x95C);
    for (i = 0; i < 64; effect++, i++) {
        if (effect->active != 0) {
            if (func_801F9A80(effect) & BYTE_MASK) {
                func_801F9BDC(effect);
            }
            effect->unk_14 += 0x2000;
            effect->unk_18 += 0x100000;
            effect->unk_C += effect->unk_18;
            if (--effect->unk_2 == 0) {
                effect->active = 0;
            }
            ran = 1;
        }
    }
    return ran;
}

#ifdef NON_MATCHING
NON_MATCHING void func_801FA01C(void) {
    SVECTOR* vertex;
    u16*     quad;
    u8*      shade;
    u16      ring;
    u16      col;
    u16      phase;
    s32      angle;
    u16      next;
    s32      dot;

    D_800E595C = 0;
    D_800E595E = 0;
    D_800E5960 = 0x1000;
    vertex     = MEM_PTR(SVECTOR, AREA_WORK + 0x1164);
    angle      = 0;
    for (ring = 0; ring < 15; ring++) {
        angle += 0x80;
        for (phase = 0, col = 0; col < 32; phase += 0x80, col++) {
            vertex->vx = (rsin((u16)angle) * rcos(phase)) >> 12;
            vertex->vy = (rsin((u16)angle) * rsin(phase)) >> 12;
            vertex->vz = rcos((u16)angle);
            vertex++;
        }
    }
    angle -= 0x80;
    /* FAKE: the loop weight lifts the ring vertex pointer over the phase counter in the allocator (s5 above s6); pure C best 17 rows. */
    do {
        vertex->vx = 0;
        vertex->vy = 0;
    } while (0);
    vertex->vz = -0x1000;

    quad = MEM_PTR(u16, AREA_WORK + 0x27F4);
    for (col = 0; col < 32; col++) {
        if (col + 1 < 32) {
            next = col + 1;
        } else {
            next = 0;
        }
        quad[1] = 0;
        quad[0] = 0;
        quad[2] = col + 1;
        quad[3] = next + 1;
        quad += 4;
    }
    for (ring = 0; ring < 14; ring++) {
        for (col = 0; col < 32; col++) {
            if (col + 1 < 32) {
                next = col + 1;
            } else {
                next = 0;
            }
            quad[0] = col + ring * 32 + 1;
            quad[1] = next + ring * 32 + 1;
            quad[2] = col + (ring + 1) * 32 + 1;
            quad[3] = next + (ring + 1) * 32 + 1;
            quad += 4;
        }
    }
    for (col = 0; col < 32; col++) {
        if (col + 1 < 32) {
            next = col + 1;
        } else {
            next = 0;
        }
        quad[0] = col + ring * 32 + 1;
        quad[1] = next + ring * 32 + 1;
        quad[2] = quad[3] = 0x1E1;
        quad += 4;
    }

    D_800E81D8 = 0;
    D_800E81DC = 0x1000;
    D_800E81E0 = 0x1000;
    VectorNormal(MEM_PTR(s32, AREA_WORK + 0x39D8), MEM_PTR(s32, AREA_WORK + 0x39D8));
    shade  = MEM_PTR(u8, AREA_WORK + 0x37F4);
    vertex = MEM_PTR(SVECTOR, AREA_WORK + 0x115C);
    for (col = 0; col < 482; col++) {
        dot = D_800E81D8 * vertex->vx + D_800E81DC * vertex->vy + D_800E81E0 * vertex->vz;
        if (dot <= 0) {
            *shade = 0;
        } else {
            dot = SquareRoot0(dot);
            if (dot >= 0x1000) {
                dot = 0xFFF;
            }
            *shade = dot >> 7;
        }
        vertex++;
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

    Camera_SetMatrix(&camera);
    screen = MEM_PTR(DVECTOR, AREA_WORK + 0x206C);
    vertex = MEM_PTR(s16, AREA_WORK + 0x115C);
    for (i = 0, depth = MEM_PTR(s16, AREA_WORK + 0x1160); i < 482; i++) {
        pos[0] = SELF(Actor)->pos.x.fixed + (vertex[0] << 5);
        pos[1] = SELF(Actor)->pos.y.fixed + (depth[-1] << 5);
        pos[2] = SELF(Actor)->pos.z.fixed + (depth[0] << 13) + TO_COORD(0x200);
        Camera_ProjectPoint(pos, screen);
        vertex += 4;
        depth += 4;
        screen++;
    }
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    quad   = MEM_PTR(u16, AREA_WORK + 0x27F4);
    shade  = MEM_PTR(u8, AREA_WORK + 0x37F4);
    screen = MEM_PTR(DVECTOR, AREA_WORK + 0x206C);
    for (i = 0; i < 512; i++) {
        poly = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        setXY4(poly, screen[quad[0]].vx, screen[quad[0]].vy, screen[quad[1]].vx, screen[quad[1]].vy, screen[quad[2]].vx, screen[quad[2]].vy, screen[quad[3]].vx, screen[quad[3]].vy);
        tone     = shade[quad[0]];
        poly->r0 = poly->g0 = poly->b0 = tone;
        tone                           = shade[quad[1]];
        poly->r1 = poly->g1 = poly->b1 = tone;
        tone                           = shade[quad[2]];
        poly->r2 = poly->g2 = poly->b2 = tone;
        tone                           = shade[quad[3]];
        poly->r3 = poly->g3 = poly->b3 = tone;
        quad += 4;
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    }
}

MATCH void func_801FA65C(void) {
    SYS_DISPATCH_BYTE(D_801FDE10, D_80146872);
}

MATCH void func_801FA698(void) {
    D_80144EC0 = 0;
    D_80146872 = 1;
}

/* Sets up the scena07 areas on entry: scroll, tiles and the scene script each area starts with. */
MATCH void func_801FA6B4(void) {
    u8* bgm;

    if (LOHU(g_GameAreaId) == AREA_ID_CAMP_BEFORE_ANGEL_TOWER && !SYS_TestFlag(g_SceneFlags, 7)) {
        func_801C1DF0(1);
        func_801BE1B0(2);
        g_PartyPos.z.part.integer = 0xD80;
        Area_ScrollAdvance(0xD80);
    }
    if (LOHU(g_GameAreaId) == AREA_ID_URKAN_TAPA) {
        if (g_GameCellType == 1 && !SYS_TestFlag(g_SceneFlags, 4)) {
            SYS_SetFlag(g_SceneFlags, 4);
            g_AreaScrollTargetX = 0x5B8000;
            g_AreaScrollTargetY = 0x98000;
            Area_InitMapRenderer();
            func_801BE1B0(0);
            bgm = &g_SndBGMId;
            SND_StartDecrescendo(g_BGMTracks[*bgm].sep_slot, g_BGMTracks[*bgm].sequence, 100, 0x20);
            *bgm = 1;
        }
    } else if (!SYS_TestFlag(g_SceneFlags, 4)) {
        SYS_ClearFlag(g_SceneFlags, 5);
        SYS_ClearFlag(g_SceneFlags, 6);
    }
    if (LOHU(g_GameAreaId) == AREA_ID_ANGEL_TOWER_GARR_FIGHT) {
        if (!SYS_TestFlag(g_SceneFlags, 8)) {
            Game_SetScriptActive();
            g_ScriptVars[0] = 0;
            func_801BE1B0(0);
            g_ScenarioState.state_04 = 6;
            g_ScenarioState.step     = 0;
        }
        if (!SYS_TestFlag(g_SceneFlags, 9)) {
            func_801A4BC0(0x25, 0x3D, 0x51);
            func_801A4BC0(0x26, 0x3D, 0x51);
        } else {
            EMI_ArchiveLoad(0x254);
            while (!EMI_IsReady()) {
                SYS_ThreadWait(1);
            }
            func_801A4BC0(0x25, 0x3D, 0x50);
            func_801A4BC0(0x26, 0x3D, 0x50);
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_TIDAL_CAVES_OUTSIDE) {
        SYS_SetFlag(g_SceneEventFlags, 0x4F);
    }
    if (LOHU(g_GameAreaId) == AREA_ID_FAIRY_VILLAGE_DOLPHIN && g_GameCellType == 1) {
        if (!SYS_TestFlag(g_SceneFlags, 0)) {
            Game_SetScriptActive();
            g_ScriptVars[0] = 0;
            func_801C1DF0(0);
            func_801BE1B0(0);
            g_AreaDrawFlags          = 0;
            g_ScenarioState.state_04 = 1;
            g_ScenarioState.step     = 0;
        } else if (!SYS_TestFlag(g_SceneFlags, 2) && SYS_TestFlag(g_SceneFlags, 1)) {
            Game_SetScriptActive();
            g_AreaScrollTargetX = 0x2D8000;
            g_AreaScrollTargetY = 0x5D0000;
            Area_InitMapRenderer();
            func_801BE1B0(2);
            g_ScenarioState.state_04 = 3;
            g_ScenarioState.step     = 0;
            D_80146258 |= 8;
        }
    }
    D_80146872 = 2;
}

MATCH void func_801FAA2C(void) {
    SYS_DISPATCH_BYTE(D_801FDE1C, g_ScenarioState.state_04);
}

MATCH void func_801FAA68(void) {
}

MATCH void func_801FAA70(void) {
    u8* step = &g_ScenarioState.step;

    switch (*step) {
        case 0:
            if (g_SysThreads[2].state == 0) {
                MESSAGE_START_WAIT(MSG_SCENA07_001);
                *step = 1;
            }
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                UI_ModeSet(1);
                g_AreaScrollTargetX = 0x2D8000;
                g_AreaScrollTargetY = 0x5D0000;
                Area_InitMapRenderer();
                g_AreaDrawFlags = 0x1F;
                *step           = 2;
            }
            break;
        case 2:
            if (g_SysThreads[2].state == 0) {
                *g_ScriptVars = 1;
                *step         = 3;
            }
            break;
        case 3:
            if (*g_ScriptVars == 0x15) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0);
                *g_ScriptVars            = 0;
                g_ScenarioState.state_04 = 0;
                *step                    = 0;
            }
            break;
    }
}
