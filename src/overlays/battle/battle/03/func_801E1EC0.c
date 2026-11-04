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
    src     = (WorkChunk*)&BATTLE_ACTING_PARTY;
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
    g_BattleEffects[slot_id & BYTE_MASK].unk_01        = 0;
    g_BattleEffects[slot_id & BYTE_MASK].unk_02        = 0;
    g_BattleEffects[slot_id & BYTE_MASK].unk_03        = 0;
    g_BattleEffects[slot_id & BYTE_MASK].unk_04        = 0;
    g_BattleEffects[slot_id & BYTE_MASK].unk_0B        = (s8)slot_id;
    g_BattleEffects[slot_id & BYTE_MASK].target.party  = g_SpadWork;
    g_SpadWork->flags_00 |= ACTOR_FLAG_HIDDEN;
    g_SpadWork->word_08.byte.unk_09   = 0x10;
    g_SpadWork->word_08.byte.timer_0A = 0x10;
    work                              = g_SpadWork;
    ((PartyBattler*)work)->unk_02     = (((PartyBattler*)work)->unk_02 + 1);
}
