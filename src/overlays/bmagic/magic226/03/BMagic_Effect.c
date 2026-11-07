#include "magic226_03.h"
#include "sys/scene.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF004(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

INCLUDE_ASM(func_801EF048);

INCLUDE_ASM(func_801EF10C);

INCLUDE_ASM(func_801EF310);

#define BMAGIC_CAMERA_SWING_TICKS 0x3C
#include "overlays/bmagic/Effect_SwingCameraAngle.h"

#include "../../Effect_StartTint.h"

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

INCLUDE_ASM(func_801EFA64);

MATCH void func_801EFD84(void) {
    SYS_DISPATCH_TASK(D_801F0C60, 1, g_Task);
}

MATCH void func_801EFDC8(void) {
    SYS_DISPATCH_BYTE(D_801F0C78, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_800AF764();
        func_801F01B8();
    }
}

INCLUDE_ASM(func_801EFE48);

INCLUDE_ASM(func_801EFF88);

INCLUDE_ASM(func_801F00B0);

INCLUDE_ASM(func_801F01B8);

MATCH void func_801F04D4(void) {
    SYS_DISPATCH_BYTE(D_801F0C84, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F07D4();
        PopMatrix();
    }
}

/* blocker: candidate is 4 bytes short (0xBC against 0xC0); retail reloads g_Task before the timer and step stores; first diff: the bnez target at 0x801F057C. */
INCLUDE_ASM(func_801F055C);

/* blocker: source pointer register; first diff: lui a2 (retail) against lui a3 (candidate). */
/* blocker: source pointer register; first diff: lui a2 (retail) against lui a3 (candidate). */
INCLUDE_ASM(func_801F061C);

MATCH void func_801F068C(void) {
    PartyBattler* battler;
    PartyBattler* task;

    g_Task->unk_09 += 1;
    g_Task->timer -= 2;
    battler = g_BattleEffectBattler;
    task = g_Task;
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
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}
