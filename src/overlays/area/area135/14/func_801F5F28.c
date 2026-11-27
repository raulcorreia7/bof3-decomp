#include "area135_14.h"

/* Clears the height and stamps the cell codes of the two-by-two block of cells under the actor, one code byte of its gravity word per cell. */
MATCH void func_801F5F28(void) {
    s32 x;
    s32 y;
    u8  i;

    x = COORD_INT(SELF(Actor)->pos.x);
    y = COORD_INT(SELF(Actor)->pos.y);
    for (i = 0; i < 2; i++) {
        Area_HeightSet((s16)x, (s16)(i + y), 0);
        Area_CellSetCode((s16)x, (s16)y + i, (u8)(SELF(Actor)->gravity >> (i * 8)));
        Area_HeightSet((s16)((s16)x + 1), (s16)(i + y), 0);
        Area_CellSetCode((s16)x + 1, (s16)y + i, (u8)(SELF(Actor)->gravity >> ((i + 2) * 8)));
    }
}
