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
    half   = D_801CD945[(entity_index & BYTE_MASK) * 4];
    base_x = *(s32*)(D_80143F2C + (entity_index & BYTE_MASK) * 8);
    base_y = *(s32*)(D_80143F30 + (entity_index & BYTE_MASK) * 8);
loop:
    if (((count & BYTE_MASK) != (entity_index & BYTE_MASK)) && (D_801CD944[count & BYTE_MASK].active != 0)) {
        cand_half = D_801CD945[(count & BYTE_MASK) * 4];
        cand_x    = *(s32*)(D_80143F2C + (count & BYTE_MASK) * 8);
        cand_y    = *(s32*)(D_80143F30 + (count & BYTE_MASK) * 8);
        if ((func_801C7498(base_x, base_y, cand_x, cand_y, half, cand_half) & BYTE_MASK) == 0) {
            return 0;
        }
    }
    count += 1;
    if ((count & BYTE_MASK) < 3u) {
        /* goto form: the do-while shape hoists the table bases out of the loop. */
        goto loop;
    }
    return (func_801C7824(D_80143F26, D_80143F2A, D_80143F2E[entity_index & BYTE_MASK].unk_00,
                          (&D_80143F32)[(entity_index & BYTE_MASK) * 4]) &
            0xFF) != 0;
}
