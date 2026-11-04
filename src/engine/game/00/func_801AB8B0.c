#include "game_00.h"

/* The retail caller loads the fifth argument with lh, so the declaration keeps
 * s16 although the definition names it u16; the low halfword is identical. */

MATCH s32 func_801AB8B0(GameCursorState* state, u8* table, s32 value) {
    switch (table[state->index_0A]) {
        case 0x90:
        case 0x91:
        case 0x92:
        case 0x93:
        case 0x94:
        case 0x95:
            g_SpadWork->unk_0B =
                func_8015CB18(table[state->index_0A] - 0x90, (s8)table[state->index_0A + 1],
                              (s8)table[state->index_0A + 2], (s16)g_SpadWork->unk_2E, (s16)g_SpadWork->unk_30);
            state->index_0A += 2;
            break;
        case 0x98:
        case 0x99:
        case 0x9A:
        case 0x9B:
        case 0x9C:
        case 0x9D:
            g_SpadWork->unk_0B = func_8015CC00(table[state->index_0A] - 0x98, (s8)table[state->index_0A + 1],
                                               (s8)table[state->index_0A + 2], g_SpadWork->x.fixed, g_SpadWork->y.fixed,
                                               g_SpadWork->z.fixed);
            state->index_0A += 2;
            break;
        case 0x9F:
            if (ACTOR_IN_USE(g_ActorSlots[g_SpadWork->unk_0B])) {
                state->index_0A -= 1;
            }
            break;
        default:
            break;
    }
    return value & BYTE_MASK;
}
