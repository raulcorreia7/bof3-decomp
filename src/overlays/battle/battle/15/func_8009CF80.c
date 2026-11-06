#include "battle_15.h"

MATCH void func_8009CF80(u8* record, s32 index, s32 new_value) {
    switch (index & 0xFF) {
        case 0:
            record[0xCF] = new_value;
            break;
        case 1:
            record[0xD0] = new_value;
            break;
        case 2:
            record[0xD1] = new_value;
            break;
        case 3:
            record[0xD2] = new_value;
            break;
        case 4:
            record[0xD3] = new_value;
            break;
        case 5:
            record[0xD4] = new_value;
            break;
        case 6:
            record[0xD5] = new_value;
            break;
        case 7:
            record[0xD7] = new_value;
            break;
    }
}
