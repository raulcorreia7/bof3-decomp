#include "battle_03.h"

/* Byte-displacement views over the per-battler local records (stride 0x140,
 * the PartyBattler array) and the ability template records (stride 0xA4).
 * g_BattlePartyBattlers comes from battle_03.h; the rest are field bases. */

MATCH void func_801DD8AC(u32 battler_index) {
    u32 off;
    s32 tidx;
    u16 flags;

    battler_index &= BYTE_MASK;
    off = battler_index * 320u;
    if ((((u8*)(g_BattlePartyBattlers))[off] & 1u) != 0u) {
        tidx                                                        = D_80145FCC[off] * PARTY_RECORD_STRIDE;
        /* FAKE: volatile-drop keeps the original load and store order. */
        *MATCH_VOLATILE_PTR(u16, ((u8*)&g_Characters[0].hp + tidx)) = g_BattlePartyBattlers[battler_index].chr.hp;
        /* FAKE: volatile-drop keeps the original load and store order. */
        /* FAKE: retail reads D_80145F1A as volatile u8[]. */
        *MATCH_VOLATILE_PTR(u16, ((u8*)&g_Characters[0].ap + tidx)) =
            *MATCH_VOLATILE_PTR(u16, (((volatile u8*)D_80145F1A) + off));
        /* FAKE: volatile-drop keeps the original load and store order. */
        *MATCH_VOLATILE_PTR(u8, ((u8*)&g_Characters[0].willpower + tidx)) = D_80145F1C[off];
        /* FAKE: volatile-drop keeps the original load and store order. */
        flags                                        = *MATCH_VOLATILE_PTR(u16, (D_80145F10 + off)) & 0x60A0u;
        *(u16*)((D_80145F10 + off))                  = flags;
        *(u16*)((u8*)&g_Characters[0].status + tidx) = flags;
    }
}
