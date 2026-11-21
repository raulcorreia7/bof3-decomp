#include "battle_03.h"

/* func_801E5E2C */
#ifdef NON_MATCHING
NON_MATCHING void Battle_StartDamageNumber(void) {
    BattleEffect* slot;
    PartyMember*  source;
    u8            digits;
    s32           divisor;
    u8            type;
    s8            offset;

    slot   = D_801EC2E0;
    source = slot->target.party;
    type   = source->slot;
    if (type < 3) {
        COORD_INT(slot->pos.x) = source->screen_x.value + (s8)g_BattlePanelOffsets[(source->facing * 2) + (source->unk_2C.value * 8)];
        source                 = slot->target.party;
        offset                 = (g_BattlePanelOffsets + 1)[(source->facing * 2) + (source->unk_2C.value * 8)];
    } else {
        type -= 3;
        COORD_INT(slot->pos.x) = source->screen_x.value + g_BattleEnemyBattlers[type].panel_offset_x;
        source                 = slot->target.party;
        type                   = source->slot;
        type -= 3;
        offset = g_BattleEnemyBattlers[type].panel_offset_y;
    }
    COORD_INT(slot->pos.y) = source->screen_y.value + offset;
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
    type = slot->target.party->slot;
    if (type < 3) {
        g_Game.members[type].u.turn.damage_flags.value |= BATTLER_DAMAGE_NUMBER;
    } else {
        ENEMY_COMBATANT(type).turn.damage_flags.value |= 0x80;
    }
    slot->unk_0A     = digits;
    slot->arg.unk_09 = 8;
    slot->depth      = 0;
    slot->header.mode += 1;
}
#else
INCLUDE_ASM(Battle_StartDamageNumber);
#endif
