#include "sce15ef3_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801D0C48(void) {
    u8* work;

    work                   = SELF(u8);
    FIELD(s32, work, 0x34) = g_Game.members[0].pos.x.fixed;
    FIELD(s32, work, 0x38) = g_Game.members[0].pos.y.fixed;
    FIELD(s32, work, 0x3C) = g_Game.members[0].pos.z.fixed;
    func_801D16DC();
    func_801D19A0();
    work    = SELF(u8);
    work[9] = 0x78;
    work    = SELF(u8);
    work[1]++;
}

MATCH void func_801D0CC4(void) {
    if (g_AreaDrawFlags == 0) {
        SELF(Actor)->header.mode = SELF(Actor)->header.mode + 1;
    } else {
        Area_StepSparkEmitters();
        func_801D18CC();
    }
}

MATCH void func_801D0D18(void) {
    Actor_Clear();
}

MATCH void func_801D0D38(void) {
    SYS_DISPATCH_TASK(D_801D27CC, 1, g_Self);
}

MATCH void func_801D0D7C(void) {
    u8* work;

    work    = SELF(u8);
    work[9] = 8;
    work    = SELF(u8);
    work[1]++;
}

MATCH void func_801D0DAC(void) {
    Scene_DrawRedGradient(-(SELF(Actor)->timer << 5) & BYTE_MASK);
    if (--SELF(Actor)->timer == 0) {
        SELF(Actor)->timer = 8;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801D0E38(void) {
    u8 timer;

    SCENE_RED_GRADIENT_FADE(timer, 0x8, 5);
}

MATCH void func_801D0EAC(void) {
    SYS_DISPATCH_TASK(D_801D27D8, 1, g_Self);
}

MATCH void func_801D0EF0(void) {
    SELF(Actor)->pos.x.fixed = g_Game.members[2].pos.x.fixed;
    SELF(Actor)->pos.y.fixed = g_Game.members[2].pos.y.fixed;
    SELF(Actor)->pos.z.fixed = TO_COORD(Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed));
    setVector(SELF(Actor), SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, SELF(Actor)->pos.z.fixed);
    SELF(Actor)->tint.steps.delta.r = 0;
    SELF(Actor)->tint.steps.delta.g = -0x80;
    SELF(Actor)->timer              = 0x20;
    SELF(Actor)->header.mode++;
}

MATCH void func_801D0F94(void) {
    Actor* work;

    work = SELF(Actor);
    work->pos.z.fixed += 0x800000;
    func_801D1D20(&work->pos, &work->vx, work->tint.bytes.rgb.r, work->tint.bytes.rgb.g);
    if (g_ScriptVars[0] == 0xB) {
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801D1008(void) {
    Scene_AdvanceActorMode();
}

MATCH void func_801D1028(void) {
    Scene_AdvanceActorMode();
}

MATCH void func_801D1048(void) {
    Actor_Clear();
}

MATCH void func_801D1068(void) {
    SYS_DISPATCH_TASK(D_801D27EC, 1, g_Self);
}

MATCH void func_801D10AC(void) {
    DVECTOR start;
    DVECTOR end;
    s32     point[3];
    MATRIX  camera;

    SELF(Actor)->pos.x.fixed = TO_COORD(24) + COORD_HALF;
    SELF(Actor)->pos.y.fixed = TO_COORD(18);
    SELF(Actor)->pos.z.fixed = (Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) << 16) + TO_COORD(0x800);
    SELF(Actor)->screen_x    = 0x80;
    SELF(Actor)->screen_y    = 0x180;
    SELF(Actor)->unk_32      = 0;
    SELF(Actor)->timer       = 8;
    SELF(Actor)->header.mode++;
    Camera_SetMatrix(&camera);
    point[0] = SELF(Actor)->pos.x.fixed;
    point[1] = SELF(Actor)->pos.y.fixed;
    point[2] = SELF(Actor)->pos.z.fixed;
    Camera_ProjectPoint(point, &start);
    point[2] -= TO_COORD(256);
    Camera_ProjectPoint(point, &end);
    SELF(Actor)->unk_32 = ratan2(end.vy - start.vy, end.vx - start.vx) + 0x400;
    SND_SEPlay(0x202);
}

MATCH void func_801D11C8(void) {
    SELF(Actor)->pos.z.fixed += 0xFF000000;
    Scene_SetXFixed();
    if (--SELF(Actor)->timer == 0) {
        SELF(Actor)->timer = 4;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801D1250(void) {
    u8 timer;

    SELF(Actor)->screen_x += 64;
    SELF(Actor)->screen_y -= 64;
    Scene_SetXFixed();
    timer              = SELF(Actor)->timer - 1;
    SELF(Actor)->timer = timer;
    if (timer == 0) {
        SELF(Actor)->timer = 2;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801D12E0(void) {
    u8 timer;

    SELF(Actor)->screen_x -= 64;
    SELF(Actor)->screen_y += 64;
    Scene_SetXFixed();
    timer              = SELF(Actor)->timer - 1;
    SELF(Actor)->timer = timer;
    if (timer == 0) {
        SELF(Actor)->timer = 16;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801D1370(void) {
    Actor* work;
    u8     timer;

    work           = SELF(Actor);
    work->screen_x = work->screen_x - 0x10;
    work->screen_y = work->screen_y - 0x10;
    Scene_SetXFixed();
    timer              = SELF(Actor)->timer - 1;
    SELF(Actor)->timer = timer;
    if (timer == 0) {
        Actor_Clear();
    }
}

MATCH void func_801D13DC(void) {
    SYS_DISPATCH_TASK(D_801D2800, 1, g_Self);
}

MATCH void func_801D1420(void) {
    SELF(Actor)->timer       = 0;
    SELF(Actor)->unk_06      = 0x10;
    SELF(Actor)->header.mode = SELF(Actor)->header.mode + 1;
}

MATCH void func_801D1460(void) {
    SELF(Actor)->timer += 16;
    if (SELF(Actor)->timer == 0) {
        Scene_DrawRedFade(255);
        SELF(Actor)->header.mode += 1;
    } else {
        Scene_DrawRedFade(SELF(Actor)->timer);
    }
}

MATCH void func_801D14DC(void) {
    SELF(Actor)->timer -= 16;
    if (g_AreaDrawFlags != 0) {
        Scene_DrawRedFade(SELF(Actor)->timer);
    }
    if (SELF(Actor)->timer == 0) {
        if (g_AreaDrawFlags == 0) {
            Actor_Clear();
        } else {
            SELF(Actor)->header.mode--;
        }
    }
}

MATCH void func_801D1588(void) {
    SYS_DISPATCH_TASK(D_801D280C, 1, g_Self);
}

#include "overlays/scenario/shared/Scene_EndScan.h"

MATCH void func_801D1614(void) {
    if (SELF(Actor)->timer == 0) {
        Scene_ClaimScanBar();
        SELF(Actor)->timer = (rand() & 0xF) + 0x18;
    } else {
        SELF(Actor)->timer--;
    }
    if (g_AreaDrawFlags != 0) {
        Scene_UpdateScanBars(0xF0);
    }
    if (g_AreaDrawFlags == 0) {
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801D16BC(void) {
    Actor_Clear();
}

/* kept: retail steps the row and tail pointers apart; a SpriteSpark walk changes the bytes. */
MATCH void func_801D16DC(void) {
    s32   index;
    s8*   row;
    void* tail;

    row   = (s8*)AREA_WORK;
    index = 0;
    tail  = (void*)(AREA_WORK + 2);
    do {
        *row                     = 0;
        *(s8*)((u8*)(tail) + -1) = 0;
        *(s8*)(tail)             = 0;
        tail += 0x18;
        index += 1;
        row += 24;
    } while ((index & HALF_MASK) < 0x100U);
}

#include "shared/Area_FindFreeSpriteRow.h"

/* Draw a spark as a lit dot with a dim box behind it; the flag picks grey or red. */
MATCH void func_801D1758(SpriteSpark* spark) {
    TILE_1* dot;
    TILE*   box;
    DVECTOR xy;
    /* FAKE: retail reserves 48 bytes of unused stack. */
    FAKE_STACK_PADS(u8, 48);

    GFX_SET_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Area_CellAddPrim(spark->pos.vx, spark->pos.vy, 0, sizeof(DR_MODE));
    Camera_ProjectPoint(&spark->pos.vx, &xy);
    dot = (TILE_1*)g_GfxPrimCursor;
    SetTile1(dot);
    SetSemiTrans(dot, 1);
    setXY0(dot, xy.vx, xy.vy);
    if (spark->blink != 0) {
        setRGB0(dot, 128, 128, 128);
    } else {
        setRGB0(dot, 128, 0, 0);
    }
    Area_CellAddPrim(spark->pos.vx, spark->pos.vy, 0, sizeof(TILE_1));
    box = (TILE*)g_GfxPrimCursor;
    SetTile(box);
    SetSemiTrans(box, 1);
    setXY0(box, xy.vx - 1, xy.vy - 1);
    setWH(box, 3, 3);
    if (spark->blink != 0) {
        setRGB0(box, 32, 32, 32);
    } else {
        setRGB0(box, 32, 0, 0);
    }
    Area_CellAddPrim(spark->pos.vx, spark->pos.vy, 0, sizeof(TILE));
}

MATCH s32 func_801D18CC(void) {
    SpriteSpark* spark;
    MATRIX       camera;
    s32          active;
    s32          step;
    u16          i;
    u8           life;

    active = 0;
    Camera_SetMatrix(&camera);
    spark = MEM_PTR(SpriteSpark, AREA_WORK);
    i     = 0;
    do {
        if (spark->active != 0) {
            step           = spark->z_delta + 0x20000;
            spark->z_delta = step;
            spark->pos.vz += step;
            spark->blink ^= 1;
            func_801D1758(spark);
            life        = spark->life - 1;
            spark->life = life;
            active      = 1;
            if (life == 0) {
                spark->active = 0;
                spark->unk_01 = 0;
            }
        }
        spark++;
        i++;
    } while (i < SPRITE_SPARK_COUNT);
    return active;
}

#include "shared/Area_SeedSparkEmitters.h"

MATCH void func_801D19A0(void){AREA_SEED_SPARK_EMITTERS(D_801D27B0)}
/* func_801D1A60 */
#include "shared/Area_StepSparkEmitters.h"

#include "overlays/scenario/shared/Scene_DrawRedGradient.h"

MATCH void func_801D1D20(WorldPos* pos, s32* step, u8 red, u8 green) {
    FAKE_STACK_PADS(u8, 0x10); /* FAKE: retain the retail frame and projected-point spacing. */

    s32      point[3];
    s32      point2[3];
    SVECTOR  screen[2];
    POLY_G4* prim;
    s32      angle;
    u16      angle16;
    u8       i;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 896, 256) & HALF_MASK);

    angle    = 65024;
    point[0] = pos->x.fixed + ((((rcos((u16)angle) * 5) << 6) >> 4));
    point[1] = pos->y.fixed + ((((rsin((u16)angle) * 5) << 6) >> 4));
    point[2] = pos->z.fixed;
    Camera_ProjectPoint(point, (DVECTOR*)&screen[0]);
    point2[0] = step[0] + ((((rcos((u16)angle) * 5) << 6) >> 4));
    point2[1] = step[1] + ((((rsin((u16)angle) * 5) << 6) >> 4));
    point2[2] = step[2];
    Camera_ProjectPoint(point2, (DVECTOR*)&screen[1]);

    i = 0;
    do {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY2(prim, screen[0].vx, screen[0].vy, screen[1].vx, screen[1].vy);

        angle += 128;
        angle16  = (u16)angle;
        point[0] = pos->x.fixed + ((((rcos(angle16) * 5) << 6) >> 4));
        point[1] = pos->y.fixed + ((((rsin(angle16) * 5) << 6) >> 4));
        point[2] = pos->z.fixed;
        Camera_ProjectPoint(point, (DVECTOR*)&screen[0]);
        point2[0] = step[0] + ((((rcos(angle16) * 5) << 6) >> 4));
        point2[1] = step[1] + ((((rsin(angle16) * 5) << 6) >> 4));
        point2[2] = step[2];
        Camera_ProjectPoint(point2, (DVECTOR*)&screen[1]);

        prim->x2 = screen[0].vx;
        prim->y2 = screen[0].vy;
        prim->x3 = screen[1].vx;
        prim->y3 = screen[1].vy;
        setRGB0(prim, red, red, red);
        setRGB1(prim, green, green, green);
        setRGB2(prim, red, red, red);
        setRGB3(prim, green, green, green);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
        i++;
    } while (i < 16);
}

/* Draws one shaded ring of 16 triangles around pos, rotated by angle_b. */
MATCH void func_801D1FF8(Pos3* pos, s16 radius_a, s16 radius_b, u16 angle_b, u8 shade_a, u8 shade_b) {
    DVECTOR  screen;
    DVECTOR  size;
    DVECTOR  scale;
    DVECTOR  rot;
    MATRIX   camera;
    POLY_G3* prim;
    u16      angle;
    u8       phase;
    u8       i;

    Camera_SetMatrix(&camera);
    Camera_ProjectPoint((s32*)pos, &screen);
    size.vx = radius_a;
    size.vy = radius_b;
    Game_ProjectWorldPoint(pos, &size, &scale);
    phase = g_FrameCount & 1;
    scale.vx += phase;
    scale.vy += phase;
    angle = 0;
    i     = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, screen.vx, screen.vy);
        rot.vx   = (scale.vx * rcos(angle)) >> 12;
        rot.vy   = (scale.vy * rsin(angle)) >> 12;
        prim->x1 = screen.vx + ((rot.vx * rcos(angle_b) - rot.vy * rsin(angle_b)) >> 12);
        prim->y1 = screen.vy + ((rot.vx * rsin(angle_b) + rot.vy * rcos(angle_b)) >> 12);
        angle += ONE / 16;
        rot.vx   = (scale.vx * rcos(angle)) >> 12;
        rot.vy   = (scale.vy * rsin(angle)) >> 12;
        prim->x2 = screen.vx + ((rot.vx * rcos(angle_b) - rot.vy * rsin(angle_b)) >> 12);
        prim->y2 = screen.vy + ((rot.vx * rsin(angle_b) + rot.vy * rcos(angle_b)) >> 12);
        setRGB0(prim, shade_a, shade_a, phase ? shade_a : 0);
        setRGB1(prim, shade_b, shade_b, phase ? shade_b : 0);
        setRGB2(prim, shade_b, shade_b, phase ? shade_b : 0);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G3));
        i++;
    } while (i < 16);
}

/* func_801D230C */
MATCH void Scene_SetXFixed(void) {
    Pos3 pos;
    s16  x;
    s16  y;
    u16  angle;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 896, 256));
    pos.x = SELF(Actor)->pos.x.fixed;
    pos.y = SELF(Actor)->pos.y.fixed;
    pos.z = SELF(Actor)->pos.z.fixed;
    x     = SELF(Actor)->screen_x;
    y     = SELF(Actor)->screen_y;
    angle = SELF(Actor)->unk_32;
    func_801D1FF8(&pos, x, y, angle, 192, 0);
}

/* func_801D23AC */
MATCH void Scene_DrawRedFade(u8 red) {
    TILE* prim;

    prim = (TILE*)g_GfxPrimCursor;
    SetTile(prim);
    SetSemiTrans(prim, 1);
    prim->w = SCREEN_WIDTH;
    setXY0(prim, 0, 0);
    prim->h = SCREEN_HEIGHT;
    setRGB0(prim, red, 0, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));
}

#include "overlays/scenario/shared/Scene_DrawScanBar.h"

#include "overlays/scenario/shared/Scene_ClearScanBars.h"

#include "overlays/scenario/shared/Scene_ClaimScanBar.h"

#include "overlays/scenario/shared/Scene_UpdateScanBars.h"
