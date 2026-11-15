#include "boss055_16.h"

MATCH void func_800C238C(u8 arg0, u8 arg1) {
    u32        slot;
    WorkChunk* src;
    WorkChunk* dst;
    WorkChunk* end;

    slot = Battle_AllocEffect(3, 5);
    /* FAKE: the best pure C holds the slot in t1 and the loop end in t0, the reverse of retail;
       a pointer local for the end, the symbol form of it and a statement reorder all keep t1. */
    FAKE_USE(slot);
    dst = (WorkChunk*)&g_BattleEffects[slot & BYTE_MASK];
    src = (WorkChunk*)g_BattleEnemyBattlers;
    end = src + 7;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    /* FAKE: hold the tail store before the slot offset is recomputed. */
    FAKE_ORDER_LOCK(dst->w0 = src->w0);
    g_BattleEffects[slot & BYTE_MASK].unk_06        = 3;
    g_BattleEffects[slot & BYTE_MASK].handler_index = 5;
    g_BattleEffects[slot & BYTE_MASK].header.mode   = arg0;
    g_BattleEffects[slot & BYTE_MASK].header.step   = 0;
    g_BattleEffects[slot & BYTE_MASK].arg.unk_09    = 0;
    g_BattleEffects[slot & BYTE_MASK].target.enemy  = g_BattleEnemyBattlers;
    g_BattleEffects[slot & BYTE_MASK].unk_29        = arg1;
}
