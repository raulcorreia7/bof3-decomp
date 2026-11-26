#include "boss036_16.h"

MATCH void func_800C1B6C(void) {
    u32           effect_slot;
    u8            effect_index;
    u32           effect_offset;
    s32           enemy_index;
    u8*           effect_base;
    EnemyBattler* enemy_base;
    Cpy16*        src;
    Cpy16*        dst;
    Cpy16*        end;
    u32*          record;

    record = TASK(u32);
    if ((record[0] & 0xFFFF00) == 0x10700) {
        effect_slot   = Battle_AllocEffect(3, 3);
        effect_index  = effect_slot & BYTE_MASK;
        effect_offset = effect_index * BATTLE_EFFECT_STRIDE;
        /* FAKE: retail reads the active enemy after computing the effect offset. */
        FAKE_BARRIER();
        enemy_index = g_Battle.active_battler;
        effect_base = (u8*)g_BattleEffects;
        dst         = (Cpy16*)(effect_base + effect_offset);
        enemy_base  = g_BattleEnemyBattlers;
        enemy_index -= BATTLE_PARTY_CHARACTERS_COUNT;
        src = (Cpy16*)&enemy_base[enemy_index];
        end = src + 7;
        do {
            *dst = *src;
            src += 1;
            dst += 1;
        } while (src != end);
        /* FAKE: hold tail store before tail. */
        FAKE_ORDER_LOCK(dst->w[0] = src->w[0]);
        g_BattleEffects[effect_index].header.mode = 0;
        g_BattleEffects[effect_index].header.step = 0;
        g_BattleEffects[effect_index].unk_06      = 3;
        g_BattleEffects[effect_index].effect_type = 3;
        g_BattleEffects[effect_index].arg.unk_09  = 0;
        g_BattleEffects[effect_index].unk_29      = 3;
    }
}
