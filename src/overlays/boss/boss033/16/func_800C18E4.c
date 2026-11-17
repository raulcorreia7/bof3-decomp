#include "boss033_16.h"

#define g_Task ((PartyMember*)g_Task)

MATCH void func_800C18E4(void) {
    u32    slot;
    s32    enemy;
    Cpy16* src;
    Cpy16* dst;
    Cpy16* end;

    slot  = Battle_AllocEffect(3, 6);
    dst   = (Cpy16*)&g_BattleEffects[slot & BYTE_MASK];
    enemy = g_Battle.active_battler;
    enemy -= 3;
    src = (Cpy16*)&g_BattleEnemyBattlers[enemy];
    end = src + 7;
    do {
        *dst = *src;
        src += 1;
        dst += 1;
    } while (src != end);
    /* FAKE: hold the tail store before the slot offset is recomputed. */
    FAKE_ORDER_LOCK(dst->w[0] = src->w[0]);
    g_BattleEffects[slot & BYTE_MASK].unk_06       = 3;
    g_BattleEffects[slot & BYTE_MASK].step_index   = 6;
    g_BattleEffects[slot & BYTE_MASK].header.mode  = 0;
    g_BattleEffects[slot & BYTE_MASK].header.step  = 0;
    g_BattleEffects[slot & BYTE_MASK].unk_03       = 0;
    g_BattleEffects[slot & BYTE_MASK].unk_04       = 0;
    g_BattleEffects[slot & BYTE_MASK].unk_0B       = slot;
    g_BattleEffects[slot & BYTE_MASK].target.party = g_Task;
    g_Task->unk_09                                 = slot;
    g_Task->timer                                  = 16;
    g_Task->header.flags |= 0x40;
    g_Task->header.step++;
}
