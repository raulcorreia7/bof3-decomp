#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F743C(void) {
    Actor* actor;

    actor              = g_Task;
    actor->vx          = 0;
    actor->header.mode = actor->header.mode + 1;
}

/* Hint: a3 is lhu of the low half of vx (0x0C), while 0x0C is also read as a word; the same field needs two widths. */
MATCH void func_801F745C(void) {
    Actor* work;

    work = g_Task;
    func_801F7660(work->pos.x.fixed, work->pos.y.fixed, work->pos.z.fixed, work->vx);
    g_Task->vx += 16;
    if (g_Task->vx > 1280) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F74CC(void) {
    Actor_Clear();
}

MATCH void func_801F74EC(void) {
    SYS_DISPATCH_TASK(D_801FD5B4, 1, g_Task);
}

MATCH void func_801F7530(void) {
    Actor* actor;

    actor              = g_Task;
    actor->vx          = 4096;
    actor->header.mode = actor->header.mode + 1;
}

MATCH void func_801F7554(void) {
    SpawnedActor* spawned;
    Actor*        actor;
    u8            slot;

    if ((SP_REF(Actor*, 0x44)->vx & 0xF) == 0) {
        slot = Actor_FindFreeSpawned();
        if (slot != GAME_NONE) {
            spawned               = &g_SpawnedActors[slot];
            spawned->header.flags = 1;
            spawned->type         = 0x26;
            actor                 = g_Task;
            spawned->pos.x.fixed  = actor->pos.x.fixed;
            spawned->pos.y.fixed  = actor->pos.y.fixed;
            spawned->pos.z.fixed  = Area_SampleHeight(actor->pos.x.fixed, actor->pos.y.fixed) << 16;
        }
    }
    actor = g_Task;
    actor->vx -= 1;
    if (actor->vx == 0) {
        actor->header.mode += 1;
    }
}

MATCH void func_801F7640(void) {
    Actor_Clear();
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F7660(s32 x, s32 y, s32 z, u16 angle) {
    u8       segment;
    u16      next_radial;
    u16      radial;
    s32      height;
    s32      point[3];
    MATRIX   matrix;
    s16      correction;
    s16      step;
    s16      inner_step;
    u32      difference;
    s32      step_limit;
    u16      inner_angle;
    u16      outer_angle;
    u32      step_low;
    u32      inner_color;
    u32      outer_color;
    POLY_G4* primitive;

    height = z;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 0x3C0, 0) & 0xFFFF, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    Area_SetCameraMatrix(&matrix);

    outer_color = 0x80;
    step_limit  = angle;
    step_low    = step_limit & 0xFFFF;
    step        = angle - 0x100;
    if (step_low >= 0x401U) {
        difference  = 0x500 - step_low;
        outer_color = (u32)(difference + (difference >> 31)) >> 1;
        step_limit  = 0x400;
        step        = angle - 0x100;
    }
    inner_step  = step;
    inner_color = 0;
    if (step < 0) {
        correction  = -step;
        inner_color = (u32)(correction + ((u32)correction >> 31)) >> 1;
        inner_step  = 0;
    } else {
        inner_color = 0;
    }
    outer_angle = step_limit & 0xFFFF;
    inner_angle = inner_step & 0xFFFF;
    radial      = 0;
    next_radial = 0x100;
    segment     = 0;
    do {
        primitive = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(primitive);
        SetSemiTrans(primitive, 1);

        point[0] = x + (((rsin(outer_angle) * (rcos(radial) * 3)) >> 12) * 16);
        point[1] = y + (((rsin(outer_angle) * (rsin(radial) * 3)) >> 12) * 16);
        point[2] = height + (rcos(outer_angle) * 0x3000);
        Area_ProjectPoint(point, (DVECTOR*)&primitive->x0);
        setRGB0(primitive, outer_color, outer_color, outer_color);

        point[0] = x + (((rsin(inner_angle) * (rcos(radial) * 3)) >> 12) * 16);
        point[1] = y + (((rsin(inner_angle) * (rsin(radial) * 3)) >> 12) * 16);
        point[2] = height + (rcos(inner_angle) * 0x3000);
        Area_ProjectPoint(point, (DVECTOR*)&primitive->x1);
        setRGB1(primitive, inner_color, inner_color, inner_color);

        point[0] = x + (((rsin(outer_angle) * (rcos(next_radial) * 3)) >> 12) * 16);
        point[1] = y + (((rsin(outer_angle) * (rsin(next_radial) * 3)) >> 12) * 16);
        point[2] = height + (rcos(outer_angle) * 0x3000);
        Area_ProjectPoint(point, (DVECTOR*)&primitive->x2);
        setRGB2(primitive, outer_color, outer_color, outer_color);

        radial += 0x100;
        next_radial += 0x100;
        segment++;
        point[0] = x + (((rsin(inner_angle) * (rcos(next_radial) * 3)) >> 12) * 16);
        point[1] = y + (((rsin(inner_angle) * (rsin(next_radial) * 3)) >> 12) * 16);
        point[2] = height + (rcos(inner_angle) * 0x3000);
        Area_ProjectPoint(point, (DVECTOR*)&primitive->x3);
        setRGB3(primitive, inner_color, inner_color, inner_color);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    } while (segment < 16);
}
#else
INCLUDE_ASM(func_801F7660);
#endif

MATCH void func_801F7A78(void) {
    SYS_DISPATCH_BYTE(D_801FD5DC, D_80146872);
}

MATCH void func_801F7AB4(void) {
    D_80146872 = 1;
}
