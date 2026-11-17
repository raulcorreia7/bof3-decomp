#include "battle_03.h"

/* func_801E5E2C */
#ifdef NON_MATCHING
NON_MATCHING void Battle_StartDamageNumber(void) {
    BattleEffect* slot;
    PartyMember*  source;
    u8            digits;
    s32           divisor;
    u8            kind;
    s8            offset;

    slot   = D_801EC2E0;
    source = slot->target.party;
    kind   = source->slot;
    if (kind < 3) {
        COORD_INT(slot->pos.x) = source->unk_2E.value + (s8)g_BattlePanelOffsets[(source->facing * 2) + (source->unk_2C.value * 8)];
        source                 = slot->target.party;
        offset                 = (g_BattlePanelOffsets + 1)[(source->facing * 2) + (source->unk_2C.value * 8)];
    } else {
        kind -= 3;
        COORD_INT(slot->pos.x) = source->unk_2E.value + g_BattleEnemyBattlers[kind].panel_offset_x;
        source                 = slot->target.party;
        kind                   = source->slot;
        kind -= 3;
        offset = g_BattleEnemyBattlers[kind].panel_offset_y;
    }
    COORD_INT(slot->pos.y) = source->unk_30.value + offset;
    divisor                = 0x64;
    if (slot->unk_0B == 1) {
        COORD_INT(slot->pos.y) -= 9;
    }
    digits = 2;
    /* Shorter each pass: the ladder ends when the value still fits the divisor. */
loop:
    if ((slot->target_index.target_index / divisor) <= 0) {
        digits -= 1;
        divisor = (divisor & BYTE_MASK) / 10;
        if (digits != 0) {
            goto loop; /* back to the shorter divisor */
        }
    }
    kind = slot->target.party->slot;
    if (kind < 3) {
        g_Game.members[kind].u.turn.damage_flags.value |= BATTLER_DAMAGE_NUMBER;
    } else {
        ENEMY_COMBATANT(kind).turn.damage_flags.value |= 0x80;
    }
    slot->unk_0A     = digits;
    slot->arg.unk_09 = 8;
    slot->unk_32     = 0;
    slot->header.mode += 1;
}
#else
INCLUDE_ASM(Battle_StartDamageNumber);
#endif
