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
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_BATTLER_FLAG_HANDLER_BUSY;
        func_800A9610(g_BattleTargetSelector, 0x10U);
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF0C0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, TASK_BYTES[1]);
}

INCLUDE_ASM(func_801EF104);

MATCH void func_801EF1EC(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->facing = g_BattleEffectBattler->facing;
        g_Task->unk_0C = 0;
        g_Task->unk_10 = g_Task->param.unk_0B << 0xF;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        g_Task->scale.x     = 0x8000;
        g_Task->scale.y     = 0x8000;
        g_Task->unk_48      = 2;
        g_Task->unk_25      = 0x1D;
        g_Task->unk_26      = 0;
        g_Task->unk_27      = 0xA0;
        g_Task->unk_28      = 0;
        g_Task->unk_2A      = g_Task->facing & 1;
        g_Task->unk_29      = 3;
        g_Task->unk_24      = 4;
        g_Task->unk_2C.half = 0;
        g_Task->unk_2B      = 0;
        Actor_SelectScript(0U);
        func_8014D978();
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF380(void) {
    PartyBattler* work;
    u8            count;

    work = g_Task;
    work->scale.x += 0x4000;
    count        = work->unk_09 + 1;
    work->unk_09 = count;
    work->scale.y += 0x8000;
    if (count == 4) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF3E4(void) {
    PartyBattler* work = g_Task;
    u8            timer;
    work->scale.x -= 0x4000;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->scale.y -= 0x8000;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF454(void) {
    g_Task->scale.y -= 0x1000;
    if ((s8)g_Task->unk_5F == -0x80) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF4B4(void) {
    Magic154Steps handlers = D_801EEC14;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

#include "overlays/bmagic/Effect_SetDuration.h"

MATCH void func_801EF58C(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & 0xFF)) {
        func_8014DAEC();
        func_800AFC98(2, 4);
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    } else if (func_8014DAEC() & 0xFF) {
        func_800AFC98(2, 4);
        g_Task->unk_09 = 0;
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF648(void) {
    if (func_8014DAEC() & BYTE_MASK) {
        BATTLE_ACTIVE_WORK->unk_09--;
        g_Task->header.step++;
    }
}

MATCH void func_801EF6AC(void) {
    func_801E5988();
}
