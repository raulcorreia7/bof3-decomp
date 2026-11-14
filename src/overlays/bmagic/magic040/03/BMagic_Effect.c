#include "magic040_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC80(void) {
    PartyMember* battler;
    PartyMember* work;
    PartyMember* task;
    PartyMember* owner;
    u16*         dst;
    u16*         src;
    u8           slot;
    u8           i;

    g_Task->facing = g_BattleEffectBattler->facing;
    battler        = g_BattleEffectBattler;
    work           = g_Task;
    WorldPos_Copy(&work->pos, &battler->pos);
    work->param.unk_0B = 0;
    g_Task->header.mode++;
    slot                               = Battle_AllocEffect(1, 60);
    task                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = task;
    g_Task->param.unk_0B++;
    slot                               = Battle_AllocEffect(1, 60);
    owner                              = g_Task;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].target.party = owner;
    g_Task->param.unk_0B++;
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    do {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
        i++;
    } while (i < 16);
    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(0x100);
}

INCLUDE_ASM(func_801EEDFC);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEF48 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF8C(void) {
    Magic040Steps handlers = D_801EEC10;
    u8            next_09;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if ((g_Task->header.flags & BMAGIC_EFFECT_IN_USE) != 0 && g_Task->header.step != 0) {
        func_801EF7FC();
        func_801EF600(g_Task->unk_09, g_Task->timer * 3);
        next_09 = g_Task->unk_09 + 4;
        func_801EF600(next_09, g_Task->timer * 2);
    }
}

MATCH void func_801EF074(void) {
    g_Task->facing      = BATTLE_ACTIVE_WORK->facing;
    g_Task->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed;
    g_Task->pos.z.fixed = BATTLE_ACTIVE_WORK->pos.z.fixed;
    func_801EF430(g_Task);
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;
    g_Task->header.step += 1;
}

#include "overlays/bmagic/Effect_CountUpTimersAndStep.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt32.h"

/* func_801EF1D0 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

void func_801EF388(void);

MATCH void func_801EF248(void) {
    Callback handlers[2] = {func_801EF2D8, func_801EF388};

    handlers[g_Task->header.step]();
    if (g_Task->header.flags & 0x1) {
        if (g_Task->header.step != 0) {
            func_801EFA3C();
        }
    }
}

MATCH void func_801EF2D8(void) {
    g_Task->facing      = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    func_801EF430(g_Task);
    g_Task->param.unk_0B = 0xB;
    g_Task->unk_09       = 0;
    g_Task->timer        = 128;
    g_Task->header.step += 1;
}

MATCH void func_801EF388(void) {
    g_Task->param.unk_0B -= 1;
    g_Task->unk_09 += g_Task->param.unk_0B;
    g_Task->timer -= 12;
    if (g_Task->param.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_OffsetByTargetPose.h"

MATCH void func_801EF430(void* task) {
    PartyMember* work;
    u32          slot;
    u8           kind;

    EFFECT_OFFSET_BY_TARGET_POSE(D_801EFD24, D_801EFCCC, D_801EFC74);
}

MATCH void func_801EF600(u8 start, u16 radius) {
    LINE_G2* line;
    s32      tpage;
    u8       i;

    D_1F800000.view.effect.params[0] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[1] = g_Task->unk_30.half;
    tpage                            = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    GFX_AddDitheredDrawMode(3, tpage);
    for (i = start; i < start + 32; i += 8) {
        line = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(line);
        SetSemiTrans(line, 1);
        D_1F800000.view.effect.params[4] = (i & 0x1F) << 7;
        setXY2(line, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[0] + ((rcos(D_1F800000.view.effect.params[4]) * radius) >> 12),
               D_1F800000.view.effect.params[1] + ((rsin(D_1F800000.view.effect.params[4]) * radius) >> 12));
        line->r0 = 0x80;
        line->g0 = 0x70;
        line->b0 = 0x60;
        line->r1 = 1;
        line->g1 = 1;
        line->b1 = 1;
        GFX_AddPrim(3, sizeof(LINE_G2));
    }
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    GFX_AddDitheredDrawMode(3, tpage);
}

#include "overlays/bmagic/Effect_DrawGlowFan.h"

MATCH void func_801EF7FC(void) {
    POLY_G3* poly;
    s32      tpage;
    s32      i;

    EFFECT_DRAW_GLOW_FAN(g_Task->timer, 0x80);
}

INCLUDE_ASM(func_801EFA3C);
