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
    TASK(PartyMember)->pos.x.fixed     = actor->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed     = actor->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed     = actor->pos.z.fixed;
    slot                               = Battle_AllocEffect(1, 48) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = work;
    GFX_PaletteFreeFadeTarget(actor);
    TASK(PartyMember)->timer = GFX_PaletteAllocFade(actor, 0, 0, 0, 1);
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i] = src[i] | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0];
    g_GfxPalettePending                                          = 1;
    SND_SEQueueSelection(0x100);
    TASK(PartyMember)->param.unk_0B = 1;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->header.mode++;
}

MATCH void func_801EEDDC(void) {
    g_PaletteFades[TASK(PartyMember)->timer].offset.r = TASK(PartyMember)->unk_09 * 2;
    g_PaletteFades[TASK(PartyMember)->timer].offset.g = TASK(PartyMember)->unk_09 * 2;
    g_PaletteFades[TASK(PartyMember)->timer].offset.b = TASK(PartyMember)->unk_09 * 2;
    if (TASK(PartyMember)->unk_09 >= 6) {
        TASK(PartyMember)->header.mode++;
    }
}

MATCH void func_801EEEB0(void) {
    if (g_FrameCount & 1) {
        g_PaletteFades[TASK(PartyMember)->timer].offset.r -= 1;
        g_PaletteFades[TASK(PartyMember)->timer].offset.g -= 1;
        g_PaletteFades[TASK(PartyMember)->timer].offset.b -= 1;
    }
    if (g_PaletteFades[TASK(PartyMember)->timer].offset.r == 0) {
        GFX_PaletteFreeFade(TASK(PartyMember)->timer);
        TASK(PartyMember)->header.mode++;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF054 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF098(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8C0 + 1, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF130(void) {
    TASK(PartyMember)->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed;
    TASK(PartyMember)->pos.z.part.integer = g_BattleEffectBattler->pos.z.part.integer + 0x2C0;
    TASK(PartyMember)->unk_25             = 0x1D;
    TASK(PartyMember)->unk_26             = 0;
    TASK(PartyMember)->scale.x            = 0x10000;
    TASK(PartyMember)->scale.y            = 0x10000;
    TASK(PartyMember)->unk_48             = 1;
    TASK(PartyMember)->unk_27             = 0xA0;
    TASK(PartyMember)->unk_28             = 0;
    TASK(PartyMember)->unk_24             = 4;
    TASK(PartyMember)->unk_5D             = 0;
    TASK(PartyMember)->unk_5E             = 0;
    TASK(PartyMember)->unk_5F             = 0;
    TASK(PartyMember)->unk_5C             = 0;
    TASK(PartyMember)->unk_2A             = 0;
    TASK(PartyMember)->unk_29             = 4;
    TASK(PartyMember)->unk_2C.value       = 0;
    TASK(PartyMember)->unk_2B             = 0;
    Script_Select(0U);
    TASK(PartyMember)->unk_09 = 0xFF;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF27C(void) {
    s32          angle;
    s32*         angle_cell;
    u8           count;
    u32          slot;
    s8           tint;
    PartyMember* battler;

    Script_AnimStepLoop();
    count                          = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09      = count;
    angle                          = (count & 0x3F) << 6;
    angle_cell                     = &g_ScratchPad.cells.words[0];
    *angle_cell                    = angle;
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin(angle) * 0xC000) >> 12);
    TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle_cell) * 0xC000) >> 12);
    if ((TASK(PartyMember)->unk_09 & 7) == 0) {
        slot                               = Battle_AllocEffect(1, 48) & BYTE_MASK;
        battler                            = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = battler;
        g_BattleEffects[slot].arg.unk_09   = (TASK(PartyMember)->unk_09 & 0xFC) + 8;
        g_BattleEffects[slot].pos.x.fixed  = TASK(PartyMember)->pos.x.fixed;
        g_BattleEffects[slot].pos.y.fixed  = TASK(PartyMember)->pos.y.fixed;
        g_BattleEffects[slot].pos.z.fixed  = TASK(PartyMember)->pos.z.fixed;
        g_BattleEffectBattler->unk_09++;
        g_BattleEffectBattler->param.unk_0B++;
    }
    if (TASK(PartyMember)->unk_09 == 0x40) {
        TASK(PartyMember)->header.flags |= 0x20;
        TASK(PartyMember)->unk_5C = 1;
        tint                      = -0x40;
        TASK(PartyMember)->unk_5D = tint;
        TASK(PartyMember)->unk_5E = tint;
        TASK(PartyMember)->unk_5F = tint;
        TASK(PartyMember)->header.step++;
    }
}

MATCH void func_801EF49C(void) {
    s32  value = -0x80;
    s32* d;
    u8   tick;

    TASK(PartyMember)->unk_5D -= 4;
    TASK(PartyMember)->unk_5E -= 4;
    TASK(PartyMember)->unk_5F -= 4;
    Script_AnimStepLoop();
    tick                           = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09      = tick;
    d                              = &g_ScratchPad.cells.words[0];
    d[0]                           = BMAGIC_PHASE_ANGLE(tick & BMAGIC_PHASE_MASK);
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + FIXED_MUL(rsin(d[0]), 0xC000);
    TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + FIXED_MUL(rcos(d[0]), 0xC000);
    TASK(PartyMember)->unk_5D      = value;
    TASK(PartyMember)->header.step += 1;
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"

MATCH void func_801EF5F8(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8D0 + 1, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF690(void) {
    TASK(PartyMember)->unk_25       = 0x1D;
    TASK(PartyMember)->unk_26       = 0;
    TASK(PartyMember)->scale.x      = 0x10000;
    TASK(PartyMember)->scale.y      = 0x10000;
    TASK(PartyMember)->unk_48       = 1;
    TASK(PartyMember)->unk_27       = 0xA0;
    TASK(PartyMember)->unk_28       = 0;
    TASK(PartyMember)->unk_24       = 4;
    TASK(PartyMember)->unk_5D       = 0;
    TASK(PartyMember)->unk_5E       = 0;
    TASK(PartyMember)->unk_5F       = 0;
    TASK(PartyMember)->unk_5C       = 0;
    TASK(PartyMember)->unk_2A       = 0;
    TASK(PartyMember)->unk_29       = 4;
    TASK(PartyMember)->unk_2C.value = 0;
    TASK(PartyMember)->unk_2B       = 0;
    Script_Select(1U);
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF7A4(void) {
    Script_AnimStepOnce();
    if (Script_AnimStepOnce() != 0u) {
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 2;
    }
}

MATCH void func_801EF7F4(void) {
    s32 value = -0x80;
    TASK(PartyMember)->unk_5D -= 4;
    TASK(PartyMember)->unk_5E -= 4;
    TASK(PartyMember)->unk_5F -= 4;
    Script_AnimStepOnce();
    TASK(PartyMember)->unk_5D = value;
    TASK(PartyMember)->header.step += 1;
}

MATCH void Effect_TickDownAndClear2(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}
