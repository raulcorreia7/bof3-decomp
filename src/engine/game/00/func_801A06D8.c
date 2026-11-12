#include "game_00.h"

MATCH u32 func_801A06D8(void) {
    Actor* row;
    u32    result;
    u8     i;
    u8     n;
    u8     j;
    u8     flags;

    result = g_Game.walk_flags & AREA_WALK_LEADER_SWITCH_ACTIVE;
    if (result == 0) {
        for (i = 0; i < ENTITY_MAX; i++) {
            row            = &g_Actors[i];
            g_Task         = row;
            g_CurrentActor = row;
            if (!ACTOR_IN_USE(*row)) {
                continue;
            }
            SP_REF(s8, 0x3) = 0;
            if (row->timer == 0 && (g_Actors[i].interaction_flags & ACTOR_FLAG_SCRIPT_PENDING)) {
                if (g_Actors[i].interaction_flags & ACTOR_FLAG_SCRIPT_REQUEST) {
                    if ((s8)func_801A17A0(&g_Actors[i].interaction_flags) && !(g_Task->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                        g_Actors[i].unk_79 = g_Task->direction_08 & 0x7;
                        if (!(g_Task->option_flags & ACTOR_OPT_KEEP_FACING)) {
                            g_Task->direction_08 = (g_Game.members[0].facing ^ 0x4) & 0x7;
                            func_8015BAC4(g_Task->direction_08);
                        } else {
                            func_8015BAC4(g_Task->direction_08 & 0x7);
                        }
                        if (g_Task->header.mode == 0xA) {
                            g_Actors[i].unk_79 |= 1;
                        }
                    }
                } else {
                    func_801A18C8(row);
                }
            } else if (g_CurrentActor->interaction_flags & ACTOR_FLAG_INTERACTION_PENDING) {
                func_801A3A08();
                continue;
            } else if (g_Actors[i].roll_90 >= 0x1F && g_Task->timer == 0) {
                func_801A27C4(&g_Actors[i]);
            } else {
                D_801C83D8[g_Task->header.mode](&g_Actors[i]);
            }
            if (g_Task->unk_06 == 0xA) {
                continue;
            }
            flags = g_Actors[i].interaction_flags;
            if (!(flags & 0x40)) {
                if (flags & ACTOR_FLAG_MOVING) {
                    func_8015BAC4(g_Task->direction_08);
                    g_Actors[i].interaction_flags &= ~ACTOR_FLAG_MOVING;
                } else if (!(g_Task->option_flags & ACTOR_OPT_WAIT_STREAM)) {
                    n = g_Actors[i].unk_78 - 2 < 0 ? 0 : g_Actors[i].unk_78 - 2;
                    j = 0;
                    do {
                        j++;
                        Actor_StepAnimLoop();
                    } while (j <= n);
                }
            } else if (!(g_Task->option_flags & ACTOR_OPT_WAIT_STREAM)) {
                if (g_Task->header.flags & ACTOR_FLAG_STEP_MOVE) {
                    Actor_StepAnimLoop();
                } else {
                    Actor_StepAnimOnce();
                }
            }
        }
        result     = (u16)g_EncounterSteps;
        D_80146878 = result;
    }
    return result;
}
