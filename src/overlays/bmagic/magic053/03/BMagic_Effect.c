#include "magic053_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC10(void) {
    Magic053Steps handlers = D_801EEC04;
    PartyBattler* saved_task;
    PartyBattler* saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F0578[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyBattler*)&D_801F0578[i];
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

MATCH void func_801EF064(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF0A8(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801F0554, g_Task->header.step);
    if (g_Task->header.flags & 1) {
        if (g_Task->header.step != 0) {
            if (g_Task->header.step < 4) {
                func_800AF764();
                func_8014D290();
                Effect_SetActiveActorMatrix();
                func_801EF7E0();
                func_801EFA30();
                PopMatrix();
            }
        }
    }
    g_ScriptBank = 0x800D3800;
}

INCLUDE_ASM(func_801EF174);

INCLUDE_ASM(func_801EF420);

MATCH void func_801EF5C0(void) {
    s16* state;
    u16  var_v0;
    u8   temp_v0;

    func_8014DAEC();
    if (g_Task->unk_09 & 1) {
        state  = &g_AreaCameraAngle.vx;
        var_v0 = *state + 0x14;
    } else {
        state  = &g_AreaCameraAngle.vx;
        var_v0 = *state - 0x14;
    }
    *state         = var_v0;
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_AreaCameraAngle.vx = -0x2AAU;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF674(void) {
    u8 temp_v0;

    temp_v0 = g_Task->timer;
    if (temp_v0 != 0) {
        g_Task->timer = temp_v0 - 2;
    }
    if (func_8014DAEC() & 0xFF) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF6D8(void) {
    PartyBattler* work;

    if (g_Task->unk_04 == 0) {
        work               = (PartyBattler*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

INCLUDE_ASM(func_801EF7E0);

INCLUDE_ASM(func_801EFA30);

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
    s32  temp_v1;
    s16* angle = &D_1F800004;

    r                   = rand();
    temp_v1             = g_Task->param.unk_0B;
    g_Task->unk_0C      = (r & 7) + 8;
    *angle              = temp_v1 << 9;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(*angle) * g_Task->unk_0C);
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos(*angle) * g_Task->unk_0C);
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    g_Task->unk_09      = 8;
    g_Task->timer       = 0x10;
    g_Task->header.step += 1;
}

MATCH void func_801EFF24(void) {
    PartyBattler* task;
    s16*          angle_cell;
    s32           direction;
    s32           velocity;

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
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}
