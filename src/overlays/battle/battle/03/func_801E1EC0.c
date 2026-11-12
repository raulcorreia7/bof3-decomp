#include "battle_03.h"

typedef struct WorkChunk {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} WorkChunk;

MATCH void func_801E1EC0(void) {
    u32                   effect_slot;
    WorkChunk*            src;
    WorkChunk*            dst;
    WorkChunk*            end;
    volatile PartyMember* work;

    effect_slot = Battle_AllocEffect(0, 15);
    dst         = (WorkChunk*)&g_BattleEffects[effect_slot & BYTE_MASK];
    src         = (WorkChunk*)&BATTLE_ACTIVE_PARTY;
    end         = src + 7;
    do {
        *dst = *src;
        src += 1;
        dst += 1;
    } while (src != end);
    /* FAKE: hold tail store before tail. */
    FAKE_ORDER_LOCK(dst->w0 = src->w0);
    g_BattleEffects[effect_slot & BYTE_MASK].unk_06        = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].handler_index = 0xF;
    g_BattleEffects[effect_slot & BYTE_MASK].header.mode   = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].header.step   = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_03        = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_04        = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_0B        = effect_slot;
    g_BattleEffects[effect_slot & BYTE_MASK].target.party  = g_Task;
    g_Task->header.flags |= ACTOR_FLAG_HIDDEN;
    g_Task->unk_09                    = 0x10;
    g_Task->timer                     = 16;
    work                              = g_Task;
    ((PartyMember*)work)->header.step = (((PartyMember*)work)->header.step + 1);
}
