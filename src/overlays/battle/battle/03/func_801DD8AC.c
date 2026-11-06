#include "battle_03.h"

/* Byte-displacement views over the per-battler local records (stride 0x140,
 * the PartyBattler array) and the ability template records (stride 0xA4).
 * g_BattlePartyBattlers comes from battle_03.h; the rest are field bases. */

MATCH void func_801DD8AC(u32 battler_index) {
    u32 off;
    s32 character_offset;
    u16 flags;

    battler_index &= BYTE_MASK;
    off = battler_index * 320u;
    if ((((u8*)(g_BattlePartyBattlers))[off] & 1u) != 0u) {
        character_offset = g_BattlePartyBattlers[battler_index].character_index * PARTY_RECORD_STRIDE;
        *(u16*)(((u8*)&g_Characters[0].hp + character_offset))       = g_BattlePartyBattlers[battler_index].chr.hp;
        /* FAKE: volatile-drop keeps the original load and store order. */
        *(u16*)(((u8*)&g_Characters[0].ap + character_offset))       = *(u16*)((((volatile u8*)D_80145F1A) + off));
        *(u8*)(((u8*)&g_Characters[0].willpower + character_offset)) = D_80145F1C[off];
        flags                                                        = *(u16*)((D_80145F10 + off)) & 0x60A0u;
        *(u16*)((D_80145F10 + off))                                  = flags;
        *(u16*)((u8*)&g_Characters[0].status + character_offset)     = flags;
    }
}
