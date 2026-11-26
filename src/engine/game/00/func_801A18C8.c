#include "game_00.h"

MATCH void func_801A18C8(Actor* record) {
    u8*    game_state;
    Actor* work;
    s32    state;

    work       = record;
    game_state = &g_GameStateIndex;
    state      = GAME_REQUEST_MESSAGE;
    if (*game_state != state) {
        if (work->callback_index != GAME_NONE) {
            Game_ScenarioDispatchRecord(record);
        }
        if (*game_state != state) {
            if (SELF(Actor)->unk_06 == 5) {
                D_8014865C          = ((s32)(-(((s32)work - (s32)g_Actors) * 0xD79435E5)) >> 3);
                g_MenuStep.step     = 0;
                g_MenuStep.sub_step = 0;
                g_GameEntryState    = GAME_MODE_SHOP;
                return;
            }
            if ((g_ScenarioState.flags_01 & SCENARIO_STATE_SCRIPT_ACTIVE) == 0) {
                if ((SELF(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
                    SELF(Actor)->direction = work->unk_79;
                    work->interaction_flags |= ACTOR_INTERACTION_MOVING;
                }
                g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            }
            work->interaction_flags &= ~ACTOR_INTERACTION_SCRIPT_PENDING;
        }
    }
}
