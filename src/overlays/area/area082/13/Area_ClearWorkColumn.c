#include "area082_13.h"

/* func_801F3910 */
MATCH void Area_ClearWorkColumn(void) {
    s32 index;
    s8* cell;

    cell  = (s8*)AREA_WORK;
    index = 0;
    do {
        *cell = 0;
        index += 1;
        cell += 0x14;
    } while ((u32)(index & BYTE_MASK) < 0x80U);
}
