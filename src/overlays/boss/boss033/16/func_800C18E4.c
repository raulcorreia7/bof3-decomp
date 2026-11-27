#include "boss033_16.h"

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
    COPY_TAIL_WORD(dst, src);
    g_BattleEffects[slot & BYTE_MASK].unk_06       = 3;
    g_BattleEffects[slot & BYTE_MASK].effect_type  = 6;
    g_BattleEffects[slot & BYTE_MASK].header.mode  = 0;
    g_BattleEffects[slot & BYTE_MASK].header.step  = 0;
    g_BattleEffects[slot & BYTE_MASK].unk_03       = 0;
    g_BattleEffects[slot & BYTE_MASK].unk_04       = 0;
    g_BattleEffects[slot & BYTE_MASK].unk_0B       = slot;
    g_BattleEffects[slot & BYTE_MASK].target.party = SELF(PartyMember);
    SELF(PartyMember)->unk_09                      = slot;
    SELF(PartyMember)->timer                       = 16;
    SELF(PartyMember)->header.flags |= 0x40;
    SELF(PartyMember)->header.step++;
}
