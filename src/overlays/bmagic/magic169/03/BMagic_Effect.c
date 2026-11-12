#include "magic169_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC38);

MATCH void func_801EED8C(void) {
    u16* src;
    u16* dst;
    u16  i;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    func_800AFD9C();
    g_Task->pos.z.fixed += TO_COORD(192);
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    MEM(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = MEM(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    g_GfxPalettePending                                 = 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
    g_Task->unk_09       = 0;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
}

INCLUDE_ASM(func_801EEEB0);

MATCH void func_801EEFE0(void) {
    u8 timer;

    if (g_Task->param.unk_0B == 0) {
        timer          = g_Task->unk_09 - 1;
        g_Task->unk_09 = timer;
        if (!(timer & BYTE_MASK)) {
            g_Task->header.mode += 1;
        }
    }
}

#include "shared/Effect_StartPlaying.h"

INCLUDE_ASM(func_801EF070);

/* func_801EF210 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF254(void) {
    BMagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC14, header.step);
}

MATCH void func_801EF2CC(void) {
    u8           count;
    u8           i;
    u8           slot;
    PartyMember* actor;
    PartyMember* work;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        actor          = &g_Game.members[g_Task->unk_04];
        g_Task->facing = actor->facing;
        WorldPos_Copy(&g_Task->pos, &actor->pos);
        g_Task->param.unk_0B = 0;
        g_Task->unk_09       = 8;
        g_Task->timer        = 0;
        g_Task->header.step += 1;
        i = 0;
        do {
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                work                                   = g_Task;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = ((i & BYTE_MASK) >> 2) + 0x10;
                BMAGIC_EFFECT_SLOTS[slot].target.party = work;
                g_Task->param.unk_0B += 1;
            }
            i++;
        } while (i < 24);
    }
}

MATCH void func_801EF444(void) {
    PartyMember* battler;
    u8           timer;
    PartyMember* work;

    work         = g_Task;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    battler      = &g_Game.members[work->unk_04];
    if (!(timer & BYTE_MASK)) {
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF4FC(void) {
    s32 cue;

    g_PaletteFades[g_Task->timer].offset.red++;
    g_PaletteFades[g_Task->timer].offset.green++;
    g_PaletteFades[g_Task->timer].offset.blue++;
    if (--g_Task->unk_09 == 0) {
        cue = EMI_CUE_ID(SND_BANK_COMMON, 0x02);
        if (g_Task->unk_04 & 0x1) {
            cue = EMI_CUE_ID(SND_BANK_COMMON, 0x01);
        }
        SND_QueueSelectionFx(cue);
        g_Task->header.step++;
    }
}

#include "overlays/bmagic/Effect_NextStepUnderTickLimit.h"

INCLUDE_ASM(func_801EF688);

MATCH void func_801EF7D0(void) {
    if (g_Task->param.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        if (func_801DB524(g_Task->unk_04) & BYTE_MASK) {
            Battle_MarkDamaged(g_Task->unk_04);
        }
        func_801E5988();
    }
}

MATCH void func_801EF860(void) {
    SYS_DISPATCH_TASK(D_801F0420, 1, g_Task);
}

INCLUDE_ASM(func_801EF8A4);

MATCH void func_801EFA18(void) {
    s32  phase;
    s32  speed;
    s16* angle_cell;
    u8   count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->unk_0C      = 8;
        angle_cell          = &D_1F800004;
        phase               = g_Task->param.unk_0B & 0xF;
        *angle_cell         = phase << 8;
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x800000;
        speed               = ((RANDOM_MASK(3)) << 20) + 0x200000;
        g_Task->unk_14      = speed;
        g_Task->unk_20      = speed / 16;
        g_Task->unk_5D      = (RANDOM_MASK(7)) + 6;
        g_Task->unk_5E      = (RANDOM_MASK(7)) + 6;
        g_Task->unk_5F      = (RANDOM_MASK(7)) + 6;
        g_Task->unk_09      = 0;
        g_Task->timer       = 16;
        g_Task->header.step++;
    }
}

MATCH void func_801EFBC4(void) {
    s32  phase;
    s32  b;
    s16* angle_cell;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B & 0xF;
    g_Task->unk_0C += 2;
    *angle_cell         = phase << 8;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    if (g_Task->unk_20 < g_Task->unk_14) {
        b              = g_Task->unk_14 - g_Task->unk_20;
        g_Task->unk_14 = b;
        g_Task->pos.z.fixed += b;
    }
    count          = g_Task->unk_09 + 2;
    g_Task->unk_09 = count;
    if (count == 16) {
        g_Task->header.step++;
    }
}

MATCH void func_801EFCF4(void) {
    s32  phase;
    s32  b;
    s16* angle_cell;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B & 0xF;
    g_Task->unk_0C += 1;
    *angle_cell         = phase << 8;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    if (g_Task->unk_20 < g_Task->unk_14) {
        b              = g_Task->unk_14 - g_Task->unk_20;
        g_Task->unk_14 = b;
        g_Task->pos.z.fixed += b;
    }
    if (g_FrameCount & 0x1) {
        count          = g_Task->unk_09 - 1;
        g_Task->unk_09 = count;
        if (count == 0) {
            g_BattleEffectBattler->param.unk_0B -= 1;
            Actor_Clear();
        }
    }
}

INCLUDE_ASM(func_801EFE3C);

INCLUDE_ASM(func_801F0090);

/* func_801F0368 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F03CC */
#include "overlays/bmagic/Actor_Clear.h"
