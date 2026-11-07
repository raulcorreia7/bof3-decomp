#include "magic068_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EED50);

MATCH void func_801EF44C(void) {
    u8 timer;

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 0x3E;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EF4A8(void) {
    func_801EF55C();
    if (g_InputPressed != 0) {
        g_Task->header.mode = 4;
    }
}

INCLUDE_ASM(func_801EF4EC);

INCLUDE_ASM(func_801EF55C);

MATCH void func_801EF73C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF780(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 1, 2, g_Task);
}

MATCH void func_801EF7C4(void) {
    g_Task->facing      = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x02000000;
    func_800AF764();
    SND_QueueSelectionFx(0x100);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0xF;
    g_Task->timer        = 3;
    g_Task->header.step += 1;
}

MATCH void func_801EF884(void) {
    u8 temp_v0;

    Effect_SetActorMatrix();
    func_801EFA48();
    PopMatrix();
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_Task->unk_09 = 0xF;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF908);

MATCH void func_801EF9D0(void) {
    u8 timer;

    Effect_SetActorMatrix();
    func_801EFA48();
    PopMatrix();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        BMAGIC_TICK_EFFECT_WORK();
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EFA48);

#include "overlays/bmagic/Effect_SetActorMatrix.h"
