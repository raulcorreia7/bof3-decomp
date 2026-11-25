#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F743C(void) {
    Actor* actor;

    actor              = TASK(Actor);
    actor->vx          = 0;
    actor->header.mode = actor->header.mode + 1;
}

/* Hint: a3 is lhu of the low half of vx (0x0C), while 0x0C is also read as a word; the same field needs two widths. */
MATCH void func_801F745C(void) {
    Actor* work;

    work = TASK(Actor);
    func_801F7660(work->pos.x.fixed, work->pos.y.fixed, work->pos.z.fixed, work->vx);
    TASK(Actor)->vx += 16;
    if (TASK(Actor)->vx > 1280) {
        TASK(Actor)->header.mode += 1;
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

    actor              = TASK(Actor);
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
            actor                 = TASK(Actor);
            spawned->pos.x.fixed  = actor->pos.x.fixed;
            spawned->pos.y.fixed  = actor->pos.y.fixed;
            spawned->pos.z.fixed  = Area_HeightSample(actor->pos.x.fixed, actor->pos.y.fixed) << 16;
        }
    }
    actor = TASK(Actor);
    actor->vx -= 1;
    if (actor->vx == 0) {
        actor->header.mode += 1;
    }
}

MATCH void func_801F7640(void) {
    Actor_Clear();
}

/* scales a unit-circle term to the ring radius */
static inline s32 Scene_RingRadius(s32 unit) {
    return unit * 3;
}

/* draws a ring of 16 shaded quads about (x, y, z), its rim and inner edge set by angle */
MATCH void func_801F7660(s32 x, s32 y, s32 z, u16 angle) {
    u16      radial;
    u16      next_radial;
    u8       segment;
    s32      point[3];
    MATRIX   matrix;
    s16      step;
    s16      inner_step;
    u32      difference;
    u16      step_limit;
    u16      inner_angle;
    u16      outer_angle;
    u32      step_low;
    u32      inner_color;
    u32      outer_color;
    POLY_G4* primitive;

    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_UI, GetTPage(0, 1, 0x3C0, 0) & 0xFFFF);
    Camera_SetMatrix(&matrix);

    outer_color = 0x80;
    step_limit  = angle;
    step_low    = step_limit & 0xFFFF;
    if (step_low > 0x400) {
        difference  = 0x500 - step_low;
        outer_color = (difference + (difference >> 31)) >> 1;
        step_limit  = 0x400;
    }
    step        = angle - 0x100;
    inner_step  = step;
    inner_color = 0;
    if (step < 0) {
        inner_color = (u32)(-step + ((u32)-step >> 31)) >> 1;
        inner_step  = 0;
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

        point[0] = x + (((rsin(outer_angle) * Scene_RingRadius(rcos(radial))) >> 12) * 16);
        point[1] = y + (((rsin(outer_angle) * Scene_RingRadius(rsin(radial))) >> 12) * 16);
        point[2] = z + (rcos(outer_angle) * 0x3000);
        Camera_ProjectPoint(point, (DVECTOR*)&primitive->x0);
        setRGB0(primitive, outer_color, outer_color, outer_color);

        point[0] = x + (((rsin(inner_angle) * Scene_RingRadius(rcos(radial))) >> 12) * 16);
        point[1] = y + (((rsin(inner_angle) * Scene_RingRadius(rsin(radial))) >> 12) * 16);
        point[2] = z + (rcos(inner_angle) * 0x3000);
        Camera_ProjectPoint(point, (DVECTOR*)&primitive->x1);
        setRGB1(primitive, inner_color, inner_color, inner_color);

        point[0] = x + (((rsin(outer_angle) * Scene_RingRadius(rcos(next_radial))) >> 12) * 16);
        point[1] = y + (((rsin(outer_angle) * Scene_RingRadius(rsin(next_radial))) >> 12) * 16);
        point[2] = z + (rcos(outer_angle) * 0x3000);
        Camera_ProjectPoint(point, (DVECTOR*)&primitive->x2);
        setRGB2(primitive, outer_color, outer_color, outer_color);

        point[0] = x + (((rsin(inner_angle) * Scene_RingRadius(rcos(next_radial))) >> 12) * 16);
        point[1] = y + (((rsin(inner_angle) * Scene_RingRadius(rsin(next_radial))) >> 12) * 16);
        radial += 0x100;
        next_radial += 0x100;
        segment++;
        point[2] = z + (rcos(inner_angle) * 0x3000);
        Camera_ProjectPoint(point, (DVECTOR*)&primitive->x3);
        setRGB3(primitive, inner_color, inner_color, inner_color);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    } while (segment < 16);
}

MATCH void func_801F7A78(void) {
    SYS_DISPATCH_BYTE(D_801FD5DC, D_80146872);
}

MATCH void func_801F7AB4(void) {
    D_80146872 = 1;
}
