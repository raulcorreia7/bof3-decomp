#include "battle_03.h"

MATCH void func_801E1EC0(void) {
    u32                   effect_slot;
    Cpy16*                src;
    Cpy16*                dst;
    Cpy16*                end;
    volatile PartyMember* work;

    effect_slot = Battle_AllocEffect(0, 15);
    dst         = (Cpy16*)&g_BattleEffects[effect_slot & BYTE_MASK];
    src         = (Cpy16*)&BATTLE_ACTIVE_PARTY;
    end         = src + 7;
    do {
        *dst = *src;
        src += 1;
        dst += 1;
    } while (src != end);
    /* FAKE: hold tail store before tail. */
    FAKE_ORDER_LOCK(dst->w[0] = src->w[0]);
    g_BattleEffects[effect_slot & BYTE_MASK].unk_06       = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].effect_type  = 0xF;
    g_BattleEffects[effect_slot & BYTE_MASK].header.mode  = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].header.step  = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_03       = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_04       = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_0B       = effect_slot;
    g_BattleEffects[effect_slot & BYTE_MASK].target.party = TASK(PartyMember);
    TASK(PartyMember)->header.flags |= ACTOR_FLAG_HIDDEN;
    TASK(PartyMember)->unk_09         = 0x10;
    TASK(PartyMember)->timer          = 16;
    work                              = TASK(PartyMember);
    ((PartyMember*)work)->header.step = (((PartyMember*)work)->header.step + 1);
}
