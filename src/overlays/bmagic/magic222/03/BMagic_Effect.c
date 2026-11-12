#include "magic222_03.h"
#include "sys/scene.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

#include "overlays/bmagic/Effect_CountDownTimerQueueFx.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEEE0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF24(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0D64, g_Task->header.step);
    if ((g_Task->header.flags & 0x1) && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EEFC8);

INCLUDE_ASM(func_801EF148);

/* func_801EF274 */
MATCH void Effect_SwingCameraAngle(void) {
    BMAGIC_SWING_CAMERA(22);
}

MATCH void func_801EF324(void) {
    u8           count;
    u32          slot;
    PartyMember* work;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        slot                               = Battle_AllocEffect(1, 96) & BYTE_MASK;
        work                               = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 3;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffectBattler->param.unk_0B += 1;
        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 1;
        g_Task->unk_5D = 0x40;
        g_Task->unk_5E = 0x40;
        g_Task->unk_5F = 0x40;
        g_Task->unk_09 = 12;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_StartTint.h"

MATCH void func_801EF4F0(void) {
    g_Task->unk_5D -= 0x10;
    g_Task->unk_5E -= 0x10;
    g_Task->unk_5F -= 0x10;
    g_Task->scale.x += 0x1800;
    if ((s8)g_Task->unk_5D == -0x80) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF5A4(void) {
    SYS_DISPATCH_BYTE(D_801F0D7C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF87C();
        BMagic_DrawDarkRing();
        PopMatrix();
    }
}

MATCH void func_801EF634(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--g_Task->unk_09 == 0) {
        src              = g_BattleEffectBattler;
        dst              = g_Task;
        dst->pos.x.fixed = src->pos.x.fixed;
        dst->pos.y.fixed = src->pos.y.fixed;
        dst->pos.z       = src->pos.z;
        dst->unk_14      = 0;
        dst->unk_09      = 0;
        g_Task->timer    = 38;
        g_Task->header.step++;
    }
}

MATCH void func_801EF6C8(void) {
    g_Task->unk_09 += 1;
    g_Task->unk_14 += 6;
    if (g_Task->unk_09 == 0x10) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF87C);

#include "overlays/bmagic/BMagic_DarkRingQuads.h"

/* func_801EFACC */
MATCH void BMagic_DrawDarkRing(void) {
    GFX_AddDitheredDrawMode(5, getTPage(0, 2, 320, 256));
    D_1F800000.view.effect.params[0] = g_Task->unk_14;
    D_1F800000.view.effect.params[1] = g_Task->unk_14 * 2;
    D_1F800000.view.effect.params[5] = g_Task->unk_09 * 4;
    BMAGIC_DRAW_DARK_RING_QUADS(5, 5);
}

MATCH void func_801EFDEC(void) {
    SYS_DISPATCH_BYTE(D_801F0D8C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F0168();
        func_801F0218();
        PopMatrix();
    }
}

MATCH void func_801EFE74(void) {
    s32  r;
    s32  phase;
    s16* angle = &D_1F800004;

    r                   = rand();
    phase               = g_Task->param.unk_0B;
    g_Task->unk_0C      = (r & 0x7) + 8;
    *angle              = phase << 9;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(*angle) * g_Task->unk_0C);
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos(*angle) * g_Task->unk_0C);
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    g_Task->unk_09      = 8;
    g_Task->timer       = 16;
    g_Task->header.step += 1;
}

MATCH void func_801EFF7C(void) {
    PartyMember* task;
    s16*         angle_cell;
    s32          direction;
    s32          velocity;

    task       = g_Task;
    angle_cell = &D_1F800004;
    direction  = task->param.unk_0B;
    task->unk_0C += 1;
    *angle_cell         = direction << 9;
    velocity            = rsin((s16)(direction << 9)) * g_Task->unk_0C;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + velocity;
    velocity            = rcos(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + velocity;
    if (--g_Task->unk_09 == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0070(void) {
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
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void Effect_SetActorMatrix3(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

INCLUDE_ASM(func_801F0218);

MATCH void func_801F0504(void) {
    SYS_DISPATCH_BYTE(D_801F0D98, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F07A8();
        func_801F07A8();
    }
}

INCLUDE_ASM(func_801F0584);

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void func_801F066C(void) {
    u8 timer;

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 16;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F06C8(void) {
    PartyMember* work;

    work = g_Task;
    work->param.unk_0B += 4;
    work = g_Task;
    work->timer--;
    if (work->timer == 0) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801F0730(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = g_Task;
    work->param.unk_0B += 4;
    work         = g_Task;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F07A8);
