#include "area040_13.h"

MATCH void func_801F369C(void) {
    s8 row;
    s8 col;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            func_801A4BC0(col + 0x94, row + 0x20, 0);
        }
    }
}
