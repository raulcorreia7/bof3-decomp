#include "area049_13.h"
#include "area/spad.h"
#include "overlays/area/AreaSprite.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_8011700C(void) {
    /* Retail reads the handler record from the entry $v0; the uninitialised local reads it. */
    u8* entity;

    SYS_DISPATCH_TASK(D_8011818C, 1, entity);
}

MATCH void func_80117048(void) {
    ((Actor*)g_Task)->pos.x.fixed = TO_COORD(11) + COORD_HALF;
    ((Actor*)g_Task)->pos.y.fixed = TO_COORD(84) + COORD_HALF;
    ((Actor*)g_Task)->pos.z.fixed = TO_COORD(256);
    func_801172D0();
    ((Actor*)g_Task)->header.mode += 1;
}

MATCH void func_801170A4(void) {
    if (!(func_80117410() & BYTE_MASK)) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801170D8);

INCLUDE_ASM(func_801172D0);

INCLUDE_ASM(func_80117410);

MATCH void func_80117514(void) {
    AreaSprite* work = D_801181DC;
    u8          count;

    count = work->flags_02 - 1;
    work->origin.x += work->normal.vx * 2;
    work->origin.y += work->normal.vy * 2;
    work->flags_02 = count;
    work->half_size += 0x80;
    if (!(count & BYTE_MASK)) {
        ((AreaSprite*)D_801181DC)->flags_02 = 0x40;
        ((AreaSprite*)D_801181DC)->flags_01++;
    }
}

MATCH void func_8011759C(void) {
    AreaSprite* work = D_801181DC;
    u8          count;

    work->origin.x += work->normal.vx;
    work->flags_03--;
    work->origin.y += work->normal.vy;
    count = --((AreaSprite*)D_801181DC)->flags_02;
    if (!(count & BYTE_MASK)) {
        ((AreaSprite*)D_801181DC)->flags = 0;
    }
}

MATCH void func_80117610(void) {
    SYS_DISPATCH_TASK(D_8011819C, 1, g_Task);
    func_80117900();
}

MATCH void func_8011765C(void) {
    g_GameFlags |= GAME_FLAG_MENU_LOCK;
    func_801172D0();
    ((Actor*)g_Task)->timer = 180;
    ((Actor*)g_Task)->header.mode += 1;
}

INCLUDE_ASM(func_801176B8);

INCLUDE_ASM(func_80117768);

MATCH void func_80117818(void) {
    if (func_80117900() == 0) {
        func_80196070();
        D_80146258 &= ~0x40;
    }
}

MATCH void func_80117864(void* arg0) {
    struct {
        u8  unk_00;
        u8  unk_01;
        u8  unk_02;
        u8  unk_03;
        s32 unk_04;
        s32 unk_08;
        s32 unk_0C;
        u8  pad_10[0xC];
        s32 unk_1C;
        u8  pad_20[4];
        u16 unk_24;
        u8  unk_26;
    }* p = arg0;

    Actor* a = g_Task;
    s32    v;

    p->unk_04 = a->pos.x.fixed;
    p->unk_08 = a->pos.y.fixed;
    v         = a->pos.z.fixed;
    p->unk_00 = 1;
    p->unk_24 = 0x80;
    p->unk_03 = 0xC0;
    p->unk_26 = 2;
    p->unk_1C = 0;
    p->unk_01 = 0;
    p->unk_02 = 0x20;
    p->unk_0C = v;
}

#include "overlays/area/Area_FindFreeWorkRow.h"

INCLUDE_ASM(func_80117900);

MATCH void func_80117A30(void) {
    SYS_DISPATCH_BYTE(D_801181AC, g_Task->header.step);
}

MATCH void func_80117A74(void) {
    if (SYS_TestFlag(D_80144ED0, 62) != 0) {
        func_80117B60(0x40);
        func_80196070();
    }
    g_Task->header.step++;
}

MATCH void func_80117ACC(void) {
    if (SYS_TestFlag(D_80144ED0, 62) != 0) {
        g_Task->timer++;
        func_80117B60(0x80 - (g_Task->timer >> 1));
        if (g_Task->timer >= 128) {
            func_80196070();
        }
    }
}

INCLUDE_ASM(func_80117B60);

MATCH void func_80117BF4(void) {
    SYS_DISPATCH_BYTE(D_801181B4, g_Task->header.step);
}

MATCH void func_80117C38(void) {
    Scene_AdvanceActorState();
}

INCLUDE_ASM(func_80117C58);

MATCH void func_80117DF0(void) {
    if (!(g_FrameCount & 0x1)) {
        ((Actor*)g_Task)->timer += 1;
    }
    if (((Actor*)g_Task)->timer >= 128U) {
        Actor_Clear();
    }
    func_80117E78(128 - ((Actor*)g_Task)->timer, 0);
}

INCLUDE_ASM(func_80117E78);
