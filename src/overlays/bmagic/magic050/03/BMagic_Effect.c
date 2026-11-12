#include "magic050_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC10 */
#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

MATCH void func_801EEDF8(void) {
    s32 cue;
    s32 timer;
    u8  timer_next;

    timer = g_Task->unk_09;
    if (timer != 16) {
        if (timer < 17) {
            cue = 0x101;
            if (timer != 8) {
            } else {
                goto block_7;
            }
        } else {
            cue = 0x101;
            if (timer != 24) {
            } else {
                goto block_7;
            }
        }
    } else {
        cue = 0x102;
    block_7:
        SND_QueueSelectionFx(cue);
    }
    timer_next     = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer_next;
    if ((timer_next & BYTE_MASK) == 25) {
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEF08 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF4C(void) {
    SYS_DISPATCH_BYTE(D_801EFAF0, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Battle_ProjectRange();
        func_801EF1B0();
        func_801EF4C4();
        func_801EF898();
    }
}

INCLUDE_ASM(func_801EEFDC);

#include "overlays/bmagic/Effect_CountUpTimerByTwoAndStep.h"

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
