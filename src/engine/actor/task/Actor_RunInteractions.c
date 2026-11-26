#include "engine/game/00/game_00.h"

/* func_801A06D8 */
MATCH u32 Actor_RunInteractions(void) {
    Actor* actor;
    u32    result;
    u8     i;
    u8     n;
    u8     j;
    u8     flags;

    result = g_Game.walk_flags & AREA_WALK_LEADER_SWITCH_ACTIVE;
    if (result == 0) {
        for (i = 0; i < ENTITY_MAX; i++) {
            actor = &g_Actors[i];
            SELF_SET(actor);
            g_CurrentActor = actor;
            if (!ACTOR_IN_USE(*actor)) {
                continue;
            }
            SP_REF(s8, 0x3) = 0;
            if (actor->timer == 0 && (g_Actors[i].interaction_flags & ACTOR_INTERACTION_SCRIPT_PENDING)) {
                if (g_Actors[i].interaction_flags & ACTOR_INTERACTION_SCRIPT_REQUEST) {
                    if ((s8)func_801A17A0(&g_Actors[i].interaction_flags) && !(SELF(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                        g_Actors[i].unk_79 = SELF(Actor)->direction & 0x7;
                        if (!(SELF(Actor)->option_flags & ACTOR_OPT_KEEP_FACING)) {
                            SELF(Actor)->direction = (g_Game.members[0].facing ^ 0x4) & 0x7;
                            Script_DispatchSelector(SELF(Actor)->direction);
                        } else {
                            Script_DispatchSelector(SELF(Actor)->direction & 0x7);
                        }
                        if (SELF(Actor)->header.mode == ACTOR_MODE_TURN) {
                            g_Actors[i].unk_79 |= 1;
                        }
                    }
                } else {
                    func_801A18C8(actor);
                }
            } else if (g_CurrentActor->interaction_flags & ACTOR_INTERACTION_PENDING) {
                func_801A3A08();
                continue;
            } else if (g_Actors[i].roll_90 >= 0x1F && SELF(Actor)->timer == 0) {
                func_801A27C4(&g_Actors[i]);
            } else {
                g_ActorModes[SELF(Actor)->header.mode](&g_Actors[i]);
            }
            if (SELF(Actor)->unk_06 == 0xA) {
                continue;
            }
            flags = g_Actors[i].interaction_flags;
            if (!(flags & 0x40)) {
                if (flags & ACTOR_INTERACTION_MOVING) {
                    Script_DispatchSelector(SELF(Actor)->direction);
                    g_Actors[i].interaction_flags &= ~ACTOR_INTERACTION_MOVING;
                } else if (!(SELF(Actor)->option_flags & ACTOR_OPT_WAIT_STREAM)) {
                    n = g_Actors[i].unk_78 - 2 < 0 ? 0 : g_Actors[i].unk_78 - 2;
                    j = 0;
                    do {
                        j++;
                        Script_AnimStepLoop();
                    } while (j <= n);
                }
            } else if (!(SELF(Actor)->option_flags & ACTOR_OPT_WAIT_STREAM)) {
                if (SELF(Actor)->header.flags & ACTOR_FLAG_STEP_MOVE) {
                    Script_AnimStepLoop();
                } else {
                    Script_AnimStepOnce();
                }
            }
        }
        result                 = (u16)g_EncounterSteps;
        g_ScenarioState.unk_08 = result;
    }
    return result;
}
