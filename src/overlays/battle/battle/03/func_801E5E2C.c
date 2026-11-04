#include "battle_03.h"

/* +1 columns of the panel tables at g_BattlePanelOffsets and D_801EB712: the byte after
 * each row stride's first entry, as the retail relocations name them. */
extern s8 D_801EB713[];

/* nonmatching unmeasured: tried cached slot pointer; kind-3 hoisted to a local; unsigned index casts; else-scoped row
 * local. resume: a source shape that materializes kind-3 before the branch (retail fills the beqz delay slot with
 * addiu). */
#ifdef NON_MATCHING
NON_MATCHING void func_801E5E2C(void) {
    BattleEffect* slot;
    PartyBattler* source;
    s32           digits;
    s32           divisor;
    u8            kind;
    s8            offset;

    slot   = D_801EC2E0;
    source = slot->work_74.party;
    kind   = source->slot;
    if (kind < 3) {
        slot->unk_34.half.hi =
            source->unk_2E.half + (s8)g_BattlePanelOffsets[(source->unk_08 * 2) + (source->unk_2C.half * 8)];
        source = slot->work_74.party;
        offset = (g_BattlePanelOffsets + 1)[(source->unk_08 * 2) + (source->unk_2C.half * 8)];
    } else {
        slot->unk_34.half.hi = source->unk_2E.half + (s8)D_801EB712[(kind - 3) * 0x118];
        source               = slot->work_74.party;
        offset               = D_801EB713[(source->slot - 3) * 0x118];
    }
    slot->unk_38.half.hi = source->unk_30.half + offset;
    divisor              = 0x64;
    if (slot->unk_0B == 1) {
        slot->unk_38.half.hi = slot->unk_38.half.hi - 9;
    }
    digits = 2;
    /* Shorter each pass: the ladder ends when the value still fits the divisor. */
loop:
    if ((FIELD(s32, slot, 0x60) / divisor) <= 0) {
        digits -= 1;
        divisor = (divisor & BYTE_MASK) / 10;
        if (digits != 0) {
            goto loop; /* back to the shorter divisor */
        }
    }
    kind = slot->work_74.party->slot;
    if (kind < 3) {
        g_BattlePartyBattlers[kind].flags_124.value |= COMBATANT_FLAG_DAMAGE_NUMBER;
    } else {
        D_801EB730[(kind - 3) * 0x118] |= 0x80;
    }
    slot->unk_0A           = digits;
    slot->unk_09           = 8;
    FIELD(s16, slot, 0x32) = 0;
    slot->unk_01 += 1;
}
#else
INCLUDE_ASM(func_801E5E2C);
#endif
