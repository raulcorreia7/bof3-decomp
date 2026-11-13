#include "magic167_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

/* Copies the selected battler's pose into the effect, spawns one battle effect
 * at that position and eight more in a four-column grid, and queues the
 * selection sound. */
MATCH void func_801EEC94(void) {
    PartyMember* battler;
    PartyMember* target;
    u32          first_slot;
    u8           i;
    u8           slot;

    battler              = g_BattleSelectedActor;
    g_Task->facing       = battler->facing;
    g_Task->pos.x        = battler->pos.x;
    g_Task->pos.y        = battler->pos.y;
    g_Task->pos.z        = battler->pos.z;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 16;
    g_Task->header.mode += 1;
    first_slot                                   = Battle_AllocEffect(1, 0x47) & BYTE_MASK;
    g_BattleEffects[first_slot].target.party     = g_Task;
    g_BattleEffects[first_slot].header.mode      = 0;
    g_BattleEffects[first_slot].arg.unk_09       = 0;
    g_BattleEffects[first_slot].pos.x            = g_Task->pos.x;
    g_BattleEffects[first_slot].pos.y            = g_Task->pos.y;
    COORD_INT(g_BattleEffects[first_slot].pos.z) = COORD_INT(g_Task->pos.z);
    g_Task->param.unk_0B += 1;
    i = 0;
    do {
        slot                               = Battle_AllocEffect(1, 0x47);
        target                             = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = (i & 0x3) * 8;
        g_BattleEffects[slot].arg.unk_09   = ((i >> 2) * 40) + 17;
        g_BattleEffects[slot].target.party = target;
        g_BattleEffects[slot].pos.x        = g_Task->pos.x;
        g_BattleEffects[slot].pos.y        = g_Task->pos.y;
        g_BattleEffects[slot].pos.z        = g_Task->pos.z;
        g_Task->param.unk_0B += 1;
        i++;
    } while (i < 8);
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

/* func_801EEE88 */
#include "overlays/bmagic/Effect_PreparePalette.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

#include "overlays/bmagic/Effect_Pause.h"

INCLUDE_ASM(func_801EF080);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* func_801EF2D8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF31C(void) {
    SYS_DISPATCH_BYTE(D_801F08B8, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        D_1F800004 = g_Task->unk_09 * 5;
        func_801EF4B0();
        func_801EF708();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF4B0);

INCLUDE_ASM(func_801EF708);

MATCH void func_801EF9B8(void) {
    SYS_DISPATCH_BYTE(D_801F08C4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        if (g_Task->header.step < 3) {
            func_801EFC44();
        }
        func_801F05C8(2);
        func_801F05C8(3);
        PopMatrix();
    }
}

MATCH void func_801EFA70(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->timer       = 1;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EFACC(void) {
    u8 timer;

    g_Task->param.unk_0B += 2;
    g_Task->unk_09 += 1;
    timer = g_Task->timer;
    if (timer < 16U) {
        g_Task->timer = timer + 1;
    }
    if (g_Task->unk_09 == 0x18) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFB5C(void) {
    g_Task->param.unk_0B += 2;
    g_Task->unk_09 += 1;
    g_Task->timer -= 1;
    if (g_Task->unk_09 == 0x28) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFBE4(void) {
    PartyMember* work;
    u8           next;

    work        = g_Task;
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0x18) {
        g_BattleEffectBattler->param.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EFC44);

INCLUDE_ASM(func_801F05C8);
