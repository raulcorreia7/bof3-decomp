#include "magic115_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    PartyMember* actor;
    PartyMember* work;
    u32          slot;
    u8           i;
    u16*         dst;
    u16*         src;

    actor                              = g_Battle.selected_actor;
    BMAGIC_WORK->pos.x.fixed           = actor->pos.x.fixed;
    BMAGIC_WORK->pos.y.fixed           = actor->pos.y.fixed;
    BMAGIC_WORK->pos.z.fixed           = actor->pos.z.fixed;
    slot                               = Battle_AllocEffect(1, 48) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = work;
    GFX_PaletteFreeFadeTarget(actor);
    BMAGIC_WORK->timer = GFX_PaletteAllocFade(actor, 0, 0, 0, 1);
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i] = src[i] | PSX_COLOR_STP_BIT;
    }
    *MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW)) = *MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW));
    g_GfxPalettePending                                               = 1;
    SND_SEQueueSelection(0x100);
    BMAGIC_WORK->param.unk_0B = 1;
    BMAGIC_WORK->unk_09       = 0;
    BMAGIC_WORK->header.mode++;
}

MATCH void func_801EEDDC(void) {
    g_PaletteFades[BMAGIC_WORK->timer].offset.r = BMAGIC_WORK->unk_09 * 2;
    g_PaletteFades[BMAGIC_WORK->timer].offset.g = BMAGIC_WORK->unk_09 * 2;
    g_PaletteFades[BMAGIC_WORK->timer].offset.b = BMAGIC_WORK->unk_09 * 2;
    if (BMAGIC_WORK->unk_09 >= 6) {
        BMAGIC_WORK->header.mode++;
    }
}

MATCH void func_801EEEB0(void) {
    if (g_FrameCount & 1) {
        g_PaletteFades[BMAGIC_WORK->timer].offset.r -= 1;
        g_PaletteFades[BMAGIC_WORK->timer].offset.g -= 1;
        g_PaletteFades[BMAGIC_WORK->timer].offset.b -= 1;
    }
    if (g_PaletteFades[BMAGIC_WORK->timer].offset.r == 0) {
        GFX_PaletteFreeFade(BMAGIC_WORK->timer);
        BMAGIC_WORK->header.mode++;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF054 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF098(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8C0 + 1, BMAGIC_WORK->header.step);
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF130(void) {
    BMAGIC_WORK->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed;
    BMAGIC_WORK->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed;
    BMAGIC_WORK->pos.z.part.integer = g_BattleEffectBattler->pos.z.part.integer + 0x2C0;
    BMAGIC_WORK->unk_25             = 0x1D;
    BMAGIC_WORK->unk_26             = 0;
    BMAGIC_WORK->scale.x            = 0x10000;
    BMAGIC_WORK->scale.y            = 0x10000;
    BMAGIC_WORK->unk_48             = 1;
    BMAGIC_WORK->unk_27             = 0xA0;
    BMAGIC_WORK->unk_28             = 0;
    BMAGIC_WORK->unk_24             = 4;
    BMAGIC_WORK->unk_5D             = 0;
    BMAGIC_WORK->unk_5E             = 0;
    BMAGIC_WORK->unk_5F             = 0;
    BMAGIC_WORK->unk_5C             = 0;
    BMAGIC_WORK->unk_2A             = 0;
    BMAGIC_WORK->unk_29             = 4;
    BMAGIC_WORK->unk_2C.value       = 0;
    BMAGIC_WORK->unk_2B             = 0;
    Script_Select(0U);
    BMAGIC_WORK->unk_09 = 0xFF;
    BMAGIC_WORK->header.step += 1;
}

MATCH void func_801EF27C(void) {
    s32          angle;
    s32*         angle_cell;
    u8           count;
    u32          slot;
    s8           tint;
    PartyMember* battler;

    Script_AnimStepLoop();
    count                    = BMAGIC_WORK->unk_09 + 1;
    BMAGIC_WORK->unk_09      = count;
    angle                    = (count & 0x3F) << 6;
    angle_cell               = &g_ScratchPad.cells.words[0];
    *angle_cell              = angle;
    BMAGIC_WORK->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin(angle) * 0xC000) >> 12);
    BMAGIC_WORK->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle_cell) * 0xC000) >> 12);
    if ((BMAGIC_WORK->unk_09 & 7) == 0) {
        slot                               = Battle_AllocEffect(1, 48) & BYTE_MASK;
        battler                            = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = battler;
        g_BattleEffects[slot].arg.unk_09   = (BMAGIC_WORK->unk_09 & 0xFC) + 8;
        g_BattleEffects[slot].pos.x.fixed  = BMAGIC_WORK->pos.x.fixed;
        g_BattleEffects[slot].pos.y.fixed  = BMAGIC_WORK->pos.y.fixed;
        g_BattleEffects[slot].pos.z.fixed  = BMAGIC_WORK->pos.z.fixed;
        g_BattleEffectBattler->unk_09++;
        g_BattleEffectBattler->param.unk_0B++;
    }
    if (BMAGIC_WORK->unk_09 == 0x40) {
        BMAGIC_WORK->header.flags |= 0x20;
        BMAGIC_WORK->unk_5C = 1;
        tint                = -0x40;
        BMAGIC_WORK->unk_5D = tint;
        BMAGIC_WORK->unk_5E = tint;
        BMAGIC_WORK->unk_5F = tint;
        BMAGIC_WORK->header.step++;
    }
}

