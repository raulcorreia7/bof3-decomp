#include "battle_03.h"

/* func_801E5E2C */
#ifdef NON_MATCHING
NON_MATCHING void Battle_StartDamageNumber(void) {
    BattleEffect* slot;
    BattleEffect* work;
    BattleEffect* check;
    BattleEffect* current;
    PartyMember*  source;
    s16           type;
    u32           index;
    s32           divisor;
    u8            digits;
    u8            offset;
    u8            member;

    slot   = D_801EC2E0;
    source = slot->target.party;
    if (source->slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        index                  = (source->facing * 2) + (source->unk_2C.value * 8);
        COORD_INT(slot->pos.x) = (s8)g_BattlePanelOffsets[index] + source->screen_x.value;
        source                 = slot->target.party;
        index                  = (source->facing * 2) + (source->unk_2C.value * 8);
        offset                 = (g_BattlePanelOffsets + 1)[index];
    } else {
        type                   = source->slot - BATTLE_PARTY_CHARACTERS_COUNT;
        COORD_INT(slot->pos.x) = g_BattleEnemyBattlers[type].panel_offset_x + source->screen_x.value;
        source                 = slot->target.party;
        type                   = source->slot - BATTLE_PARTY_CHARACTERS_COUNT;
        offset                 = g_BattleEnemyBattlers[type].panel_offset_y;
    }
    /* FAKE: holds the running-slot reload below this store, as retail orders them. */
    FAKE_VOLATILE(s16, COORD_INT(slot->pos.y)) = source->screen_y.value + (s8)offset;
    /* The running slot can change hands, so re-read it before each phase. */
    check                                      = D_801EC2E0;
    if (check->unk_0B == 1) {
        COORD_INT(check->pos.y) -= 9;
    }
    divisor = 0x64;
    /* Drop a decimal place per pass until the value still fits the divisor. */
    current = D_801EC2E0;
    for (digits = 2; digits != 0; digits--) {
        if ((current->target_index.target_index / (divisor & BYTE_MASK)) > 0) {
            break;
        }
        divisor = (divisor & BYTE_MASK) / 10u;
    }
    member = current->target.party->slot;
    if (member < BATTLE_PARTY_CHARACTERS_COUNT) {
        g_Game.members[member].u.turn.damage_flags.value |= BATTLER_DAMAGE_NUMBER;
    } else {
        ENEMY_COMBATANT(member).turn.damage_flags.value |= BATTLER_DAMAGE_NUMBER;
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
