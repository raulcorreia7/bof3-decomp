#include "magic220_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlots.h"

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEF78 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFBC(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F06E0, g_Task->header.step);
    if ((g_Task->header.flags & BMAGIC_EFFECT_IN_USE) != 0 && g_Task->header.step != 0) {
        func_8014D290();
        Effect_SetActiveActorMatrix();
        func_801EF9F0();
        BMagic_DrawDarkRing();
        PopMatrix();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EF078);

MATCH void func_801EF1F4(void) {
    u8 count;

    Actor_StepAnimOnce();
    g_Task->param.unk_0B += 0xC;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->unk_09 = 0x1E;
        g_Task->timer  = 3;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF294(void) {
    PartyMember* battler;
    PartyMember* work;
    u8           i;
    u8           slot;

    if (--g_Task->unk_09 == 0) {
        if (--g_Task->timer != 0) {
            for (i = 0; i < 16; i++) {
                slot = BMagic_AllocEffect();
                if (slot != GAME_NONE) {
                    battler                                = g_BattleEffectBattler;
                    BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                    BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                    BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
                    g_BattleEffectBattler->param.unk_0B += 1;
                }
            }
            if (g_Task->timer == 2) {
                SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 1));
            }
            SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 2));
            work         = g_Task;
            work->unk_09 = 4;
            work->unk_0C = 0x800;
            g_Task->header.step += 1;
        } else {
            g_AreaCameraRefreshCount = 93;
            g_Task->unk_09           = 60;
            g_Task->header.step      = 4;
        }
    }
}

MATCH void func_801EF40C(void) {
    if (g_FrameCount & 0x1) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed - g_Task->unk_0C;
    } else {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed - g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_0C;
    }
    if (--g_Task->unk_09 == 0) {
        g_Task->unk_09 = 8;
        g_Task->header.step--;
    }
}

/* Sways and spawns (MAGIC220_SWAY_AND_SPAWN), shakes the area camera with the
 * ticker's low bit and steps the handler at zero. */
MATCH void func_801EF4EC(void) {
    PartyMember* battler;
    u8           i;
    u8           slot;
    u8           timer;

    MAGIC220_SWAY_AND_SPAWN();
    if (g_Task->unk_09 & 0x1) {
        g_AreaCameraOffsetX = 16;
    } else {
        g_AreaCameraOffsetX = 0;
    }
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09 = 32;
        g_Task->header.step += 1;
    }
}

/* Sways and spawns (MAGIC220_SWAY_AND_SPAWN), shakes the area camera by half
 * the ticker on odd ticks and steps the handler at zero. */
MATCH void func_801EF6B8(void) {
    PartyMember* battler;
    u8           i;
    u8           slot;
    u8           timer;

    MAGIC220_SWAY_AND_SPAWN();
    if (g_Task->unk_09 & 0x1) {
        g_AreaCameraOffsetX = g_Task->unk_09 >> 1;
    } else {
        g_AreaCameraOffsetX = 0;
    }
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_AreaCameraOffsetX = 0;
        g_Task->unk_09      = 8;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

MATCH void func_801EF8CC(void) {
    s8 count;

    count = g_Task->unk_5D;
    if (count != 0) {
        g_Task->unk_5D = count - 2;
    }
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

MATCH void func_801EF9F0(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1) {
        tpage = 0x125;
    } else if (GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->param.unk_0B;
    D_1F800000.view.effect.params[5] = LOB(g_Task->unk_5D) * 4;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vz                 = 0;
    D_1F800014[1].vz                 = 0;
    D_1F800014[0].vz                 = 0;

    for (i = 1; i <= 64; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 6), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 6), D_1F800000.view.effect.params[0]);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        setRGB1(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        setRGB2(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
}

#include "overlays/bmagic/BMagic_DarkRingQuads.h"

/* func_801EFC40 */
MATCH void BMagic_DrawDarkRing(void) {
    GFX_AddDitheredDrawMode(5, getTPage(0, 2, 320, 256));
    D_1F800000.view.effect.params[0] = g_Task->param.unk_0B;
    D_1F800000.view.effect.params[1] = g_Task->param.unk_0B * 2;
    D_1F800000.view.effect.params[5] = (s8)g_Task->unk_5D * 4;
    BMAGIC_DRAW_DARK_RING_QUADS(5, 5);
}

MATCH void func_801EFF60(void) {
    SYS_DISPATCH_TASK(D_801F0700, 1, g_Task);
}

MATCH void func_801EFFA4(void) {
    SYS_DISPATCH_BYTE(D_801F0704, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F0334();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F002C);

INCLUDE_ASM(func_801F010C);

MATCH void func_801F01C8(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell  = &D_1F800004;
    phase       = g_Task->param.unk_0B;
    *angle_cell = phase << 8;
    g_Task->pos.x.fixed += rsin((s16)(phase << 8)) * 2;
    g_Task->pos.y.fixed += rcos(*angle_cell) * 2;
    count         = g_Task->timer - 2;
    g_Task->timer = count;
    if (count == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* Draw the magic220 glow as a textured diamond around the effect, its shade set by the timer. */
MATCH void func_801F0334(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    D_1F800000.view.effect.params[0] = 0x100;
    D_1F800000.view.effect.params[5] = g_Task->timer * 6;
    D_1F800014[0].vx                 = FIXED_MUL(rcos(ANGLE_45), D_1F800000.view.effect.params[0]);
    D_1F800014[0].vy                 = FIXED_MUL(rsin(ANGLE_45), D_1F800000.view.effect.params[0]);
    D_1F800014[0].vz                 = 0;
    D_1F800014[1].vx                 = FIXED_MUL(rcos(1536), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = FIXED_MUL(rsin(1536), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vz                 = 0;
    D_1F800014[2].vx                 = FIXED_MUL(rcos(3584), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rsin(3584), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vz                 = 0;
    D_1F800014[3].vx                 = FIXED_MUL(rcos(2560), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vy                 = FIXED_MUL(rsin(2560), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vz                 = 0;
    prim->tpage                      = GetTPage(0, 1, 832, 256);
    prim->clut                       = GetClut(0, 482);
    prim->u0                         = 0;
    prim->v0                         = 128;
    prim->u1                         = 32;
    prim->v1                         = 128;
    prim->u2                         = 0;
    prim->v2                         = 160;
    prim->u3                         = 32;
    prim->v3                         = 160;
    setRGB0(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[5]);
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}

/* func_801F0628 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F068C */
#include "overlays/bmagic/Actor_Clear.h"
