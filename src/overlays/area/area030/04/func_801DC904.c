#include "area030_04.h"

/* Increments the AREA030 scratchpad panel field at offset 3 when the global flag D_80144281 equals 3. */
MATCH void func_801DC904(void) {
    volatile u8* scratch;
    u8           flag;

    flag = D_80144281;
    if (flag == 3u) {
        scratch    = SP_REF(volatile u8*, 0x44u);
        scratch[3] = (scratch[3] + 1u);
    }
}
