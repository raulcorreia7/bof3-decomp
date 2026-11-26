#include "magic042_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC18 */
MATCH void BMagic_BurstUpdate(void) {
    BMagic_DispatchTaskPair(BMagic_BurstInit, Effect_MarkDamagedOnZeroTick);
}

/* func_801EEC70 */
MATCH void BMagic_BurstInit(void) {
    u32 slot;

    TASK(PartyMember)->facing       = g_BattleEffectBattler->facing;
    TASK(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 62) & BYTE_MASK;
    g_BattleEffects[slot].target.party = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    TASK(PartyMember)->param.unk_0B += 1;
    SND_SEQueueSelection(0x100);
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEDA4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EEDE8 */
MATCH void BMagic_BurstFlareUpdate(void) {
    BMagicBurstFlareSteps handlers;

    handlers = g_BMagicBurstFlareSteps;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
    if (TASK(PartyMember)->header.flags & 0x1 && TASK(PartyMember)->header.step != 0) {
        BMagic_BurstDrawGlow();
        BMagic_BurstDrawRays(0, TASK(PartyMember)->unk_09);
        BMagic_BurstDrawSpokes(TASK(PartyMember)->param.unk_0B + 8, TASK(PartyMember)->timer);
        BMagic_BurstDrawSpokes(TASK(PartyMember)->param.unk_0B + 0x10, TASK(PartyMember)->timer);
        BMagic_BurstDrawSpokes(TASK(PartyMember)->param.unk_0B + 0x18, TASK(PartyMember)->timer);
    }
}

MATCH void func_801EEF08(void) {
    TASK(PartyMember)->facing      = g_BattleEffectBattler->facing;
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    func_801EF1B0();
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->timer        = 0;
    TASK(PartyMember)->header.step += 1;
}

/* func_801EEFB8 */
MATCH void BMagic_BurstFlareOpen(void) {
    PartyMember* work;

    work = TASK(PartyMember);
    work->param.unk_0B++;
    work = TASK(PartyMember);
    work->timer++;
    if (work->timer == 4) {
        work = TASK(PartyMember);
        work->header.step++;
    }
}

/* func_801EF024 */
MATCH void BMagic_BurstFlareLengthen(void) {
    PartyMember* work;

    work = TASK(PartyMember);
    work->param.unk_0B++;
    work = TASK(PartyMember);
    work->unk_09 += 8;
    if (work->unk_09 == 80) {
        work = TASK(PartyMember);
        work->header.step++;
    }
}

/* func_801EF090 */
MATCH void BMagic_BurstFlareGrow(void) {
    u8 timer;

    TASK(PartyMember)->param.unk_0B += 1;
    TASK(PartyMember)->unk_09 += 4;
    timer                    = TASK(PartyMember)->timer + 4;
    TASK(PartyMember)->timer = timer;
    if ((timer & BYTE_MASK) == 32) {
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EF118 */
MATCH void BMagic_BurstFlareEnd(void) {
    u8 count;
    u8 timer_next;

    TASK(PartyMember)->param.unk_0B += 1;
    count = TASK(PartyMember)->unk_09;
    if (count != 0) {
        TASK(PartyMember)->unk_09 = count - 0xC;
    }
    timer_next               = TASK(PartyMember)->timer - 4;
    TASK(PartyMember)->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_OffsetByTargetPose.h"

MATCH void func_801EF1B0(void) {
    PartyMember* work;
    u32          slot;
    u8           type;

    EFFECT_OFFSET_BY_TARGET_POSE(g_BMagicBurstFormTypes, g_BMagicBurstFormOffsets, g_BMagicBurstCharacterOffsets);
}

/* func_801EF380 */
MATCH void BMagic_BurstDrawRays(u8 start, u16 radius) {
    LINE_G2* line;
    s32      tpage;
    u8       i;

    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->screen_y.value;
    tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    for (i = start; i < start + 32; i += 16) {
        line = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(line);
        SetSemiTrans(line, 1);
        g_ScratchPad.cells.halves[4] = (i & 0x1F) << 7;
        setXY2(line, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[0] + ((rcos(g_ScratchPad.cells.halves[4]) * radius) >> 12),
               g_ScratchPad.cells.halves[1] + ((rsin(g_ScratchPad.cells.halves[4]) * radius) >> 12));
        setRGB0(line, 0xC0, 0xC0, 0xC0);
        setRGB1(line, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_G2));
        g_ScratchPad.cells.halves[2] = radius / 3 * 2;
        line                         = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(line);
        SetSemiTrans(line, 1);
        g_ScratchPad.cells.halves[4] = (i & 0x1F) << 7;
        setXY2(line, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1] - 1, g_ScratchPad.cells.halves[0] + ((rcos(g_ScratchPad.cells.halves[4]) * g_ScratchPad.cells.halves[2]) >> 12),
               g_ScratchPad.cells.halves[1] + ((rsin(g_ScratchPad.cells.halves[4]) * g_ScratchPad.cells.halves[2]) >> 12) - 1);
        setRGB0(line, 0x80, 0x80, 0x80);
        setRGB1(line, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_G2));
        line = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(line);
        SetSemiTrans(line, 1);
        g_ScratchPad.cells.halves[4] = (i & 0x1F) << 7;
        setXY2(line, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1] + 1, g_ScratchPad.cells.halves[0] + ((rcos(g_ScratchPad.cells.halves[4]) * g_ScratchPad.cells.halves[2]) >> 12),
               g_ScratchPad.cells.halves[1] + ((rsin(g_ScratchPad.cells.halves[4]) * g_ScratchPad.cells.halves[2]) >> 12) + 1);
        setRGB0(line, 0x80, 0x80, 0x80);
        setRGB1(line, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_G2));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

/* func_801EF71C */
MATCH void BMagic_BurstDrawSpokes(u8 start, u16 radius) {
    LINE_G2* line;
    s32      tpage;
    s16      i;

    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->screen_y.value;
    tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    for (i = start; i < start + 128; i += 32) {
        line = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(line);
        SetSemiTrans(line, 1);
        g_ScratchPad.cells.halves[4] = (i & 0x7F) << 5;
        setXY2(line, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[0] + ((rcos(g_ScratchPad.cells.halves[4]) * radius) >> 12),
               g_ScratchPad.cells.halves[1] + ((rsin(g_ScratchPad.cells.halves[4]) * radius) >> 12));
        setRGB0(line, 0x80, 0x80, 0x20);
        setRGB1(line, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_G2));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

#include "overlays/bmagic/shared/Effect_DrawGlowFan.h"

/* func_801EF920 */
MATCH void BMagic_BurstDrawGlow(void) {
    POLY_G3* poly;
    s32      tpage;
    s32      i;

    EFFECT_DRAW_GLOW_FAN((TASK(PartyMember)->timer >> 1) + (rand() & 3), 0x60);
}
