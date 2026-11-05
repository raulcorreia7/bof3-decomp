#include "area068_13.h"

MATCH void func_801F2DE8(void) {
    u8 pick;

    pick               = rand() & 0xF;
    D_801F4DFC         = D_801F3FE4[pick];
    D_801F4E00         = D_801F3FE4[pick];
    D_801F4E0C         = 0;
    D_801F4E10         = 0;
    D_801F4E14         = 0;
    D_801F4E04         = 0;
    D_801F4E08         = 0;
    g_SpadWork->unk_01 = 1;
}
