#include "magic226_03.h"
#include "sys/scene.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlots.h"

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF004 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF048(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0C44, g_Task->header.step);
    if ((g_Task->header.flags & BMAGIC_EFFECT_IN_USE) != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_8014D290();
        Effect_SetActiveActorMatrix();
        func_801EF814();
        BMagic_DrawDarkRing();
        PopMatrix();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EF10C);

INCLUDE_ASM(func_801EF310);

/* func_801EF540 */
MATCH void Effect_SwingCameraAngle(void) {
    BMAGIC_SWING_CAMERA(60);
}

#include "overlays/bmagic/Effect_StartTint.h"

MATCH void func_801EF698(void) {
    u8 timer_next;

    timer_next = g_Task->timer;
    if (timer_next != 0) {
        g_Task->timer = timer_next - 2;
    }
    g_Task->unk_5D -= 8;
    g_Task->unk_5E -= 8;
    g_Task->unk_5F -= 8;
    if ((s8)g_Task->unk_5D == -0x80) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

INCLUDE_ASM(func_801EF814);

#include "overlays/bmagic/BMagic_DrawDarkRing.h"

MATCH void func_801EFD84(void) {
    SYS_DISPATCH_TASK(D_801F0C60, 1, g_Task);
}

MATCH void func_801EFDC8(void) {
    SYS_DISPATCH_BYTE(D_801F0C78, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801F01B8();
    }
}

INCLUDE_ASM(func_801EFE48);

/* Moves the effect in a circle of radius 2 around its origin by the angle byte 0x0B, arcs it in z with its
 * velocity, and relaunches the arc every 16 frames from the rise speed the ticker picks. */
MATCH void func_801EFF88(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell  = &D_1F800004;
    phase       = (g_Task->param.unk_0B - 2) & 0xF;
    /* kept: (s16) types the rsin angle; without it GCC loads the ticker into a0 and the body is 4 bytes short. */
    *angle_cell = phase << 8;
    g_Task->pos.x.fixed += rsin((s16)(phase << 8)) * 2;
    g_Task->pos.y.fixed += rcos(*angle_cell) * 2;
    g_Task->pos.z.fixed += g_Task->unk_14;
    g_Task->unk_14 += g_Task->unk_20;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->unk_14 = D_801F0C68[g_Task->param.unk_0B & 0x3];
        g_Task->unk_20 = -(g_Task->unk_14 / 8);
        g_Task->unk_09 = 16;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801F00B0);

MATCH void func_801F01B8(void) {
    POLY_FT4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[5] = (s8)g_Task->unk_5E * 6;
    D_1F800000.view.effect.params[0] = g_Task->timer;
    prim                             = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    prim->x0    = g_Task->unk_2E.half + FIXED_MUL(rcos(512), D_1F800000.view.effect.params[0]);
    prim->y0    = g_Task->unk_30.half + FIXED_MUL(rsin(512), D_1F800000.view.effect.params[0]);
    prim->x1    = g_Task->unk_2E.half + FIXED_MUL(rcos(1536), D_1F800000.view.effect.params[0]);
    prim->y1    = g_Task->unk_30.half + FIXED_MUL(rsin(1536), D_1F800000.view.effect.params[0]);
    prim->x2    = g_Task->unk_2E.half + FIXED_MUL(rcos(3584), D_1F800000.view.effect.params[0]);
    prim->y2    = g_Task->unk_30.half + FIXED_MUL(rsin(3584), D_1F800000.view.effect.params[0]);
    prim->x3    = g_Task->unk_2E.half + FIXED_MUL(rcos(2560), D_1F800000.view.effect.params[0]);
    prim->y3    = g_Task->unk_30.half + FIXED_MUL(rsin(2560), D_1F800000.view.effect.params[0]);
    prim->tpage = GetTPage(0, 1, 832, 256);
    prim->clut  = GetClut(0, 482);
    prim->u0    = 0;
    prim->v0    = 128;
    prim->u1    = 32;
    prim->v1    = 128;
    prim->u2    = 0;
    prim->v2    = 160;
    prim->u3    = 32;
    prim->v3    = 160;
    prim->r0    = g_Task->unk_5D + D_1F800000.view.effect.params[5];
    prim->g0    = D_1F800000.view.effect.params[5];
    prim->b0    = D_1F800000.view.effect.params[5];
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}

MATCH void func_801F04D4(void) {
    SYS_DISPATCH_BYTE(D_801F0C84, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F07D4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F055C);

INCLUDE_ASM(func_801F061C);

MATCH void func_801F068C(void) {
    PartyMember* battler;
    PartyMember* task;

    g_Task->unk_09 += 1;
    g_Task->timer -= 2;
    battler           = g_BattleEffectBattler;
    task              = g_Task;
    task->pos.x.fixed = battler->pos.x.fixed;
    task->pos.y.fixed = battler->pos.y.fixed;
    task->pos.z.fixed -= task->unk_14;
    if (task->timer == 0) {
        battler->unk_04 -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F07D4);

/* func_801F0B8C */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0BF0 */
#include "overlays/bmagic/Actor_Clear.h"
