#include "magic105_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    PartyBattler* saved_work;
    PartyBattler* saved_active;
    PartyBattler* swap;
    s32           count;

    Bmagic_DispatchTaskPair(func_801EED1C, Effect_PlayOnZeroTick);
    count = 0;
    do {
        if (BMAGIC_EFFECT_SLOTS[(u8)count].flags & 1) {
            saved_work   = g_Task;
            saved_active = D_801EB4E0;
            swap         = BMAGIC_EFFECT_SLOTS[(u8)count].target.party;
            g_Task       = MEM_PTR(PartyBattler, &BMAGIC_EFFECT_SLOTS[(u8)count]);
            D_801EB4E0   = swap;
            func_801EF880();
            func_801EFCF0();
            D_801EB4E0 = saved_active;
            g_Task     = saved_work;
        }
        count += 1;
    } while ((u8)count < BMAGIC_EFFECT_COUNT);
}

INCLUDE_ASM(func_801EED1C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF78(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EEFBC(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 3) {
        func_801EF2F0();
        func_801EF3A0();
        PopMatrix();
    }
}

MATCH void func_801EF06C(void) {
    PartyBattler* src;
    PartyBattler* work;
    STACK_PADS(u8, 8);

    src             = BATTLE_ACTIVE_WORK;
    work            = g_Task;
    work->pos.x.raw = src->pos.x.raw;
    work->pos.y.raw = src->pos.y.raw;
    work->pos.z     = src->pos.z;
    work->unk_0C    = src->unk_0C + D_801F004C[work->unk_04];
    work->unk_10    = src->unk_0C + D_801F004E[work->unk_04];
    work->unk_0B    = 0;
    g_Task->unk_09  = 0;
    g_Task->timer   = 0;
    g_Task->step += 1;
}

INCLUDE_ASM(func_801EF124);

MATCH void func_801EF250(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 64) {
        g_Task->step = g_Task->step + 1;
    }
}

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801EF2F0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    pos.vx = (g_Task->pos.x.raw >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.raw >> 9) - 0x4000;
    pos.vz = -g_Task->pos.z.half.hi / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF3A0);

MATCH void func_801EF880(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 11), 1, g_Task);
}

MATCH void func_801EF8C4(void) {
    g_ScriptBank = 0x800C3800u;
    SYS_DISPATCH_BYTE(D_801F0078, g_Task->step);
    func_800AF764();
    g_ScriptBank = AREA_SCRIPT_BANK;
}

MATCH void func_801EF930(void) {
    u16*          cell;
    s8            tint;
    s32           height;
    PartyBattler* work;

    cell                                = &D_1F800000.view.area.entry_data;
    *cell                               = (u16)((u32)(rsin(g_Task->unk_09 << 6) * 3) >> 4);
    D_1F800000.view.area.entity_counter = (g_Task->unk_09 << 6) + 0x40;
    g_Task->pos.x.raw =
        BATTLE_ACTIVE_WORK->pos.x.raw + ((rsin(g_Task->unk_10) * D_1F800000.view.area.entity_counter) >> 3);
    g_Task->pos.y.raw =
        BATTLE_ACTIVE_WORK->pos.y.raw + ((rcos(g_Task->unk_10) * D_1F800000.view.area.entity_counter) >> 3);
    g_Task->pos.z.half.hi = (u16)((u16)BATTLE_ACTIVE_WORK->pos.z.half.hi + *cell) - 0x20;
    height                = Area_SampleHeight(g_Task->pos.x.raw, g_Task->pos.y.raw) << 16;
    work                  = g_Task;
    work->unk_25          = 0x1D;
    work->unk_14          = height >> 16;
    g_Task->unk_26        = 0;
    g_Task->unk_27        = 0xA0;
    g_Task->unk_28        = 0;
    g_Task->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    tint                = -0x40;
    g_Task->unk_5D      = tint;
    g_Task->unk_5E      = tint;
    g_Task->unk_5F      = tint;
    g_Task->unk_5C      = 1;
    g_Task->unk_2A      = 0;
    g_Task->unk_29      = 3;
    g_Task->unk_24      = 4;
    g_Task->unk_2C.half = 0;
    g_Task->unk_2B      = 0;
    Actor_SelectScript((rand() & 1) + 1);
    g_Task->timer = rand() & 0x3F;
    g_Task->step += 1;
}

MATCH void func_801EFB68(void) {
    g_Task->timer += 1;
    g_Task->pos.x.raw += (s32)(rsin((g_Task->timer & 0x3F) << 8) * 8) >> 3;
    g_Task->pos.y.raw += (s32)(rcos((g_Task->timer & 0x3F) << 8) * 8) >> 3;
    g_Task->pos.z.half.hi = (u16)g_Task->pos.z.half.hi - 8;
    if ((func_8014DAEC() & 0xFF) || (g_Task->pos.z.half.hi < g_Task->unk_14)) {
        D_801EB4E0->unk_0B -= 1;
        g_Task->flags = 0;
        g_Task->mode  = 0;
        g_Task->step  = 0;
    }
}

/* func_801EFC8C */
#include "overlays/bmagic/BMagic_AllocEffect.h"

INCLUDE_ASM(func_801EFCF0);
