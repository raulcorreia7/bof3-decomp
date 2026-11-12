#include "magic044_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEDA0);
}

MATCH void func_801EEC5C(void) {
    PartyMember* task;
    PartyMember* work;
    u16*         src;
    u16*         dst;
    u32          i;
    u8           slot;

    g_Task->facing = g_BattleEffectBattler->facing;
    task           = g_Task;
    WorldPos_Copy(&task->pos, &g_BattleEffectBattler->pos);
    task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 2; i++) {
        slot                               = Battle_AllocEffect(1, 6) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    i   = 1;
    src = MEM_PTR(u16, 0x80036C02u);
    dst = MEM_PTR(u16, 0x8003AC02u);
    for (; i < 16; i++) {
        *(dst + 32) = *(src + 32) | 0x8000;
        dst++;
        src++;
    }
    *MEM_PTR(u16, 0x8003AC40u) = 0;
    g_GfxPalettePending        = 1;
    SND_QueueSelectionFx(0x100);
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE00 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE44(void) {
    SYS_DISPATCH_BYTE(D_801F0A1C, g_Task->header.step);
    if (g_Task->unk_04 != 0) {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EF4E0();
        }
    } else {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EFA4C();
        }
    }
}

INCLUDE_ASM(func_801EEEFC);

INCLUDE_ASM(func_801EF138);

INCLUDE_ASM(func_801EF320);

/* func_801EF478 */
#include "overlays/bmagic/Effect_FinishTrail.h"

INCLUDE_ASM(func_801EF4E0);

INCLUDE_ASM(func_801EFA4C);

/* func_801F02A0 */
#include "overlays/bmagic/Effect_RecordTrail.h"

/* func_801F0390 */
#include "overlays/bmagic/Effect_ClearTrail.h"

MATCH void func_801F0478(void) {
    SYS_DISPATCH_BYTE(D_801F0A2C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F06D8();
    }
}

MATCH void func_801F04F0(void) {
    func_800AF764();
    g_Task->unk_30.half += 8;
    g_Task->unk_5D = (RANDOM_MASK(3)) + 1;
    g_Task->unk_5E = (RANDOM_MASK(3)) + 1;
    g_Task->unk_5F = (RANDOM_MASK(3)) + 1;
    g_Task->unk_09 = 0;
    g_Task->timer  = 16;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801F05AC);

INCLUDE_ASM(func_801F0638);

INCLUDE_ASM(func_801F06D8);
