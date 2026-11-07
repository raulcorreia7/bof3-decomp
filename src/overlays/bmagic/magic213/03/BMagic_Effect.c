#include "magic213_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEFC0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF004(void) {
    SYS_DISPATCH_TASK(D_801EF8A4, 2, g_Task);
}

INCLUDE_ASM(func_801EF048);

/* nonmatching: same body as Effect_FadePaletteIn, but retail has no stack frame; the shared body links one (+4 bytes, first difference at +0xE4). */
INCLUDE_ASM(func_801EF23C);

INCLUDE_ASM(func_801EF348);

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801EF4E0(void) {
    SYS_DISPATCH_TASK(D_801EF8B4, 1, g_Task);
}

MATCH void func_801EF524(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801EF8B4 + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

MATCH void func_801EF5BC(void) {
    s32           angle;
    u8            count;
    PartyBattler* work;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        angle                               = g_Task->param.unk_0B & 7;
        D_1F800000.view.area.entity_counter = angle << 9;
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(D_1F800000.view.area.entity_counter) * 0xC;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(D_1F800000.view.area.entity_counter) * 0xC;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x01800000;
        g_Task->unk_25      = 0x1D;
        g_Task->unk_26      = 0;
        g_Task->unk_27      = 0xA0;
        g_Task->unk_28      = 0;
        g_Task->unk_5D      = 0;
        g_Task->unk_5E      = 0;
        g_Task->unk_5F      = 0;
        g_Task->unk_5C      = 0;
        g_Task->unk_2A      = 0;
        g_Task->unk_29      = 4;
        g_Task->unk_24      = 4;
        work                = g_Task;
        work->unk_2B        = 1;
        work->unk_2C.half   = 0;
        Actor_SelectScript((g_Task->param.unk_0B % 3) & BYTE_MASK);
        g_Task->header.step++;
    }
}

MATCH void func_801EF7A0(void) {
    PartyBattler* work;

    if (func_8014DAEC() != 0u) {
        work               = (PartyBattler*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

/* func_801EF7EC */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EF850 */
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}
