#include "engine/game/00/game_00.h"

/* Gathers the party for a leader swap: each member takes its formation spot or the leader's, then the swap advances while one is moving. */
/* func_801B1E24 */
MATCH void Game_LeaderSwitchGather(void) {
    /* FAKE: retail frame reserves 8 bytes no statement uses. */
    FAKE_STACK_PADS(u8, 8);
    PartyMember* leader;
    PartyMember* member;
    s32          i;
    s8           slot;
    u8           count;
    u8           facing;
    s32          ok;
    s32          placed;
    s32          index;

    count  = g_PartySize;
    facing = g_Game.members[0].facing;
    i      = 0;
    if (count != 0) {
        leader = &g_Game.members[0];
        do {
            member = &leader[i];
            TASK_SET(member);
            slot = i - 1;
            if (slot < 0) {
                slot = count - 1;
            }
            if (!(leader->status.field.flags.unsigned_value & 1) && slot != 0) {
                index  = (slot - 1) * 2 + facing * 4;
                ok     = func_801B1B2C(leader->pos.x.fixed + (s_EntityPlacementOffsets[index] << 15), leader->pos.y.fixed + (s_EntityPlacementOffsets[index + 1] << 15), facing, member->speed);
                placed = (ok & BYTE_MASK) ? func_801B1C18(SPAD(0u)->cells.words[2], SPAD(0u)->cells.words[3], TASK(PartyMember)->speed) : 0;
                if ((ok & BYTE_MASK) && (placed & BYTE_MASK)) {
                    goto found;
                }
                if (!(func_801B1B2C(D_80145EC4, D_80145EC8, facing, TASK(PartyMember)->speed) & BYTE_MASK)) {
                    goto next;
                }
            } else if (!(func_801B1B2C(leader->pos.x.fixed, leader->pos.y.fixed, facing, member->speed) & BYTE_MASK)) {
                goto next;
            }
        found:
            if (i != 0) {
                Party_BattlersClearState(i & BYTE_MASK);
                TASK(PartyMember)->header.mode = 3;
                Actor_SetSemiTransparent();
                TASK(PartyMember)->unk_5C = 1;
            }
        next:
            count = g_PartySize;
            i++;
        } while (i < count);
    }
    TASK_SET(g_Game.members);
    for (i = 1; i < g_PartySize; i++) {
        if (g_Game.members[i].header.mode == 3) {
            TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
            return;
        }
    }
    TASK(PartyMember)->header.step = 4;
}
