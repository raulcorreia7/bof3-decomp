#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801B1E24(void) {
    PartyMember* rows;
    PartyMember* row;
    s32          i;
    s8           prev;
    s32          index;
    s32          result;
    s32          state;
    s32          offset;
    u8           value;
    u8*          base;
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);

    base  = (u8*)&g_Game.members[0].facing;
    value = *base;
    i     = 0;
    if (g_Game.party_size != 0) {
        rows = (PartyMember*)(base - 8);
        row  = rows;
        do {
            TASK_SET(row);
            prev = i - 1;
            if (prev < 0) {
                prev = g_Game.party_size - 1;
            }
            if (!(rows->header.flags & 1) && prev != 0) {
                index  = (prev - 1) * 2 + (value & BYTE_MASK) * 4;
                result = func_801B1B2C(rows->pos.x.fixed + (s_EntityPlacementOffsets[index] << 15), rows->pos.y.fixed + (D_801CD08D[index] << 15), value & BYTE_MASK, row->speed);
                if (((result & BYTE_MASK) != 0) && ((func_801B1C18(SP_REF(s32, 8), SP_REF(s32, 0xC), TASK(PartyMember)->speed) & 0xFF) != 0)) {
                    goto found; /* first position test matched: run the row mark */
                }
                if (!(func_801B1B2C(D_80145EC4, D_80145EC8, value & BYTE_MASK, TASK(PartyMember)->speed) & 0xFF)) {
                    goto next; /* fallback position rejected: next row */
                }
            } else if (!(func_801B1B2C(rows->pos.x.fixed, rows->pos.y.fixed, value & BYTE_MASK, row->speed) & BYTE_MASK)) {
                goto next; /* fallback position rejected: next row */
            }
        found:
            if (i != 0) {
                Party_BattlersClearState(i & BYTE_MASK);
                g_Task->header.mode = 3;
                Actor_SetSemiTransparent();
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
