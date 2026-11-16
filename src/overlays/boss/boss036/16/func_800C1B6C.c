#include "boss036_16.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800C1B6C(void) {
    u32        effect_slot;
    u32        effect_offset;
    s32        active_battler;
    WorkChunk* src;
    WorkChunk* dst;
    WorkChunk* end;

    if ((FIELD(u32, g_Task, 0) & 0xFFFF00) != 0x10700) {
        return;
    }

    effect_slot   = Battle_AllocEffect(3, 3);
    effect_offset = (effect_slot & BYTE_MASK) * sizeof(BattleEffect);
    /* FAKE: keeps the battler load between the slot offset and destination base. */
    FAKE_ORDER_LOCK(active_battler = g_Battle.active_battler);
    dst = (WorkChunk*)((u8*)g_BattleEffects + effect_offset);
    active_battler -= 3;
    src = (WorkChunk*)&g_BattleEnemyBattlers[active_battler];
    end = src + 7;
    do {
        *dst = *src;
        src += 1;
        dst += 1;
    } while (src != end);
    FAKE_ORDER_LOCK(dst->w0 = src->w0);

    g_BattleEffects[effect_slot & BYTE_MASK].header.mode   = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].header.step   = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_06        = 3;
    g_BattleEffects[effect_slot & BYTE_MASK].handler_index = 3;
    g_BattleEffects[effect_slot & BYTE_MASK].arg.unk_09    = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_29        = 3;
}
#else
INCLUDE_ASM(func_800C1B6C);
#endif
