#include "battle_03.h"

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
    source = slot->target.party;
    kind   = source->slot;
    if (kind < 3) {
        COORD_INT(slot->pos.x) =
            source->unk_2E.half + (s8)g_BattlePanelOffsets[(source->facing * 2) + (source->unk_2C.half * 8)];
        source = slot->target.party;
        offset = (g_BattlePanelOffsets + 1)[(source->facing * 2) + (source->unk_2C.half * 8)];
    } else {
        COORD_INT(slot->pos.x) = source->unk_2E.half + ENEMY_COMBATANT(kind).panel_offset_x;
        source                 = slot->target.party;
        offset                 = ENEMY_COMBATANT(source->slot).panel_offset_y;
    }
    COORD_INT(slot->pos.y) = source->unk_30.half + offset;
    divisor                = 0x64;
    if (slot->unk_0B == 1) {
        COORD_INT(slot->pos.y) -= 9;
    }
    digits = 2;
    /* Shorter each pass: the ladder ends when the value still fits the divisor. */
loop:
    if ((slot->word_60.target_index / divisor) <= 0) {
        digits -= 1;
        divisor = (divisor & BYTE_MASK) / 10;
        if (digits != 0) {
            goto loop; /* back to the shorter divisor */
        }
    }
    kind = slot->target.party->slot;
    if (kind < 3) {
        g_BattlePartyBattlers[kind].turn.damage_flags.value |= COMBATANT_FLAG_DAMAGE_NUMBER;
    } else {
        ENEMY_COMBATANT(kind).turn.damage_flags.value |= 0x80;
    }
    slot->unk_0A = digits;
    slot->unk_09 = 8;
    slot->unk_32 = 0;
    slot->header.mode += 1;
}
#else
INCLUDE_ASM(func_801E5E2C);
#endif
