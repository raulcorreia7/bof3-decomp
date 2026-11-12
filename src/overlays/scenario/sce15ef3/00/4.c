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
        func_801D1A60();
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
    func_801D1D20(&work->pos, &work->vx, work->tint.bytes.unk_5D, work->tint.bytes.unk_5E);
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
    func_801D230C();
    if (--g_Task->timer == 0) {
        g_Task->timer = 4;
        g_Task->header.mode += 1;
    }
}

INCLUDE_ASM(func_801D1250);

INCLUDE_ASM(func_801D12E0);

MATCH void func_801D1370(void) {
    Actor* work;
    u8     timer;

    work           = g_Task;
    work->screen_x = work->screen_x - 0x10;
    work->screen_y = work->screen_y - 0x10;
    func_801D230C();
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

INCLUDE_ASM(func_801D1614);

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

INCLUDE_ASM(func_801D1758);

INCLUDE_ASM(func_801D18CC);

INCLUDE_ASM(func_801D19A0);

INCLUDE_ASM(func_801D1A60);

#include "overlays/scenario/Scene_DrawRedGradient.h"

INCLUDE_ASM(func_801D1D20);

INCLUDE_ASM(func_801D1FF8);

MATCH void func_801D230C(void) {
    Point3DL pos;
    s16      x;
    s16      y;
    u16      angle;

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

INCLUDE_ASM(Scene_DrawScanBar);

#include "overlays/scenario/Scene_ClearScanBars.h"

#include "overlays/scenario/Scene_ClaimScanBar.h"

INCLUDE_ASM(Scene_UpdateScanBars);
