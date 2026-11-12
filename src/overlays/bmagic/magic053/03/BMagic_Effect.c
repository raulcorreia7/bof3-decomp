#include "magic053_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC10(void) {
    Magic053Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F0578[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F0578[i];
            g_BattleEffectBattler = D_801F0578[i].target.party;
            func_801EFD50();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF064 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0A8(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0554, g_Task->header.step);
    if (g_Task->header.flags & 1) {
        if (g_Task->header.step != 0) {
            if (g_Task->header.step < 4) {
                Battle_ProjectRange();
                func_8014D290();
                Effect_SetActiveActorMatrix();
                func_801EF7E0();
                BMagic_DrawDarkRing();
                PopMatrix();
            }
        }
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EF174);

INCLUDE_ASM(func_801EF420);

MATCH void func_801EF5C0(void) {
    s16* state;
    u16  angle;
    u8   timer;

    Actor_StepAnimOnce();
    if (g_Task->unk_09 & 1) {
        state = &g_AreaCameraAngle.vx;
        angle = *state + 0x14;
    } else {
        state = &g_AreaCameraAngle.vx;
        angle = *state - 0x14;
    }
    *state         = angle;
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_AreaCameraAngle.vx = -0x2AAU;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF674(void) {
    u8 timer;

    timer = g_Task->timer;
    if (timer != 0) {
        g_Task->timer = timer - 2;
    }
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF6D8(void) {
    PartyMember* work;

    if (g_Task->unk_04 == 0) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

MATCH void func_801EF7E0(void) {
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
    D_1F800000.view.effect.params[5] = g_Task->timer << 2;
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

#include "overlays/bmagic/BMagic_DrawDarkRing.h"

MATCH void func_801EFD50(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Task);
}

MATCH void func_801EFD94(void) {
    SYS_DISPATCH_BYTE(D_801F056C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F01C0();
        PopMatrix();
    }
}

MATCH void func_801EFE1C(void) {
    s32  r;
    s32  direction;
    s16* angle = &D_1F800004;

    r                   = rand();
    direction           = g_Task->param.unk_0B;
    g_Task->unk_0C      = (r & 7) + 8;
    *angle              = direction << 9;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(*angle) * g_Task->unk_0C);
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos(*angle) * g_Task->unk_0C);
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    g_Task->unk_09      = 8;
    g_Task->timer       = 16;
    g_Task->header.step += 1;
}

MATCH void func_801EFF24(void) {
    PartyMember* task;
    s16*         angle_cell;
    s32          direction;
    s32          velocity;

    task       = g_Task;
    angle_cell = &D_1F800004;
    direction  = task->param.unk_0B;
    task->unk_0C += 2;
    *angle_cell         = direction << 9;
    velocity            = rsin((s16)(direction << 9)) * g_Task->unk_0C;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + velocity;
    velocity            = rcos(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + velocity;
    if (--g_Task->unk_09 == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0018(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B;
    g_Task->unk_0C += 1;
    *angle_cell         = phase << 9;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(phase << 9)) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    count               = g_Task->timer - 1;
    g_Task->timer       = count;
    if (count == 0) {
        g_BattleEffectBattler->unk_04 -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F01C0);

/* func_801F0494 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F04F8 */
#include "overlays/bmagic/Actor_Clear.h"
