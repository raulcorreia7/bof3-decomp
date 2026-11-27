#include "magic040_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC80(void) {
    PartyMember* battler;
    PartyMember* work;
    PartyMember* task;
    PartyMember* owner;
    u16*         dst;
    u16*         src;
    u8           slot;
    u8           i;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    battler                   = g_BattleEffectBattler;
    work                      = SELF(PartyMember);
    WorldPos_Copy(&work->pos, &battler->pos);
    work->param.unk_0B = 0;
    SELF(PartyMember)->header.mode++;
    slot                               = Battle_AllocEffect(1, 60);
    task                               = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = task;
    SELF(PartyMember)->param.unk_0B++;
    slot                               = Battle_AllocEffect(1, 60);
    owner                              = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].target.party = owner;
    SELF(PartyMember)->param.unk_0B++;
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    do {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
        i++;
    } while (i < 16);
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(0x100);
}

MATCH void func_801EEDFC(void) {
    PartyMember* work;
    u8           slot;

    if (SELF(PartyMember)->param.unk_0B != 0) {
        return;
    }
    if ((Battle_CanTarget(3, g_Battle.target_selector) & BYTE_MASK) != 0) {
        slot                               = Battle_AllocEffect(1, 72);
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].unk_04       = 3;
        g_BattleEffects[slot].arg.unk_09   = 1;
        g_BattleEffects[slot].unk_0A       = 0;
        g_BattleEffects[slot].target.party = work;
        SELF(PartyMember)->param.unk_0B += 1;
    } else {
        slot                               = Battle_AllocEffect(1, 72);
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].unk_04       = 8;
        g_BattleEffects[slot].arg.unk_09   = 1;
        g_BattleEffects[slot].unk_0A       = 0;
        g_BattleEffects[slot].target.party = work;
        SELF(PartyMember)->param.unk_0B += 1;
    }
    SELF(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EEF48 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF8C(void) {
    Magic040Steps handlers = D_801EEC10;
    u8            next_09;

    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if ((SELF(PartyMember)->header.flags & BMAGIC_EFFECT_IN_USE) != 0 && SELF(PartyMember)->header.step != 0) {
        func_801EF7FC();
        func_801EF600(SELF(PartyMember)->unk_09, SELF(PartyMember)->timer * 3);
        next_09 = SELF(PartyMember)->unk_09 + 4;
        func_801EF600(next_09, SELF(PartyMember)->timer * 2);
    }
}

MATCH void func_801EF074(void) {
    SELF(PartyMember)->facing      = BATTLE_ACTIVE_WORK->facing;
    SELF(PartyMember)->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed = BATTLE_ACTIVE_WORK->pos.z.fixed;
    func_801EF430(g_Self);
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->timer  = 0;
    SELF(PartyMember)->header.step += 1;
}

#include "overlays/bmagic/shared/Effect_CountUpTimersAndStep.h"

#include "overlays/bmagic/shared/Effect_CountUpAndStepAt32.h"

/* func_801EF1D0 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

void func_801EF388(void);

MATCH void func_801EF248(void) {
    Callback handlers[2] = {func_801EF2D8, func_801EF388};

    handlers[SELF(PartyMember)->header.step]();
    if (SELF(PartyMember)->header.flags & 0x1) {
        if (SELF(PartyMember)->header.step != 0) {
            BMagic_DrawShrinkingRing();
        }
    }
}

MATCH void func_801EF2D8(void) {
    SELF(PartyMember)->facing      = g_BattleEffectBattler->facing;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    func_801EF430(g_Self);
    SELF(PartyMember)->param.unk_0B = 0xB;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->timer        = 128;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF388(void) {
    SELF(PartyMember)->param.unk_0B -= 1;
    SELF(PartyMember)->unk_09 += SELF(PartyMember)->param.unk_0B;
    SELF(PartyMember)->timer -= 12;
    if (SELF(PartyMember)->param.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_OffsetByTargetPose.h"

MATCH void func_801EF430(void* task) {
    PartyMember* work;
    u32          slot;
    u8           type;

    EFFECT_OFFSET_BY_TARGET_POSE(D_801EFD24, D_801EFCCC, D_801EFC74);
}

MATCH void func_801EF600(u8 start, u16 radius) {
    LINE_G2* line;
    s32      tpage;
    u8       i;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->screen_y.value;
    tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    for (i = start; i < start + 32; i += 8) {
        line = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(line);
        SetSemiTrans(line, 1);
        g_ScratchPad.cells.halves[4] = (i & 0x1F) << 7;
        setXY2(line, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[0] + ((rcos(g_ScratchPad.cells.halves[4]) * radius) >> 12),
               g_ScratchPad.cells.halves[1] + ((rsin(g_ScratchPad.cells.halves[4]) * radius) >> 12));
        setRGB0(line, 0x80, 0x70, 0x60);
        setRGB1(line, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_G2));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

#include "overlays/bmagic/shared/Effect_DrawGlowFan.h"

MATCH void func_801EF7FC(void) {
    POLY_G3* poly;
    s32      tpage;
    s32      i;

    EFFECT_DRAW_GLOW_FAN(SELF(PartyMember)->timer, 0x80);
}

MATCH void BMagic_DrawShrinkingRing(void) {
    LINE_F2* line;
    s32      tpage;
    s32      i;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    i                            = 0;
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->screen_y.value;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->unk_09;
    for (i = 0; i < 32; i++) {
        line = (LINE_F2*)g_GfxPrimCursor;
        SetLineF2(line);
        SetSemiTrans(line, 1);
        g_ScratchPad.cells.halves[4] = i << 7;
        setXY0(line, g_ScratchPad.cells.halves[0] + ((rsin((s16)(i << 7)) * g_ScratchPad.cells.halves[2]) >> 12),
               g_ScratchPad.cells.halves[1] + ((rcos(g_ScratchPad.cells.halves[4]) * g_ScratchPad.cells.halves[2]) >> 12));
        g_ScratchPad.cells.halves[4] = (i + 1) << 7;
        line->x1                     = g_ScratchPad.cells.halves[0] + ((rsin((s16)((i + 1) << 7)) * g_ScratchPad.cells.halves[2]) >> 12);
        line->y1                     = g_ScratchPad.cells.halves[1] + ((rcos(g_ScratchPad.cells.halves[4]) * g_ScratchPad.cells.halves[2]) >> 12);
        setRGB0(line, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_F2));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}
