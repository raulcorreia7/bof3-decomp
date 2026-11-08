#include "game_00.h"

/* One 0x140-byte battle work row. Only the fields this unit reads are named. */
typedef struct BattleWorkSlot {
    u8  flags;
    u8  mode;
    u8  step;
    u8  pad_03[0x31];
    s32 x;
    s32 y;
    u8  pad_3C[0x34];
    u8  speed_70;
    u8  pad_71[0xBB];
    u8  flags_12C;
    u8  pad_12D[0x13];
} BattleWorkSlot;

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 58.67%. resume: a lever or header
 * fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_801B1E24(void) {
    BattleWorkSlot* rows;
    BattleWorkSlot* row;
    s32             i;
    s8              prev;
    s32             index;
    s32             result;
    s32             state;
    s32             offset;
    u8              value;
    u8*             base;
    /* FAKE: unused frame, 8 bytes. */
    STACK_PADS(u8, 8);

    base  = (u8*)&g_Game.members[0].facing;
    value = *base;
    i     = 0;
    if (g_Game.party_size != 0) {
        rows = (BattleWorkSlot*)(base - 8);
        row  = rows;
        do {
            TASK_SET(row);
            prev = i - 1;
            if (prev < 0) {
                prev = g_Game.party_size - 1;
            }
            if (!(rows->flags_12C & 1) && prev != 0) {
                index  = (prev - 1) * 2 + (value & BYTE_MASK) * 4;
                result = func_801B1B2C(rows->x + (s_EntityPlacementOffsets[index] << 15),
                                       rows->y + (D_801CD08D[index] << 15), value & BYTE_MASK, row->speed_70);
                if (((result & BYTE_MASK) != 0) &&
                    ((func_801B1C18(SP_REF(s32, 8), SP_REF(s32, 0xC), ((BattleWorkSlot*)g_Task)->speed_70) & 0xFF) !=
                     0)) {
                    goto found; /* first position test matched: run the row mark */
                }
                if (!(func_801B1B2C(D_80145EC4, D_80145EC8, value & BYTE_MASK, ((BattleWorkSlot*)g_Task)->speed_70) &
                      0xFF)) {
                    goto next; /* fallback position rejected: next row */
                }
            } else if (!(func_801B1B2C(rows->x, rows->y, value & BYTE_MASK, row->speed_70) & BYTE_MASK)) {
                goto next; /* fallback position rejected: next row */
            }
        found:
            if (i != 0) {
                Party_ClearBattlerState(i & BYTE_MASK);
                g_Task->header.mode = 3;
                func_801C2438();
                g_Task->tint.bytes.flags = 1;
            }
        next:
            i++;
            row++;
        } while (i < g_Game.party_size);
    }

    i = 1;
    TASK_SET(g_Game.members);
    offset = BATTLE_PARTY_STRIDE;
    while (i < g_Game.party_size) {
        if (D_80145E91[offset] == 3) {
            state = g_Task->header.step + 1;
            goto store; /* row not in state 3: keep the incremented state */
        }
        i++;
        offset += BATTLE_PARTY_STRIDE;
    }
    state = 4;
store:
    g_Task->header.step = state;
}
#else
INCLUDE_ASM(func_801B1E24);
#endif
