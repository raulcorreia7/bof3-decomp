#include "magic154_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC24.h"

INCLUDE_ASM(func_801EEC90);

INCLUDE_ASM(func_801EEE94);

MATCH void func_801EEFE0(void) {
    if (g_Task->unk_09 == 0) {
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->flags &= ~PARTY_BATTLER_FLAG_HANDLER_BUSY;
        func_800A9610(g_BattleTargetSelector, 0x10U);
        g_Task->mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF0C0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_Task)[1]);
}

INCLUDE_ASM(func_801EF104);

MATCH void func_801EF1EC(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->facing = D_801EB4E0->facing;
        g_Task->unk_0C = 0;
        g_Task->unk_10 = g_Task->unk_0B << 0xF;
        func_801DD350(g_Task);
        g_Task->coord_x_34.raw = D_801EB4E0->coord_x_34.raw + g_Task->unk_0C;
        g_Task->coord_y_38.raw = D_801EB4E0->coord_y_38.raw + g_Task->unk_10;
        g_Task->word_3C.word   = D_801EB4E0->word_3C.word;
        g_Task->unk_40         = 0x8000;
        g_Task->unk_44         = 0x8000;
        g_Task->unk_48         = 2;
        g_Task->unk_25         = 0x1D;
        g_Task->unk_26         = 0;
        g_Task->unk_27         = 0xA0;
        g_Task->unk_28         = 0;
        g_Task->unk_2A         = g_Task->facing & 1;
        g_Task->unk_29         = 3;
        g_Task->unk_24         = 4;
        g_Task->unk_2C.half    = 0;
        g_Task->unk_2B         = 0;
        Actor_SelectScript(0U);
        func_8014D978();
        g_Task->unk_09 = 0;
        g_Task->step += 1;
    }
}

MATCH void func_801EF380(void) {
    PartyBattler* work;
    u8            count;

    work = g_Task;
    work->unk_40 += 0x4000;
    count        = work->unk_09 + 1;
    work->unk_09 = count;
    work->unk_44 = work->unk_44 + 0x8000;
    if (count == 4) {
        g_Task->step++;
    }
}

MATCH void func_801EF3E4(void) {
    PartyBattler* work = g_Task;
    u8            timer;
    work->unk_40 -= 0x4000;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->unk_44 -= 0x8000;
    if (timer == 0) {
        D_801EB4E0->unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF454(void) {
    g_Task->unk_44 -= 0x1000;
    if ((s8)g_Task->unk_5F == -0x80) {
        D_801EB4E0->unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF4B4);

#include "overlays/bmagic/Effect_ReloadTimerAndStep.h"

MATCH void func_801EF58C(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & 0xFF)) {
        func_8014DAEC();
        func_800AFC98(2, 4);
        D_801EB4E0->unk_0B -= 1;
        g_Task->step += 1;
    } else if (func_8014DAEC() & 0xFF) {
        func_800AFC98(2, 4);
        g_Task->unk_09 = 0;
        D_801EB4E0->unk_0B -= 1;
        g_Task->step += 1;
    }
}

MATCH void func_801EF648(void) {
    if (func_8014DAEC() & BYTE_MASK) {
        BATTLE_ACTIVE_WORK->unk_09--;
        g_Task->step++;
    }
}

MATCH void func_801EF6AC(void) {
    func_801E5988();
}
