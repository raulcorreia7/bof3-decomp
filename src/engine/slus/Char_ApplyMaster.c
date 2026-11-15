#include "engine/slus/slus.h"

/* runs the update script selected by the character's master: each entry is an
 * (opcode, operand) pair applied to one counter slot, MASTER_MOD_END ends it.
 */
MATCH void Char_ApplyMaster(Character* character) {
    u8* pc;
    u8* val;
    u8  op;

    if (character->master_id == GAME_NONE) {
        return;
    }
    pc = (u8*)D_80183A1C[character->master_id];
    if (pc == NULL) {
        return;
    }
    op = *pc;
    if ((op & BYTE_MASK) == MASTER_MOD_END) {
        return;
    }
    val = pc + 1;
    do {
        switch (op & BYTE_MASK) {
            case RES_INDEX_FIRE:
                Char_AddResistance(&character->stats.resistances[RES_INDEX_FIRE], (s8)*val);
                break;
            case RES_INDEX_FROST:
                Char_AddResistance(&character->stats.resistances[RES_INDEX_FROST], (s8)*val);
                break;
            case RES_INDEX_ELECTRIC:
                Char_AddResistance(&character->stats.resistances[RES_INDEX_ELECTRIC], (s8)*val);
                break;
            case RES_INDEX_EARTH:
                Char_AddResistance(&character->stats.resistances[RES_INDEX_EARTH], (s8)*val);
                break;
            case RES_INDEX_WIND:
                Char_AddResistance(&character->stats.resistances[RES_INDEX_WIND], (s8)*val);
                break;
            case RES_INDEX_HOLY:
                Char_AddResistance(&character->stats.resistances[RES_INDEX_HOLY], (s8)*val);
                break;
            case RES_INDEX_PSIONIC:
                Char_AddResistance(&character->stats.resistances[RES_INDEX_PSIONIC], (s8)*val);
                break;
            case RES_INDEX_STATUS:
                Char_AddResistance(&character->stats.resistances[RES_INDEX_STATUS], (s8)*val);
                break;
            case RES_INDEX_DEATH:
                Char_AddResistance(&character->stats.resistances[RES_INDEX_DEATH], (s8)*val);
                break;
            case MASTER_MOD_SURPRISE_CHANCE:
                Char_AddPercent(&character->stats.surprise_chance, *val);
                break;
            case MASTER_MOD_REPRISAL_CHANCE:
                Char_AddPercent(&character->stats.reprisal_chance, *val);
                break;
            case MASTER_MOD_CRITICAL_CHANCE:
                Char_AddPercent(&character->stats.critical_chance, *val);
                break;
            case MASTER_MOD_EVASION:
                Char_AddPercent(&character->stats.evasion, *val);
                break;
            case MASTER_MOD_ACCURACY:
                Char_AddPercent(&character->stats.accuracy, *val);
                break;
            default:
                break;
        }
        pc += 2;
        val += 2;
        op = *pc;
    } while ((op & BYTE_MASK) != MASTER_MOD_END);
}
