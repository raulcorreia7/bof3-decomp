#include "battle_03.h"

typedef struct WorkChunk {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} WorkChunk;

MATCH void func_801E1EC0(void) {
    u32                    slot_id;
    WorkChunk*             src;
    WorkChunk*             dst;
    WorkChunk*             end;
    volatile PartyBattler* work;

    slot_id = Battle_AllocEffect(0, 0xF);
    dst     = (WorkChunk*)&g_BattleEffects[slot_id & BYTE_MASK];
    src     = (WorkChunk*)&BATTLE_ACTIVE_PARTY;
    end     = src + 7;
    do {
        *dst = *src;
        src += 1;
        dst += 1;
    } while (src != end);
    /* FAKE: hold tail store before tail. */
    ORDER_LOCK(dst->w0 = src->w0);
    g_BattleEffects[slot_id & BYTE_MASK].unk_06        = 0;
    g_BattleEffects[slot_id & BYTE_MASK].handler_index = 0xF;
    g_BattleEffects[slot_id & BYTE_MASK].mode          = 0;
    g_BattleEffects[slot_id & BYTE_MASK].step          = 0;
    g_BattleEffects[slot_id & BYTE_MASK].unk_03        = 0;
    g_BattleEffects[slot_id & BYTE_MASK].unk_04        = 0;
    g_BattleEffects[slot_id & BYTE_MASK].unk_0B        = (s8)slot_id;
    g_BattleEffects[slot_id & BYTE_MASK].target.party  = g_Task;
    g_Task->flags |= ACTOR_FLAG_HIDDEN;
    g_Task->word_08.byte.unk_09   = 0x10;
    g_Task->word_08.byte.timer_0A = 0x10;
    work                          = g_Task;
    ((PartyBattler*)work)->step   = (((PartyBattler*)work)->step + 1);
}
