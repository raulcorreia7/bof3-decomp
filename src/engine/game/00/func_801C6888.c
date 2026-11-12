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
    half   = D_801CD944[entity_index & BYTE_MASK].key;
    base_x = g_EncounterParty[entity_index & BYTE_MASK].x.fixed;
    base_y = g_EncounterParty[entity_index & BYTE_MASK].y.fixed;
loop:
    if (((count & BYTE_MASK) != (entity_index & BYTE_MASK)) && (D_801CD944[count & BYTE_MASK].active != 0)) {
        cand_half = D_801CD944[count & BYTE_MASK].key;
        cand_x    = g_EncounterParty[count & BYTE_MASK].x.fixed;
        cand_y    = g_EncounterParty[count & BYTE_MASK].y.fixed;
        if ((func_801C7498(base_x, base_y, cand_x, cand_y, half, cand_half) & BYTE_MASK) == 0) {
            return 0;
        }
    }
    count += 1;
    if ((count & BYTE_MASK) < 3u) {
        goto loop;
    }
    return (func_801C7824(D_80143F26, D_80143F2A, COORD_INT(g_EncounterParty[entity_index & BYTE_MASK].x), COORD_INT(g_EncounterParty[entity_index & BYTE_MASK].y)) & BYTE_MASK) != 0;
}
