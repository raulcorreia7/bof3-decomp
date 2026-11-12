#include "magic105_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    PartyMember* saved_work;
    PartyMember* saved_active;
    PartyMember* swap;
    s32          count;

    BMagic_DispatchTaskPair(func_801EED1C, Effect_PlayOnZeroTick);
    count = 0;
    do {
        if (BMAGIC_EFFECT_SLOTS[(u8)count].header.flags & 1) {
            saved_work            = g_Task;
            saved_active          = g_BattleEffectBattler;
            swap                  = BMAGIC_EFFECT_SLOTS[(u8)count].target.party;
            g_Task                = MEM_PTR(PartyMember, &BMAGIC_EFFECT_SLOTS[(u8)count]);
            g_BattleEffectBattler = swap;
            func_801EF880();
            func_801EFCF0();
            g_BattleEffectBattler = saved_active;
            g_Task                = saved_work;
        }
        count += 1;
    } while ((u8)count < BMAGIC_EFFECT_COUNT);
}

INCLUDE_ASM(func_801EED1C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEF78 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFBC(void) {
    Magic105Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 3) {
        func_801EF2F0();
        func_801EF3A0();
        PopMatrix();
    }
}

MATCH void func_801EF06C(void) {
    PartyMember* src;
    PartyMember* work;
    FAKE_STACK_PADS(u8, 8);

    src                = BATTLE_ACTIVE_WORK;
    work               = g_Task;
    work->pos.x.fixed  = src->pos.x.fixed;
    work->pos.y.fixed  = src->pos.y.fixed;
    work->pos.z        = src->pos.z;
    work->unk_0C       = src->unk_0C + D_801F004C[work->unk_04];
    work->unk_10       = src->unk_0C + D_801F004E[work->unk_04];
    work->param.unk_0B = 0;
    g_Task->unk_09     = 0;
    g_Task->timer      = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF124(void) {
    u8 slot;
    u8 tick;

    if ((g_FrameCount & 3) == (g_Task->unk_04 & 3)) {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            BMAGIC_EFFECT_SLOTS[slot].target.party = g_Task;
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
            BMAGIC_EFFECT_SLOTS[slot].header.step  = 0;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = g_Task->unk_09;
            BMAGIC_EFFECT_SLOTS[slot].unk_10       = g_Task->unk_10;
            g_Task->param.unk_0B += 1;
        }
    }
    if (g_FrameCount & 1) {
        tick           = g_Task->unk_09 + 1;
        g_Task->unk_09 = tick;
        if (tick == 0x20) {
            g_Task->header.step += 1;
        }
    }
}

MATCH void func_801EF250(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 64) {
        g_Task->header.step = g_Task->header.step + 1;
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
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF3A0);

MATCH void func_801EF880(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 11), 1, g_Task);
}

MATCH void func_801EF8C4(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0078, g_Task->header.step);
    Battle_ProjectRange();
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF930(void) {
    u16*         cell;
    s8           tint;
    s32          height;
    PartyMember* work;

    cell                                = &D_1F800000.view.area.entry_data;
    *cell                               = ((u32)(rsin(g_Task->unk_09 << 6) * 3) >> 4);
    D_1F800000.view.area.entity_counter = (g_Task->unk_09 << 6) + 0x40;
    g_Task->pos.x.fixed                 = BATTLE_ACTIVE_WORK->pos.x.fixed + ((rsin(g_Task->unk_10) * D_1F800000.view.area.entity_counter) >> 3);
    g_Task->pos.y.fixed                 = BATTLE_ACTIVE_WORK->pos.y.fixed + ((rcos(g_Task->unk_10) * D_1F800000.view.area.entity_counter) >> 3);
    COORD_INT(g_Task->pos.z)            = (COORD_INT(BATTLE_ACTIVE_WORK->pos.z) + *cell) - 0x20;
    height                              = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) << 16;
    work                                = g_Task;
    work->unk_25                        = 0x1D;
    work->unk_14                        = height >> 16;
    g_Task->unk_26                      = 0;
    g_Task->unk_27                      = 0xA0;
    g_Task->unk_28                      = 0;
    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
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
    Actor_SelectScript((RANDOM_MASK(1)) + 1);
    g_Task->timer = RANDOM_MASK(0x3F);
    g_Task->header.step += 1;
}

MATCH void func_801EFB68(void) {
    g_Task->timer += 1;
    g_Task->pos.x.fixed += (rsin((g_Task->timer & 0x3F) << 8) * 8) >> 3;
    g_Task->pos.y.fixed += (rcos((g_Task->timer & 0x3F) << 8) * 8) >> 3;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) - 8;
    if ((Actor_StepAnimOnce() & BYTE_MASK) || (COORD_INT(g_Task->pos.z) < g_Task->unk_14)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.flags = 0;
        g_Task->header.mode  = 0;
        g_Task->header.step  = 0;
    }
}

/* func_801EFC8C */
#include "overlays/bmagic/BMagic_AllocEffect.h"

INCLUDE_ASM(func_801EFCF0);
