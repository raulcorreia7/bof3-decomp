#include "battle_15.h"

/* func_8009C868 */
MATCH u8 Battle_Unk0E1BitTest(volatile u8* entry, s32 bit_index) {
    return ((entry[0xE1] >> bit_index) & 1U);
}
