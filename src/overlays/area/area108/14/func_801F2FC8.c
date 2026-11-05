#include "area108_14.h"

MATCH void func_801F2FC8(void) {
    u8 i;

    D_801F63EC = MEM_PTR(u8, 0x800E4800u);
    i          = 0u;
    do {
        func_801F2F1C(D_801F63EC);
        D_801F63EC += 0x28;
        i += 1u;
    } while (i < 16u);
}