MATCH void func_801EF49C(void) {
    s32  value = -0x80;
    s32* d;
    u8   tick;

    BMAGIC_WORK->unk_5D -= 4;
    BMAGIC_WORK->unk_5E -= 4;
    BMAGIC_WORK->unk_5F -= 4;
    Script_AnimStepLoop();
    tick                     = BMAGIC_WORK->unk_09 + 1;
    BMAGIC_WORK->unk_09      = tick;
    d                        = &g_ScratchPad.cells.words[0];
    d[0]                     = BMAGIC_PHASE_ANGLE(tick & BMAGIC_PHASE_MASK);
    BMAGIC_WORK->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + FIXED_MUL(rsin(d[0]), 0xC000);
    BMAGIC_WORK->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + FIXED_MUL(rcos(d[0]), 0xC000);
    BMAGIC_WORK->unk_5D      = value;
    BMAGIC_WORK->header.step += 1;
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"

MATCH void func_801EF5F8(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8D0 + 1, BMAGIC_WORK->header.step);
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF690(void) {
    BMAGIC_WORK->unk_25       = 0x1D;
    BMAGIC_WORK->unk_26       = 0;
    BMAGIC_WORK->scale.x      = 0x10000;
    BMAGIC_WORK->scale.y      = 0x10000;
    BMAGIC_WORK->unk_48       = 1;
    BMAGIC_WORK->unk_27       = 0xA0;
    BMAGIC_WORK->unk_28       = 0;
    BMAGIC_WORK->unk_24       = 4;
    BMAGIC_WORK->unk_5D       = 0;
    BMAGIC_WORK->unk_5E       = 0;
    BMAGIC_WORK->unk_5F       = 0;
    BMAGIC_WORK->unk_5C       = 0;
    BMAGIC_WORK->unk_2A       = 0;
    BMAGIC_WORK->unk_29       = 4;
    BMAGIC_WORK->unk_2C.value = 0;
    BMAGIC_WORK->unk_2B       = 0;
    Script_Select(1U);
    BMAGIC_WORK->header.step += 1;
}

MATCH void func_801EF7A4(void) {
    Script_AnimStepOnce();
    if (Script_AnimStepOnce() != 0u) {
        BMAGIC_WORK->header.step = BMAGIC_WORK->header.step + 2;
    }
}

MATCH void func_801EF7F4(void) {
    s32 value = -0x80;
    BMAGIC_WORK->unk_5D -= 4;
    BMAGIC_WORK->unk_5E -= 4;
    BMAGIC_WORK->unk_5F -= 4;
    Script_AnimStepOnce();
    BMAGIC_WORK->unk_5D = value;
    BMAGIC_WORK->header.step += 1;
}

MATCH void Effect_TickDownAndClear2(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}
