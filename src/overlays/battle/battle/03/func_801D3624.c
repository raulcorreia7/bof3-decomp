#include "battle_03.h"

extern s8 D_801EB713[];

/* Non-volatile view of the battle mode word (0x801463C0): ram.h declares it
 * volatile, and a volatile 16-bit load cannot be narrowed to the byte the
 * slot-selection call takes. */

/* starts a battle: clears the 0x20 setup flag, records the battle
 * mode, resolves the battler row of the random kind (local rows for kinds
 * 0-2, enemy rows for 3+) and copies its position words into the 0x80146386
 * pair.
 */
MATCH void func_801D3624(void) {
    u16* setup_flags;
    /* FAKE: allocator tie, row pointer in a1. */
    MATCH_FAKE_PIN(PartyBattler*, work, "a1");
    u32 row_offset;
    u8  kind_index;
    u16 mode;
    s32 kind;

    setup_flags = &g_BattleState;
    if ((*setup_flags & 0x20) == 0) {
        return;
    }

    *setup_flags &= ~0x20;
    D_8014637C[1] = 7;
    D_8014637C[2] = 0;
    Battle_SetSlotPending(g_BattleActingBattler);
    mode       = g_BattleActionId;
    D_801463CD = (u8)mode;
    if ((u16)(mode - 0x24) < 2 || mode == 0x8C) {
        kind                   = Battle_PickTarget();
        kind_index             = (u8)kind;
        g_BattleTargetSelector = kind;
        if (kind_index < 3) {
            work                  = &g_BattlePartyBattlers[kind_index];
            g_BattleSelectedActor = work;
            /* Retail builds this pointer as base + 0x118 + row * 0x140. */
            D_80146390            = &g_BattlePartyBattlers[0].unk_118 + kind_index * BATTLE_PARTY_STRIDE;
            D_80146386 = work->unk_2E.half +
                         g_BattlePanelOffsets[D_80145F09[kind_index][0] * 8 + work->word_08.byte.facing_08 * 2];
            D_80146388 =
                work->unk_30.half + D_801EB0B1[D_80145F09[kind_index][0] * 8 + work->word_08.byte.facing_08 * 2];
        } else {
            row_offset            = kind_index * 0x118;
            work                  = (PartyBattler*)(g_BattleEnemies + row_offset);
            D_80146390            = g_BattleEnemies + 0xF4 + row_offset;
            g_BattleSelectedActor = work;
            row_offset            = (kind_index - 3) * 0x118;
            D_80146386            = work->unk_2E.half + D_801EB712[row_offset];
            D_80146388            = work->unk_30.half + D_801EB713[row_offset];
        }
        D_8014638A = FIELD(u16, work, 0x32);
    }
    func_800AE1F8((*(u8*)&g_BattleActionId));
    g_BattleUiStep += 1;
}
