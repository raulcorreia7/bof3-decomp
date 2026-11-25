#include "battle_03.h"

/* func_801E5E2C */
#ifdef NON_MATCHING
NON_MATCHING void Battle_StartDamageNumber(void) {
    BattleEffect* slot;
    BattleEffect* work;
    PartyMember*  source;
    u32           type;
    u32           index;
    s32           divisor;
    u8            digits;
    u8            offset;

    slot   = D_801EC2E0;
    source = slot->target.party;
    if (source->slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        index                  = (source->facing * 2) + (source->unk_2C.value * 8);
        COORD_INT(slot->pos.x) = source->screen_x.value + (s8)g_BattlePanelOffsets[index];
        source                 = slot->target.party;
        index                  = (source->facing * 2) + (source->unk_2C.value * 8);
        offset                 = (g_BattlePanelOffsets + 1)[index];
    } else {
        type                   = source->slot - BATTLE_PARTY_CHARACTERS_COUNT;
        COORD_INT(slot->pos.x) = source->screen_x.value + g_BattleEnemyBattlers[type].panel_offset_x;
        source                 = slot->target.party;
        type                   = source->slot - BATTLE_PARTY_CHARACTERS_COUNT;
        offset                 = g_BattleEnemyBattlers[type].panel_offset_y;
    }
    COORD_INT(slot->pos.y) = source->screen_y.value + (s8)offset;
    /* The running slot can change hands, so re-read it before each phase. */
    slot                   = D_801EC2E0;
    divisor                = 0x64;
    if (slot->unk_0B == 1) {
        COORD_INT(slot->pos.y) -= 9;
    }
    /* Drop a decimal place per pass until the value still fits the divisor. */
    slot = D_801EC2E0;
    for (digits = 2; digits != 0; digits--) {
        if ((slot->target_index.target_index / (divisor & BYTE_MASK)) > 0) {
            break;
        }
        divisor = (divisor & BYTE_MASK) / 10u;
    }
    type = slot->target.party->slot;
    if (type < BATTLE_PARTY_CHARACTERS_COUNT) {
        g_Game.members[type].u.turn.damage_flags.value |= BATTLER_DAMAGE_NUMBER;
    } else {
        ENEMY_COMBATANT(type).turn.damage_flags.value |= BATTLER_DAMAGE_NUMBER;
    }
    /* The slot pointer is live, so each write reads the running slot again. */
    D_801EC2E0->unk_0A     = digits;
    D_801EC2E0->arg.unk_09 = 8;
    work                   = D_801EC2E0;
    work->depth            = 0;
    work->header.mode += 1;
}
#else
INCLUDE_ASM(Battle_StartDamageNumber);
#endif
