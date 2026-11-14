#include "magic042_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    BMagic_DispatchTaskPair(func_801EEC70, func_801EED44);
}

MATCH void func_801EEC70(void) {
    u32 slot;

    g_Task->facing       = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 62) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_Task->param.unk_0B += 1;
    SND_QueueSelectionEffect(0x100);
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEDA4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEDE8(void) {
    Magic042Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
    if (g_Task->header.flags & 0x1 && g_Task->header.step != 0) {
        func_801EF920();
        func_801EF380(0, g_Task->unk_09);
        func_801EF71C(g_Task->param.unk_0B + 8, g_Task->timer);
        func_801EF71C(g_Task->param.unk_0B + 0x10, g_Task->timer);
        func_801EF71C(g_Task->param.unk_0B + 0x18, g_Task->timer);
    }
}

MATCH void func_801EEF08(void) {
    g_Task->facing      = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    func_801EF1B0();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EEFB8(void) {
    PartyMember* work;

    work = g_Task;
    work->param.unk_0B++;
    work = g_Task;
    work->timer++;
    if (work->timer == 4) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801EF024(void) {
    PartyMember* work;

    work = g_Task;
    work->param.unk_0B++;
    work = g_Task;
    work->unk_09 += 8;
    if (work->unk_09 == 80) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801EF090(void) {
    u8 timer;

    g_Task->param.unk_0B += 1;
    g_Task->unk_09 += 4;
    timer         = g_Task->timer + 4;
    g_Task->timer = timer;
    if ((timer & BYTE_MASK) == 32) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF118(void) {
    u8 count;
    u8 timer_next;

    g_Task->param.unk_0B += 1;
    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 0xC;
    }
    timer_next    = g_Task->timer - 4;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_OffsetByTargetPose.h"

MATCH void func_801EF1B0(void) {
    PartyMember* work;
    u32          slot;
    u8           kind;

    EFFECT_OFFSET_BY_TARGET_POSE(D_801EFC24, D_801EFBCC, D_801EFB74);
}

/* Draws rays out from the effect point at two angles, start and start + 16: a bright one of the full radius and a dimmer pair two thirds as long, one pixel above and below it. */
MATCH void func_801EF380(u8 start, u16 radius) {
    LINE_G2* line;
    s32      tpage;
    u8       i;

    D_1F800000.view.effect.params[0] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[1] = g_Task->unk_30.half;
    tpage                            = getTPage(0, 1, 320, 256);
    GFX_AddDitheredDrawMode(3, tpage);
    for (i = start; i < start + 32; i += 16) {
        line = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(line);
        SetSemiTrans(line, 1);
        D_1F800000.view.effect.params[4] = (i & 0x1F) << 7;
        setXY2(line, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[0] + ((rcos(D_1F800000.view.effect.params[4]) * radius) >> 12),
               D_1F800000.view.effect.params[1] + ((rsin(D_1F800000.view.effect.params[4]) * radius) >> 12));
        setRGB0(line, 0xC0, 0xC0, 0xC0);
        setRGB1(line, 1, 1, 1);
        GFX_AddPrim(3, sizeof(LINE_G2));
        D_1F800000.view.effect.params[2] = radius / 3 * 2;
        line                             = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(line);
        SetSemiTrans(line, 1);
        D_1F800000.view.effect.params[4] = (i & 0x1F) << 7;
        setXY2(line, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1] - 1,
               D_1F800000.view.effect.params[0] + ((rcos(D_1F800000.view.effect.params[4]) * D_1F800000.view.effect.params[2]) >> 12),
               D_1F800000.view.effect.params[1] + ((rsin(D_1F800000.view.effect.params[4]) * D_1F800000.view.effect.params[2]) >> 12) - 1);
        setRGB0(line, 0x80, 0x80, 0x80);
        setRGB1(line, 1, 1, 1);
        GFX_AddPrim(3, sizeof(LINE_G2));
        line = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(line);
        SetSemiTrans(line, 1);
        D_1F800000.view.effect.params[4] = (i & 0x1F) << 7;
        setXY2(line, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1] + 1,
               D_1F800000.view.effect.params[0] + ((rcos(D_1F800000.view.effect.params[4]) * D_1F800000.view.effect.params[2]) >> 12),
               D_1F800000.view.effect.params[1] + ((rsin(D_1F800000.view.effect.params[4]) * D_1F800000.view.effect.params[2]) >> 12) + 1);
        setRGB0(line, 0x80, 0x80, 0x80);
        setRGB1(line, 1, 1, 1);
        GFX_AddPrim(3, sizeof(LINE_G2));
    }
    tpage = getTPage(0, 0, 320, 256);
    GFX_AddDitheredDrawMode(3, tpage);
}

MATCH void func_801EF71C(u8 start, u16 radius) {
    LINE_G2* line;
    s32      tpage;
    s16      i;

    D_1F800000.view.effect.params[0] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[1] = g_Task->unk_30.half;
    tpage                            = getTPage(0, 1, 320, 256);
    GFX_AddDitheredDrawMode(3, tpage);
    for (i = start; i < start + 128; i += 32) {
        line = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(line);
        SetSemiTrans(line, 1);
        D_1F800000.view.effect.params[4] = (i & 0x7F) << 5;
        setXY2(line, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[0] + ((rcos(D_1F800000.view.effect.params[4]) * radius) >> 12),
               D_1F800000.view.effect.params[1] + ((rsin(D_1F800000.view.effect.params[4]) * radius) >> 12));
        setRGB0(line, 0x80, 0x80, 0x20);
        setRGB1(line, 1, 1, 1);
        GFX_AddPrim(3, sizeof(LINE_G2));
    }
    tpage = getTPage(0, 0, 320, 256);
    GFX_AddDitheredDrawMode(3, tpage);
}

#include "overlays/bmagic/Effect_DrawGlowFan.h"

MATCH void func_801EF920(void) {
    POLY_G3* poly;
    s32      tpage;
    s32      i;

    EFFECT_DRAW_GLOW_FAN((g_Task->timer >> 1) + (rand() & 3), 0x60);
}
