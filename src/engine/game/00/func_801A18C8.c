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
            Game_DispatchScenarioRecord(record);
        }
        if (*game_state != state) {
            if (g_SpadWork->unk_06 == 5) {
                D_8014865C       = (s8)((s32)(-(((s32)work - (s32)g_Actors) * 0xD79435E5)) >> 3);
                D_80148650       = 0;
                D_80148651       = 0;
                g_GameEntryState = 7;
                return;
            }
            if ((D_80146871 & 0x40) == 0) {
                if ((g_SpadWork->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
                    g_SpadWork->direction_08 = work->unk_79;
                    work->flags_74 |= ACTOR_FLAG_MOVING;
                }
                g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            }
            work->flags_74 &= ~ACTOR_FLAG_SCRIPT_PENDING;
        }
    }
}
