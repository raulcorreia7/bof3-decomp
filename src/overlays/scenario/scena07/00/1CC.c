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
    u8* row;

    if ((g_Task->vx & 0x7) == 0) {
        row = func_801F8394();
        if (row != NULL) {
            Scene_InitSpark((FallingSpark*)row);
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

INCLUDE_ASM(func_801F78B0);

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
    u8* row;

    func_801F9330(D_801FDFC0);
    if (g_Task->vx >= 9) {
        row = func_801F8394();
        if (((g_Task->vx & 3) == 0) && (row != NULL)) {
            func_801F8478(row);
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

INCLUDE_ASM(func_801F7BE0);

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

MATCH void func_801F81D4(u8* row) {
    GFX_DRAW_PROJECTED_DISC((s32*)(row + 0x0C), row[3], 0x20, 1);
}

MATCH void func_801F8358(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK);
    i = 0;
    do {
        p[0] = 0;
        i++;
        p += 0x1C;
    } while (i < 8);
    D_801FDFC4 = 0;
    D_801FDFC8 = 0;
}

MATCH u8* func_801F8394(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < 8; i++) {
        if (p[SCRATCH_ROW_OFFSET] == 0) {
            return p;
        }
        p += SCRATCH_ROW_STRIDE;
    }
    return NULL;
}

#include "overlays/scenario/Scene_InitSpark.h"

/* Starts a spark row at a random point of a sphere around the actor, raised 512 units. */
MATCH void func_801F8478(u8* row) {
    s32* cell;
    u16  yaw;
    u16  pitch;
    s16  radius;

    cell    = (s32*)row;
    row[0]  = 1;
    row[1]  = 0;
    row[2]  = 8;
    row[3]  = 0;
    cell[2] = 0;
    row[4]  = 1;
    yaw     = rand() & 0x7FF;
    pitch   = rand() & 0xFFF;
    radius  = ((rand() % 2) << 12) | (rand() & 0xFFF);
    cell[3] = g_Task->pos.x.fixed + ((radius * ((rsin(yaw) * rcos(pitch)) >> 12)) >> 8);
    cell[4] = g_Task->pos.y.fixed + ((radius * ((rsin(yaw) * rsin(pitch)) >> 12)) >> 8);
    cell[5] = g_Task->pos.z.fixed + radius * rcos(yaw) + TO_COORD(512);
}

MATCH u8 func_801F85D8(void) {
    u8     active;
    u8*    rec;
    s32    i;
    MATRIX matrix;

    active = 0;
    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, FONT_TPAGE_X, FONT_TPAGE_Y));
    Area_SetCameraMatrix(&matrix);
    rec = MEM_PTR(u8, AREA_WORK);
    i   = 0;
    do {
        if (rec[0] != 0) {
            D_801FDDF0[rec[1]](rec);
            active = 1;
            func_801F81D4(rec);
        }
        i++;
        rec += SCRATCH_ROW_STRIDE;
    } while ((u32)(i & BYTE_MASK) < 8);
    return active;
}

MATCH void func_801F86BC(u8* row) {
    u8 next;

    row[3] += 6;
    if (--row[2] == 0) {
        next   = row[1] + 1;
        row[2] = row[4];
        row[1] = next;
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

INCLUDE_ASM(func_801F90F4);

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

INCLUDE_ASM(func_801FA01C);

INCLUDE_ASM(func_801FA38C);

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
