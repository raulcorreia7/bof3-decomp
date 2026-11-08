#include "engine/slus/slus.h"

/* runs the update script selected by arg[0x1B]: each entry is an
 * (opcode, operand) pair applied to one counter slot, MASTER_MOD_END ends it.
 */
MATCH void Char_ApplyMaster(u8* arg) {
    u8* pc;
    u8* val;
    u8  op;

    if (arg[0x1B] == GAME_NONE) {
        return;
    }
    pc = (u8*)D_80183A1C[arg[0x1B]];
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
                Char_AddResistance(arg + 0x2B, (s8)*val);
                break;
            case RES_INDEX_FROST:
                Char_AddResistance(arg + 0x2C, (s8)*val);
                break;
            case RES_INDEX_ELECTRIC:
                Char_AddResistance(arg + 0x2D, (s8)*val);
                break;
            case RES_INDEX_EARTH:
                Char_AddResistance(arg + 0x2E, (s8)*val);
                break;
            case RES_INDEX_WIND:
                Char_AddResistance(arg + 0x2F, (s8)*val);
                break;
            case RES_INDEX_HOLY:
                Char_AddResistance(arg + 0x30, (s8)*val);
                break;
            case RES_INDEX_PSIONIC:
                Char_AddResistance(arg + 0x31, (s8)*val);
                break;
            case RES_INDEX_STATUS:
                Char_AddResistance(arg + 0x32, (s8)*val);
                break;
            case RES_INDEX_DEATH:
                Char_AddResistance(arg + 0x33, (s8)*val);
                break;
            case MASTER_MOD_SURPRISE_CHANCE:
                Char_AddPercent(arg + 0x34, *val);
                break;
            case MASTER_MOD_REPRISAL_CHANCE:
                Char_AddPercent(arg + 0x35, *val);
                break;
            case MASTER_MOD_CRITICAL_CHANCE:
                Char_AddPercent(arg + 0x36, *val);
                break;
            case MASTER_MOD_EVASION:
                Char_AddPercent(arg + 0x37, *val);
                break;
            case MASTER_MOD_ACCURACY:
                Char_AddPercent(arg + 0x38, *val);
                break;
            default:
                break;
        }
        pc += 2;
        val += 2;
        op = *pc;
    } while ((op & BYTE_MASK) != MASTER_MOD_END);
}
