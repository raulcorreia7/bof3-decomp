#include "magic075_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

INCLUDE_ASM(func_801EEDE0);

INCLUDE_ASM(func_801EEEB0);

/* func_801EEFF4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF038(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF7A0 + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF0D0(void) {
    s32          angle;
    s32*         angle_cell;
    u8           count;
    PartyMember* work;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        angle                      = (g_Task->param.unk_0B & 0x7) << 9;
        angle_cell                 = &D_1F800000;
        *angle_cell                = angle;
        g_Task->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed + ((rsin(angle) * 0xA000) >> 12);
        g_Task->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle_cell) * 0xA000) >> 12);
        g_Task->pos.z.part.integer = g_BattleEffectBattler->pos.z.part.integer + 0x180;
        g_Task->unk_25             = 0x1D;
        g_Task->unk_26             = 0;
        g_Task->unk_27             = 0xA0;
        g_Task->unk_28             = 0;
        g_Task->unk_5D             = 0;
        g_Task->unk_5E             = 0;
        g_Task->unk_5F             = 0;
        g_Task->unk_5C             = 0;
        g_Task->unk_2A             = 0;
        g_Task->unk_29             = 4;
        g_Task->unk_24             = 4;
        work                       = g_Task;
        work->unk_2B               = 1;
        work->unk_2C.half          = 0;
        Actor_SelectScript((g_Task->param.unk_0B / 3) & BYTE_MASK);
        g_Task->header.step++;
    }
}

MATCH void func_801EF2A8(void) {
    PartyMember* work;

    if (Actor_StepAnimOnce() != 0u) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B + 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF2F4);

INCLUDE_ASM(func_801EF500);
