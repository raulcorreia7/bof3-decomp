#include "game_00.h"

MATCH s32 func_801C6888(s32 entity_index) {
    s32 base_x;
    s32 base_y;
    u8  half;
    s32 count;
    s32 cand_x;
    s32 cand_y;
    u8  cand_half;

    count  = 0;
    half   = D_801CD945[(entity_index & 0xFF) * 4];
    base_x = *(s32*)(D_80143F2C + (entity_index & 0xFF) * 8);
    base_y = *(s32*)(D_80143F30 + (entity_index & 0xFF) * 8);
loop:
    if (((count & 0xFF) != (entity_index & 0xFF)) && (D_801CD944[count & 0xFF].active != 0)) {
        cand_half = D_801CD945[(count & 0xFF) * 4];
        cand_x    = *(s32*)(D_80143F2C + (count & 0xFF) * 8);
        cand_y    = *(s32*)(D_80143F30 + (count & 0xFF) * 8);
        if ((func_801C7498(base_x, base_y, cand_x, cand_y, half, cand_half) & 0xFF) == 0) {
            return 0;
        }
    }
    count += 1;
    if ((count & 0xFF) < 3u) {
        /* goto form: the do-while shape hoists the table bases out of the loop. */
        goto loop;
    }
    return (func_801C7824(D_80143F26, D_80143F2A, D_80143F2E[entity_index & 0xFF].unk_00,
                          (&D_80143F32)[(entity_index & 0xFF) * 4]) &
            0xFF) != 0;
}
