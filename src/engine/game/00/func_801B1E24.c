#include "game_00.h"

/* Arms the party members whose placement probes pass, then advances the party step once a later member is armed. */
#ifdef NON_MATCHING
NON_MATCHING void func_801B1E24(void) {
    PartyMember* member;
    s32          i;
    s8           prev;
    s32          index;
    s32          result;
    s32          state;
    u8           facing;

    facing = g_Game.members[0].facing;
    i      = 0;
    if (g_PartySize != 0) {
        member = &g_Game.members[0];
        do {
            TASK_SET(member);
            prev = i - 1;
            if (prev < 0) {
                prev = g_PartySize - 1;
            }
            if ((g_Game.members[0].status.field.flags.unsigned_value & 1) == 0 && prev != 0) {
                index  = (prev - 1) * 2 + facing * 4;
                result = func_801B1B2C(g_Game.members[0].pos.x.fixed + (s_EntityPlacementOffsets[index] << 15), g_Game.members[0].pos.y.fixed + (s_EntityPlacementOffsets[index + 1] << 15), facing,
                                       member->speed);
                if (((result & BYTE_MASK) != 0) && ((func_801B1C18(SP_REF(s32, 0x8u), SP_REF(s32, 0xCu), TASK(PartyMember)->speed) & BYTE_MASK) != 0)) {
                    goto found;
                }
                if ((func_801B1B2C(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, facing, TASK(PartyMember)->speed) & BYTE_MASK) == 0) {
                    goto next;
                }
            } else if ((func_801B1B2C(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, facing, member->speed) & BYTE_MASK) == 0) {
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
            i++;
            member++;
        } while (i < g_PartySize);
    }

    i = 1;
    TASK_SET(g_Game.members);
    state = 4;
    while (i < g_PartySize) {
        if (g_Game.members[i].header.mode == 3) {
            state = TASK(PartyMember)->header.step + 1;
            break;
        }
        i++;
    }
    TASK(PartyMember)->header.step = state;
}
#else
INCLUDE_ASM(func_801B1E24);
#endif
