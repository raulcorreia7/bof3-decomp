#include "area135_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5F28(void) {
    s16 x;
    s16 y;
    u8  i;

    x = COORD_INT(TASK(Actor)->pos.x);
    y = COORD_INT(TASK(Actor)->pos.y);
    for (i = 0; i < 2; i++) {
        Area_HeightSet(x, (s16)(y + i), 0);
        Area_CellSetCode(x, y + i, (u8)(TASK(Actor)->gravity >> (i * 8)));
        Area_HeightSet((s16)(x + 1), (s16)(y + i), 0);
        Area_CellSetCode(x + 1, y + i, (u8)(TASK(Actor)->gravity >> ((i + 2) * 8)));
    }
}
#else
INCLUDE_ASM(func_801F5F28);
#endif
