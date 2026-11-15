#include "sce15ef3_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801D0C48(void) {
    u8* work;

    work                   = (u8*)g_Task;
    FIELD(s32, work, 0x34) = g_Game.members[0].pos.x.fixed;
    FIELD(s32, work, 0x38) = g_Game.members[0].pos.y.fixed;
    FIELD(s32, work, 0x3C) = D_80145ECC;
    func_801D16DC();
    func_801D19A0();
    work    = (u8*)g_Task;
    work[9] = 0x78;
    work    = (u8*)g_Task;
    work[1]++;
}

MATCH void func_801D0CC4(void) {
    if (g_AreaDrawFlags == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
    } else {
        Area_StepSparkEmitters();
        func_801D18CC();
    }
}

MATCH void func_801D0D18(void) {
    Actor_Clear();
}

MATCH void func_801D0D38(void) {
    SYS_DISPATCH_TASK(D_801D27CC, 1, g_Task);
}

MATCH void func_801D0D7C(void) {
    u8* work;

    work    = (u8*)g_Task;
    work[9] = 8;
    work    = (u8*)g_Task;
    work[1]++;
}

MATCH void func_801D0DAC(void) {
    Scene_DrawRedGradient(-(g_Task->timer << 5) & BYTE_MASK);
    if (--g_Task->timer == 0) {
        g_Task->timer = 8;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D0E38(void) {
    u8 timer;

    SCENE_RED_GRADIENT_FADE(timer, 0x8, 5);
}

MATCH void func_801D0EAC(void) {
    SYS_DISPATCH_TASK(D_801D27D8, 1, g_Task);
}

INCLUDE_ASM(func_801D0EF0);

MATCH void func_801D0F94(void) {
    Actor* work;

    work = g_Task;
    work->pos.z.fixed += 0x800000;
    func_801D1D20(&work->pos, &work->vx, work->tint.bytes.rgb.red, work->tint.bytes.rgb.green);
    if (g_ScriptVars[0] == 0xB) {
        g_Task->header.mode += 1;
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
    SYS_DISPATCH_TASK(D_801D27EC, 1, g_Task);
}

INCLUDE_ASM(func_801D10AC);

MATCH void func_801D11C8(void) {
    g_Task->pos.z.fixed += 0xFF000000;
    Scene_SetXFixed();
    if (--g_Task->timer == 0) {
        g_Task->timer = 4;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D1250(void) {
    u8 timer;

    g_Task->screen_x += 64;
    g_Task->screen_y -= 64;
    Scene_SetXFixed();
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->timer = 2;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D12E0(void) {
    u8 timer;

    g_Task->screen_x -= 64;
    g_Task->screen_y += 64;
    Scene_SetXFixed();
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->timer = 16;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D1370(void) {
    Actor* work;
    u8     timer;

    work           = g_Task;
    work->screen_x = work->screen_x - 0x10;
    work->screen_y = work->screen_y - 0x10;
    Scene_SetXFixed();
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        Actor_Clear();
    }
}

MATCH void func_801D13DC(void) {
    SYS_DISPATCH_TASK(D_801D2800, 1, g_Task);
}

MATCH void func_801D1420(void) {
    g_Task->timer       = 0;
    g_Task->unk_06      = 0x10;
    g_Task->header.mode = g_Task->header.mode + 1;
}

MATCH void func_801D1460(void) {
    g_Task->timer += 16;
    if (g_Task->timer == 0) {
        Scene_DrawRedFade(255);
        g_Task->header.mode += 1;
    } else {
        Scene_DrawRedFade(g_Task->timer);
    }
}

MATCH void func_801D14DC(void) {
    g_Task->timer -= 16;
    if (g_AreaDrawFlags != 0) {
        Scene_DrawRedFade(g_Task->timer);
    }
    if (g_Task->timer == 0) {
        if (g_AreaDrawFlags == 0) {
            Actor_Clear();
        } else {
            g_Task->header.mode--;
        }
    }
}

MATCH void func_801D1588(void) {
    SYS_DISPATCH_TASK(D_801D280C, 1, g_Task);
}

#include "overlays/scenario/Scene_EndScan.h"

MATCH void func_801D1614(void) {
    if (g_Task->timer == 0) {
        Scene_ClaimScanBar();
        g_Task->timer = (rand() & 0xF) + 0x18;
    } else {
        g_Task->timer--;
    }
    if (g_AreaDrawFlags != 0) {
        Scene_UpdateScanBars(0xF0);
    }
    if (g_AreaDrawFlags == 0) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D16BC(void) {
    Actor_Clear();
}

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

    GFX_SET_DRAW_MODE(GetTPage(0, 1, 960, 0));
    Area_AddCellPrim(spark->x, spark->y, 0, sizeof(DR_MODE));
    Area_ProjectPoint(&spark->x, &xy);
    dot = (TILE_1*)g_GfxPrimCursor;
    SetTile1(dot);
    SetSemiTrans(dot, 1);
    setXY0(dot, xy.vx, xy.vy);
    if (spark->unk_3 != 0) {
        setRGB0(dot, 128, 128, 128);
    } else {
        setRGB0(dot, 128, 0, 0);
    }
    Area_AddCellPrim(spark->x, spark->y, 0, sizeof(TILE_1));
    box = (TILE*)g_GfxPrimCursor;
    SetTile(box);
    SetSemiTrans(box, 1);
    setXY0(box, xy.vx - 1, xy.vy - 1);
    box->w = 3;
    box->h = 3;
    if (spark->unk_3 != 0) {
        setRGB0(box, 32, 32, 32);
    } else {
        setRGB0(box, 32, 0, 0);
    }
    Area_AddCellPrim(spark->x, spark->y, 0, sizeof(TILE));
}

INCLUDE_ASM(func_801D18CC);

#include "shared/Area_SeedSparkEmitters.h"

MATCH void func_801D19A0(void){AREA_SEED_SPARK_EMITTERS(D_801D27B0)}
/* func_801D1A60 */
#include "shared/Area_StepSparkEmitters.h"

#include "overlays/scenario/Scene_DrawRedGradient.h"

MATCH void func_801D1D20(WorldPos* pos, s32* step, u8 red, u8 green) {
    FAKE_STACK_PADS(u8, 0x10); /* FAKE: retain the retail frame and projected-point spacing. */

    s32      point[3];
    s32      point2[3];
    SVECTOR  screen[2];
    POLY_G4* prim;
    s32      angle;
    u16      angle16;
    u8       i;

    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, 896, 256) & HALF_MASK);

    angle    = 65024;
    point[0] = pos->x.fixed + ((((rcos((u16)angle) * 5) << 6) >> 4));
    point[1] = pos->y.fixed + ((((rsin((u16)angle) * 5) << 6) >> 4));
    point[2] = pos->z.fixed;
    Area_ProjectPoint(point, (DVECTOR*)&screen[0]);
    point2[0] = step[0] + ((((rcos((u16)angle) * 5) << 6) >> 4));
    point2[1] = step[1] + ((((rsin((u16)angle) * 5) << 6) >> 4));
    point2[2] = step[2];
    Area_ProjectPoint(point2, (DVECTOR*)&screen[1]);

    i = 0;
    do {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = screen[0].vx;
        prim->y0 = screen[0].vy;
        prim->x1 = screen[1].vx;
        prim->y1 = screen[1].vy;

        angle += 128;
        angle16  = (u16)angle;
        point[0] = pos->x.fixed + ((((rcos(angle16) * 5) << 6) >> 4));
        point[1] = pos->y.fixed + ((((rsin(angle16) * 5) << 6) >> 4));
        point[2] = pos->z.fixed;
        Area_ProjectPoint(point, (DVECTOR*)&screen[0]);
        point2[0] = step[0] + ((((rcos(angle16) * 5) << 6) >> 4));
        point2[1] = step[1] + ((((rsin(angle16) * 5) << 6) >> 4));
        point2[2] = step[2];
        Area_ProjectPoint(point2, (DVECTOR*)&screen[1]);

        prim->x2 = screen[0].vx;
        prim->y2 = screen[0].vy;
        prim->x3 = screen[1].vx;
        prim->y3 = screen[1].vy;
        setRGB0(prim, red, red, red);
        setRGB1(prim, green, green, green);
        setRGB2(prim, red, red, red);
        setRGB3(prim, green, green, green);
        GFX_AddPrim(1, sizeof(POLY_G4));
        i++;
    } while (i < 16);
}

INCLUDE_ASM(func_801D1FF8);

/* func_801D230C */
MATCH void Scene_SetXFixed(void) {
    Point3l pos;
    s16     x;
    s16     y;
    u16     angle;

    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, 896, 256));
    pos.x = g_Task->pos.x.fixed;
    pos.y = g_Task->pos.y.fixed;
    pos.z = g_Task->pos.z.fixed;
    x     = g_Task->screen_x;
    y     = g_Task->screen_y;
    angle = g_Task->unk_32;
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
    GFX_AddPrim(1, sizeof(TILE));
}

#include "overlays/scenario/Scene_DrawScanBar.h"

#include "overlays/scenario/Scene_ClearScanBars.h"

#include "overlays/scenario/Scene_ClaimScanBar.h"

INCLUDE_ASM(Scene_UpdateScanBars);
