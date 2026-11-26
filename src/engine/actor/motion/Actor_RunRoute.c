#include "engine/game/00/game_00.h"

/* func_801A1384 */
/* Mode 4: runs the route script row of the area, starting its moves and fades. */
MATCH void Actor_RunRoute(void* entity) {
    u8* rec;
    u8* sub;
    u8  sel;
    u8  rate;
    u8  savedFlag;
    u16 savedState;
    u8  savedRoute;
    u8  mode;

    rec        = entity;
    savedRoute = TASK(Actor)->direction;
    savedState = LOHU(rec[0x7E]);
    savedFlag  = rec[0x76];
    if (TASK(Actor)->timer != 0) {
        goto only_update; /* the pending entity update runs alone */
    }
    mode = rec[0x78];
    rate = g_RouteSpeedScale[mode];
    if (rec[0x7B] == 0) {
        FAKE_ORDER_LOCK(sub = rec + 0x74); /* FAKE: order lock holds the pointer setup. */
        if (mode != 0) {
            sel = Script_Run(sub, (*(s32**)((u8*)g_AreaLoads[g_GameAreaId] + 0x10))[rec[0x77]]);
            if (rec[0x75] != 0) {
                Actor_StartRouteWait(sub);
            }
            if (sel == GAME_NONE) {
                return;
            }
            if (TASK(Actor)->direction != sel) {
                TASK(Actor)->direction = sel;
                rec[0x74] |= ACTOR_INTERACTION_MOVING;
            }
            if (rec[0x7B] != 0) {
                Actor* spad;
                TASK(Actor)->unk_0A = (0x10 / rate);
                rec[0x7B]--;
                if (((TASK(Actor)->option_flags & ACTOR_OPT_NO_TARGET) == 0) && ((Actor_IsAheadOccupied((Actor*)rec) << 0x18) != 0)) {
                    TASK(Actor)->direction &= 7;
                    rec[0x76] = savedFlag;
                    rec[0x7B] = 0;
                    rec[0x74] |= ACTOR_INTERACTION_MOVING | ACTOR_INTERACTION_SCRIPT_REQUEST;
                    spad            = TASK(Actor);
                    LOHU(rec[0x7E]) = savedState;
                    spad->timer     = 0;
                    return;
                }
            } else if ((TASK(Actor)->unk_06 == 0x0A) && ((LOW(rec[0x74]) & 0x88) == 8)) {
                TASK(Actor)->unk_0A = (0x10 / rate);
                TASK(s32)[3]        = 0;
                TASK(s32)[4]        = 0;
                TASK(s32)[5]        = 0;
            }
            if ((rec[0x74] & ACTOR_INTERACTION_FADE_WHITE) != 0) {
                TASK(Actor)->unk_03      = TASK(Actor)->header.mode;
                TASK(Actor)->header.mode = ACTOR_MODE_FADE_WHITE;
                TASK(Actor)->unk_04      = 0;
            }
            if ((rec[0x74] & ACTOR_INTERACTION_FADE_BLACK) != 0) {
                TASK(Actor)->unk_03      = TASK(Actor)->header.mode;
                TASK(Actor)->header.mode = ACTOR_MODE_FADE_BLACK;
                TASK(Actor)->unk_04      = 0;
            }
        }
    } else {
        if (((TASK(Actor)->option_flags & ACTOR_OPT_NO_TARGET) == 0) && ((Actor_IsAheadOccupied((Actor*)rec) << 0x18) != 0)) {
            TASK(Actor)->direction &= 7;
            rec[0x74]          = rec[0x74] | ACTOR_INTERACTION_MOVING | ACTOR_INTERACTION_SCRIPT_REQUEST;
            TASK(Actor)->timer = 0;
            return;
        }
        TASK(Actor)->unk_0A = (0x10 / rate);
        rec[0x7B]--;
        Area_MoveActorRoute(rec + 0x74, TASK(Actor)->direction & 0x7);
        TASK(Actor)->direction |= 8;
        rec[0x74] |= ACTOR_INTERACTION_MOVING;
    }
    func_801A2AE4((Actor*)rec, savedRoute);
only_update:
    Area_SetXFixed((Actor*)rec);
}
