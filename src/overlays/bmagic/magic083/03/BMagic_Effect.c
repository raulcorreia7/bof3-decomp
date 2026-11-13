#include "magic083_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlotsWithSetup.h"

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH s32 func_801EF0CC(void) {
    if (*((u8*)&g_Battle.action_type) != BATTLE_ACTION_ABILITY && *((u16*)&g_Battle.action_id) == 0x136) {
        g_Battle.action_id = ABILITY_SHIELD;
    }
    return 0;
}

/* func_801EF108 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF14C(void) {
    SYS_DISPATCH_BYTE(D_801F0EF0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFB24();
        func_801EF844();
        PopMatrix();
    }
}

MATCH void func_801EF1DC(void) {
    void* battler;
    u8    count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            battler = &g_BattleEnemyBattlers[g_Task->unk_03];
        } else {
            battler = &g_Game.members[g_Task->unk_03];
        }
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF2F8);

#include "overlays/bmagic/Effect_StepOnZeroTick.h"

INCLUDE_ASM(func_801EF55C);

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF844);

INCLUDE_ASM(func_801EFB24);

MATCH void func_801EFE54(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Task);
}

MATCH void func_801EFE98(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 2, g_Task);
}

INCLUDE_ASM(func_801EFEDC);

MATCH void func_801F0010(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;
    PartyMember* reset;

    Battle_ProjectRange();
    BMagic_SetXFixed((RANDOM_MASK(3)) | 0x18);
    Effect_SetActorMatrix();
    func_801F050C();
    PopMatrix();
    if (g_FrameCount & 0x1) {
        g_Task->unk_09 += 1;
    }
    task         = g_Task;
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        reset         = g_Task;
        reset->unk_14 = -0x10;
        reset->timer  = 8;
        reset->unk_20 = 4;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0104(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;

    Battle_ProjectRange();
    BMagic_SetXFixed((RANDOM_MASK(3)) | 0x18);
    Effect_SetActorMatrix();
    func_801F050C();
    PopMatrix();
    if (g_FrameCount & 0x1) {
        g_Task->unk_09 += 1;
    }
    task         = g_Task;
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        g_Task->timer = 28 - g_Task->param.unk_0B;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F01F8(void) {
    s32 value;
    s32 value2;
    s32 value3;
    u8  value4;
    u8  value5;

    Battle_ProjectRange();
    if ((g_Task->unk_0C == 4) && (g_Task->timer < 5U)) {
        value2 = (RANDOM_MASK(3)) | 0x40;
    } else {
        value2 = (RANDOM_MASK(3)) | 0x18;
    }
    BMagic_SetXFixed(value2);
    Effect_SetActorMatrix();
    func_801F050C();
    PopMatrix();
    if (g_Task->unk_0C < 4) {
        value          = g_Task->unk_10 + 1;
        g_Task->unk_10 = value;
        if (!(value & 0x7)) {
            g_Task->unk_0C += 1;
        }
    }
    g_Task->unk_09 += g_Task->unk_0C;
    if (g_Task->unk_0C == 4) {
        value4        = g_Task->timer - 1;
        g_Task->timer = value4;
        if (!(value4 & BYTE_MASK)) {
            value5 = g_Task->unk_03;
            if (!(value5 & 0xF0)) {
                value3 = 0x102;
                if (value5 & 0x1) {
                    value3 = 0x101;
                }
                SND_QueueSelectionFx(value3);
            }
            g_Task->unk_10 = 8;
            g_Task->unk_14 = 8;
            g_Task->unk_20 = 8;
            g_Task->header.step += 1;
        }
    }
}

INCLUDE_ASM(func_801F038C);

INCLUDE_ASM(func_801F050C);

INCLUDE_ASM(BMagic_SetXFixed);

/* func_801F0DC0 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0E24 */
#include "overlays/bmagic/Actor_Clear.h"
