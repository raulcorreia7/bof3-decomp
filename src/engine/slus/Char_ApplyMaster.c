#include "engine/slus/slus.h"

/* runs the update script selected by arg[0x1B]: each entry is an
 * (opcode, operand) pair applied to one counter slot, 0x0E ends it.
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
    if ((op & BYTE_MASK) == 0x0E) {
        return;
    }
    val = pc + 1;
    do {
        switch (op & BYTE_MASK) {
            case 0:
                Char_AddResistance(arg + 0x2B, (s8)*val);
                break;
            case 1:
                Char_AddResistance(arg + 0x2C, (s8)*val);
                break;
            case 2:
                Char_AddResistance(arg + 0x2D, (s8)*val);
                break;
            case 3:
                Char_AddResistance(arg + 0x2E, (s8)*val);
                break;
            case 4:
                Char_AddResistance(arg + 0x2F, (s8)*val);
                break;
            case 5:
                Char_AddResistance(arg + 0x30, (s8)*val);
                break;
            case 6:
                Char_AddResistance(arg + 0x31, (s8)*val);
                break;
            case 7:
                Char_AddResistance(arg + 0x32, (s8)*val);
                break;
            case 8:
                Char_AddResistance(arg + 0x33, (s8)*val);
                break;
            case 9:
                Char_AddPercent(arg + 0x34, *val);
                break;
            case 10:
                Char_AddPercent(arg + 0x35, *val);
                break;
            case 11:
                Char_AddPercent(arg + 0x36, *val);
                break;
            case 12:
                Char_AddPercent(arg + 0x37, *val);
                break;
            case 13:
                Char_AddPercent(arg + 0x38, *val);
                break;
            default:
                break;
        }
        pc += 2;
        val += 2;
        op = *pc;
    } while ((op & BYTE_MASK) != 0x0E);
}
