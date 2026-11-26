#include "boss055_16.h"

MATCH void func_800C238C(u8 mode, u8 index) {
    u32    effect_slot;
    Cpy16* src;
    Cpy16* dst;
    /* FAKE: retail's loop limit uses t1. */
    FAKE_REG(Cpy16*, end, "t1");

    effect_slot = Battle_AllocEffect(3, 5);
    dst         = (Cpy16*)&g_BattleEffects[effect_slot & BYTE_MASK];
    src         = (Cpy16*)g_BattleEnemyBattlers;
    end         = src + 7;
    do {
        *dst = *src;
        src += 1;
        dst += 1;
    } while (src != end);
    /* FAKE: the final word completes the 0x74-byte record copy. */
    FAKE_ORDER_LOCK(dst->w[0] = src->w[0]);
    g_BattleEffects[effect_slot & BYTE_MASK].unk_06       = 3;
    g_BattleEffects[effect_slot & BYTE_MASK].effect_type  = 5;
    g_BattleEffects[effect_slot & BYTE_MASK].header.mode  = mode;
    g_BattleEffects[effect_slot & BYTE_MASK].header.step  = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].arg.unk_09   = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].target.enemy = g_BattleEnemyBattlers;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_29       = index;
}
