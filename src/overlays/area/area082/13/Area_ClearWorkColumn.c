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
    } while ((index & 0xFF) < 0x80U);
}
