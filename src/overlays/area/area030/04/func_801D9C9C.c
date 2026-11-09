#include "area030_04.h"

/* When byte `D_80144199` equals 4, increments byte `D_8014403D`. */
MATCH void func_801D9C9C(void) {
    if (D_80144199 == 4) {
        D_8014403D += 1;
        FISHING_STATE->mode_index_02 += 1;
        FISHING_STATE->sub_index_03 = 0;
    }
}
