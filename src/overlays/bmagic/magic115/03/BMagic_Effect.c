#include "magic115_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    PartyMember* actor;
    PartyMember* work;
    u32          slot;
    u8           i;
    u16*         dst;
    u16*         src;

    actor                              = g_Battle.selected_actor;
    g_Task->pos.x.fixed                = actor->pos.x.fixed;
    g_Task->pos.y.fixed                = actor->pos.y.fixed;
    g_Task->pos.z.fixed                = actor->pos.z.fixed;
    slot                               = Battle_AllocEffect(1, 48) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = work;
    GFX_FreePaletteFadeTarget(actor);
    g_Task->timer = GFX_AllocPaletteFade(actor, 0, 0, 0, 1);
    i             = 0;
    dst           = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src           = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i] = src[i] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    g_GfxPalettePending                                      = 1;
    SND_QueueSelectionEffect(0x100);
    g_Task->param.unk_0B = 1;
    g_Task->unk_09       = 0;
    g_Task->header.mode++;
}

MATCH void func_801EEDDC(void) {
    g_PaletteFades[g_Task->timer].offset.red   = g_Task->unk_09 * 2;
    g_PaletteFades[g_Task->timer].offset.green = g_Task->unk_09 * 2;
    g_PaletteFades[g_Task->timer].offset.blue  = g_Task->unk_09 * 2;
    if (g_Task->unk_09 >= 6) {
        g_Task->header.mode++;
    }
}

MATCH void func_801EEEB0(void) {
    if (g_FrameCount & 1) {
        g_PaletteFades[g_Task->timer].offset.red -= 1;
        g_PaletteFades[g_Task->timer].offset.green -= 1;
        g_PaletteFades[g_Task->timer].offset.blue -= 1;
    }
    if (g_PaletteFades[g_Task->timer].offset.red == 0) {
        GFX_FreePaletteFade(g_Task->timer);
        g_Task->header.mode++;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF054 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF098(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8C0 + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EF130);

MATCH void func_801EF27C(void) {
    s32          angle;
    s32*         angle_cell;
    u8           count;
    u32          slot;
    s8           tint;
    PartyMember* battler;

    Actor_StepAnimLoop();
    count               = g_Task->unk_09 + 1;
    g_Task->unk_09      = count;
    angle               = (count & 0x3F) << 6;
    angle_cell          = &D_1F800000;
    *angle_cell         = angle;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin(angle) * 0xC000) >> 12);
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle_cell) * 0xC000) >> 12);
    if ((g_Task->unk_09 & 7) == 0) {
        slot                               = Battle_AllocEffect(1, 48) & BYTE_MASK;
        battler                            = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = battler;
        g_BattleEffects[slot].arg.unk_09   = (g_Task->unk_09 & 0xFC) + 8;
        g_BattleEffects[slot].pos.x.fixed  = g_Task->pos.x.fixed;
        g_BattleEffects[slot].pos.y.fixed  = g_Task->pos.y.fixed;
        g_BattleEffects[slot].pos.z.fixed  = g_Task->pos.z.fixed;
        g_BattleEffectBattler->unk_09++;
        g_BattleEffectBattler->param.unk_0B++;
    }
    if (g_Task->unk_09 == 0x40) {
        g_Task->header.flags |= 0x20;
        g_Task->unk_5C = 1;
        tint           = -0x40;
        g_Task->unk_5D = tint;
        g_Task->unk_5E = tint;
        g_Task->unk_5F = tint;
        g_Task->header.step++;
    }
}

MATCH void func_801EF49C(void) {
    s32  value = -0x80;
    s32* d;
    u8   tick;

    g_Task->unk_5D -= 4;
    g_Task->unk_5E -= 4;
    g_Task->unk_5F -= 4;
    Actor_StepAnimLoop();
    tick                = g_Task->unk_09 + 1;
    g_Task->unk_09      = tick;
    d                   = &D_1F800000;
    d[0]                = BMAGIC_PHASE_ANGLE(tick & BMAGIC_PHASE_MASK);
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + FIXED_MUL(rsin(d[0]), 0xC000);
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + FIXED_MUL(rcos(d[0]), 0xC000);
    g_Task->unk_5D      = value;
    g_Task->header.step += 1;
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF5F8(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8D0 + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF690(void) {
    g_Task->unk_25      = 0x1D;
    g_Task->unk_26      = 0;
    g_Task->scale.x     = 0x10000;
    g_Task->scale.y     = 0x10000;
    g_Task->unk_48      = 1;
    g_Task->unk_27      = 0xA0;
    g_Task->unk_28      = 0;
    g_Task->unk_24      = 4;
    g_Task->unk_5D      = 0;
    g_Task->unk_5E      = 0;
    g_Task->unk_5F      = 0;
    g_Task->unk_5C      = 0;
    g_Task->unk_2A      = 0;
    g_Task->unk_29      = 4;
    g_Task->unk_2C.half = 0;
    g_Task->unk_2B      = 0;
    Actor_SelectScript(1U);
    g_Task->header.step += 1;
}

MATCH void func_801EF7A4(void) {
    Actor_StepAnimOnce();
    if (Actor_StepAnimOnce() != 0u) {
        g_Task->header.step = g_Task->header.step + 2;
    }
}

MATCH void func_801EF7F4(void) {
    s32 value = -0x80;
    g_Task->unk_5D -= 4;
    g_Task->unk_5E -= 4;
    g_Task->unk_5F -= 4;
    Actor_StepAnimOnce();
    g_Task->unk_5D = value;
    g_Task->header.step += 1;
}

MATCH void Effect_TickDownAndClear2(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}
