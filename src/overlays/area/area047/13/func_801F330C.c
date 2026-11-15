#include "area047_13.h"

void func_801F2F60(u8* row);

#ifdef NON_MATCHING
NON_MATCHING u8 func_801F330C(void) {
    u8*  row;
    s32* party_position;
    s32  alive;
    u8   i;
    u8   timer;

    alive          = 0;
    row            = MEM_PTR(u8, AREA_WORK);
    party_position = &g_Game.members[0].pos.x.fixed;
    i              = 0;
    do {
        if (row[AREA_ROW_FLAG_OFFSET] != 0) {
            alive = 1;
            if (row[AREA_ROW_FLAG_OFFSET + 1] == 0) {
                *(s16*)(row + 0x10)           = 0;
                *(s16*)(row + 0x12)           = 0x10;
                row[AREA_ROW_FLAG_OFFSET + 3] = 0x20;
                row[AREA_ROW_FLAG_OFFSET + 2] = 0x20;
                row[AREA_ROW_FLAG_OFFSET + 1] += 1;
            } else if (row[AREA_ROW_FLAG_OFFSET + 1] == 1) {
                ((s32*)row)[0] = party_position[0];
                timer          = row[AREA_ROW_FLAG_OFFSET + 2] - 1;
                ((s32*)row)[1] = party_position[1];
                ((s32*)row)[2] = party_position[2] + 0x800000;
                row[AREA_ROW_FLAG_OFFSET + 3] -= 1;
                row[AREA_ROW_FLAG_OFFSET + 2] = timer;
                if (timer == 0) {
                    row[AREA_ROW_FLAG_OFFSET] = 0;
                }
                *(s16*)(row + 0x10) = *(s16*)(row + 0x10) + 8;
                func_801F2F60(row);
            }
        }
        row += AREA_ROW_STRIDE;
        i++;
    } while (i < AREA_ROW_COUNT);
    return alive;
}
#else
INCLUDE_ASM(func_801F330C);
#endif
