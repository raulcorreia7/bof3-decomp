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

INCLUDE_ASM(func_801D0DD8);

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

INCLUDE_ASM(func_801D12A0);

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

INCLUDE_ASM(func_801D147C);

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
            func_801D1B10(slot);
        }
    }
    return alive;
}

INCLUDE_ASM(func_801D1B10);

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

INCLUDE_ASM(func_801D21B4);

INCLUDE_ASM(func_801D23A0);

INCLUDE_ASM(func_801D2474);

INCLUDE_ASM(func_801D26BC);

INCLUDE_ASM(func_801D2934);

MATCH void func_801D2B44(void) {
    Actor_Clear();
}

MATCH void func_801D2B64(void) {
    SYS_DISPATCH_TASK(D_801D396C, 1, g_Task);
}

INCLUDE_ASM(func_801D2BA8);

INCLUDE_ASM(func_801D2C00);

INCLUDE_ASM(func_801D2C94);

INCLUDE_ASM(func_801D2D5C);

MATCH void func_801D2DEC(void) {
    SYS_DISPATCH_TASK(D_801D397C, 1, g_Task);
}

INCLUDE_ASM(func_801D2E30);

INCLUDE_ASM(func_801D2FD8);

INCLUDE_ASM(func_801D30AC);

INCLUDE_ASM(func_801D32F4);

INCLUDE_ASM(func_801D34F0);

MATCH void func_801D369C(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801D36BC);
