#include "magic050_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC10 */
#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

MATCH void func_801EEDF8(void) {
    s32 var_a0;
    s32 temp_v1;
    u8  temp_v1_2;

    temp_v1 = g_Task->unk_09;
    if (temp_v1 != 0x10) {
        if (temp_v1 < 0x11) {
            var_a0 = 0x101;
            if (temp_v1 != 8) {
            } else {
                goto block_7;
            }
        } else {
            var_a0 = 0x101;
            if (temp_v1 != 0x18) {
            } else {
                goto block_7;
            }
        }
    } else {
        var_a0 = 0x102;
    block_7:
        SND_QueueSelectionFx(var_a0);
    }
    temp_v1_2      = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v1_2;
    if ((temp_v1_2 & BYTE_MASK) == 0x19) {
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF08(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EEF4C(void) {
    SYS_DISPATCH_BYTE(D_801EFAF0, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        func_800AF764();
        func_801EF1B0();
        func_801EF4C4();
        func_801EF898();
    }
}

INCLUDE_ASM(func_801EEFDC);

#include "../../Effect_CountUpTimerByTwoAndStep.h"

MATCH void func_801EF138(void) {
    PartyMember* work;
    u8           count;

    work = g_Task;
    work->timer++;
    work         = g_Task;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF1B0);

INCLUDE_ASM(func_801EF4C4);

INCLUDE_ASM(func_801EF898);
