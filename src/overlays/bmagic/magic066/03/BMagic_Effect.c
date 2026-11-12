#include "magic066_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* task;
    PartyMember* battler;
    u32          slot;
    u32          i;
    u16*         src;
    u16*         dst;

    battler                            = g_BattleEffectBattler;
    task                               = g_Task;
    task->pos.x.fixed                  = battler->pos.x.fixed;
    task->pos.y.fixed                  = battler->pos.y.fixed;
    task->pos.z.fixed                  = battler->pos.z.fixed;
    slot                               = Battle_AllocEffect(1, 17) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    /* Copies arena palette rows 26 and 2 into the work copy with STP set, then restores row 2's color 0. */
    for (i = 0, dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW), src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW); i < 256; i++) {
        *dst++ = *src++ | 0x8000;
    }
    {
        u16* row_dst;
        u16* row_src;

        for (i = 0, row_dst = MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW), row_src = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00); i < 16; i++) {
            *row_dst++ = *row_src++ | 0x8000;
        }
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    g_GfxPalettePending                                     = 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 24;
    g_Task->header.mode += 1;
}

MATCH void func_801EEDB8(void) {
    u8           timer;
    u32          slot;
    PartyMember* work;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        slot                               = Battle_AllocEffect(1, 17) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = work;
        /* FAKE: keeps the target selector read after the slot stores, as retail orders it. */
        FAKE_BARRIER();
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x20);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

/* func_801EEEBC */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF00(void) {
    SYS_DISPATCH_BYTE(D_801F006C, g_Task->header.step);
    if (BATTLE_ACTIVE_WORK->param.unk_0B != 0xFF) {
        Effect_SetActorMatrix();
        func_801EF158();
        PopMatrix();
    }
}

MATCH void func_801EEF78(void) {
    g_Task->pos.x.fixed  = g_AreaScrollTargetX + 0xFFEE0000;
    g_Task->pos.y.fixed  = g_AreaScrollTargetY + 0x880000;
    g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    g_Task->param.unk_0B = 0x1A;
    g_Task->unk_09       = 0x10;
    g_Task->unk_10       = 0;
    g_Task->unk_14       = 0xF0;
    g_Task->header.step++;
}

MATCH void func_801EEFF8(void) {
    PartyMember* work = g_Task;
    u8           timer;

    work->pos.y.fixed += 0xFFFF4000;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF04C(void) {
    s32 phase;

    g_Task->param.unk_0B = (g_Task->param.unk_0B - 1) & 0x1F;
    phase                = g_Task->unk_10 + 2;
    g_Task->unk_10       = phase;
    if (phase == 0x80) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF0A4(void) {
    g_Task->param.unk_0B = (g_Task->param.unk_0B - 1) & 0x1F;
    g_Task->unk_14 -= 2;
    g_Task->unk_10 -= 2;
    if (g_Task->unk_10 == 0x20) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF108(void) {
    s32 count;

    count = g_Task->unk_10 - 1;
    g_Task->unk_14 -= 2;
    g_Task->unk_10 = count;
    if (count == 0) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF158);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF834(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 2, g_Task);
}

MATCH void func_801EF878(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        D_801F00B0[i] = 0;
    }
    g_Task->unk_09 = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF8C8(void) {
    u8 timer;

    func_801EF984();
    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 96) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF930(void) {
    u8 timer;

    func_801EF984();
    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if ((timer & BYTE_MASK) == 128) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF984);

INCLUDE_ASM(func_801EFCC8);

MATCH void func_801EFFB0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 3072;
    rot.vy = 0;
    rot.vz = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}
