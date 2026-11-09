#include "area030_04.h"

/* Clears the scratch-record flag when the AREA030 state byte is >= 10. */
MATCH void func_801E023C(void) {
    if (D_80145E93[0] >= 10u) {
        *SP_REF(volatile u8*, 0x44u) = 0u;
    }
}
