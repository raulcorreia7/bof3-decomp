#include "magic218_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDB8};

    SYS_DISPATCH_TASK(handlers, 1, g_Self);
}

MATCH void func_801EEC5C(void) {
    PartyMember* task;
    PartyMember* target;
    u16*         src;
    u16*         dst;
    u16          i;
    u32          slot;

    for (i = 0; i < 8; i++) {
        D_801EF790[i] = 0;
    }
    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    task                      = SELF(PartyMember);
    WorldPos_Copy(&task->pos, &g_BattleEffectBattler->pos);
    task->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 103) & BYTE_MASK;
    target                             = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 1;
    g_BattleEffects[slot].target.party = target;
    SELF(PartyMember)->param.unk_0B += 1;
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
}
