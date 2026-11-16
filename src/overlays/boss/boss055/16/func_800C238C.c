#include "boss055_16.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800C238C(u8 mode, u8 index) {
    u32          effect_slot;
    CopyWords16* src;
    CopyWords16* dst;
    CopyWords16* end;

    effect_slot = Battle_AllocEffect(3, 5);
    dst         = (CopyWords16*)&g_BattleEffects[effect_slot & BYTE_MASK];
    src         = (CopyWords16*)g_BattleEnemyBattlers;
    end         = src + 7;
    do {
        *dst = *src;
        src += 1;
        dst += 1;
    } while (src != end);
    /* FAKE: keep the final copied word after the seven chunk loop. */
    FAKE_ORDER_LOCK(dst->w[0] = src->w[0]);
    g_BattleEffects[effect_slot & BYTE_MASK].unk_06        = 3;
    g_BattleEffects[effect_slot & BYTE_MASK].handler_index = 5;
    g_BattleEffects[effect_slot & BYTE_MASK].header.mode   = mode;
    g_BattleEffects[effect_slot & BYTE_MASK].header.step   = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].arg.unk_09    = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].target.enemy  = g_BattleEnemyBattlers;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_29        = index;
}
#else
INCLUDE_ASM(func_800C238C);
#endif
