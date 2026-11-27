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
    savedRoute = SELF(Actor)->direction;
    savedState = LOHU(rec[0x7E]);
    savedFlag  = rec[0x76];
    if (SELF(Actor)->timer != 0) {
        goto only_update; /* the pending entity update runs alone */
    }
    mode = rec[0x78];
    rate = g_RouteSpeedScale[mode];
    if (rec[0x7B] == 0) {
        do {
            sub = rec + 0x74;
        } while (0); /* FAKE: the block holds the pointer setup. */
        if (mode != 0) {
            sel = Script_Run(sub, (*(s32**)((u8*)g_AreaLoads[g_GameAreaId] + 0x10))[rec[0x77]]);
            if (rec[0x75] != 0) {
                Actor_StartRouteWait(sub);
            }
            if (sel == GAME_NONE) {
                return;
            }
            if (SELF(Actor)->direction != sel) {
                SELF(Actor)->direction = sel;
                rec[0x74] |= ACTOR_INTERACTION_MOVING;
            }
            if (rec[0x7B] != 0) {
                Actor* spad;
                SELF(Actor)->unk_0A = (0x10 / rate);
                rec[0x7B]--;
                if (((SELF(Actor)->option_flags & ACTOR_OPT_NO_TARGET) == 0) && ((Actor_IsAheadOccupied((Actor*)rec) << 0x18) != 0)) {
                    SELF(Actor)->direction &= 7;
                    rec[0x76] = savedFlag;
                    rec[0x7B] = 0;
                    rec[0x74] |= ACTOR_INTERACTION_MOVING | ACTOR_INTERACTION_SCRIPT_REQUEST;
                    spad            = SELF(Actor);
                    LOHU(rec[0x7E]) = savedState;
                    spad->timer     = 0;
                    return;
                }
            } else if ((SELF(Actor)->unk_06 == 0x0A) && ((LOW(rec[0x74]) & 0x88) == 8)) {
                SELF(Actor)->unk_0A = (0x10 / rate);
                SELF(s32)[3]        = 0;
                SELF(s32)[4]        = 0;
                SELF(s32)[5]        = 0;
            }
            if ((rec[0x74] & ACTOR_INTERACTION_FADE_WHITE) != 0) {
                SELF(Actor)->unk_03      = SELF(Actor)->header.mode;
                SELF(Actor)->header.mode = ACTOR_MODE_FADE_WHITE;
                SELF(Actor)->unk_04      = 0;
            }
            if ((rec[0x74] & ACTOR_INTERACTION_FADE_BLACK) != 0) {
                SELF(Actor)->unk_03      = SELF(Actor)->header.mode;
                SELF(Actor)->header.mode = ACTOR_MODE_FADE_BLACK;
                SELF(Actor)->unk_04      = 0;
            }
        }
    } else {
        if (((SELF(Actor)->option_flags & ACTOR_OPT_NO_TARGET) == 0) && ((Actor_IsAheadOccupied((Actor*)rec) << 0x18) != 0)) {
            SELF(Actor)->direction &= 7;
            rec[0x74]          = rec[0x74] | ACTOR_INTERACTION_MOVING | ACTOR_INTERACTION_SCRIPT_REQUEST;
            SELF(Actor)->timer = 0;
            return;
        }
        SELF(Actor)->unk_0A = (0x10 / rate);
        rec[0x7B]--;
        Area_MoveActorRoute(rec + 0x74, SELF(Actor)->direction & 0x7);
        SELF(Actor)->direction |= 8;
        rec[0x74] |= ACTOR_INTERACTION_MOVING;
    }
    func_801A2AE4((Actor*)rec, savedRoute);
only_update:
    Area_SetXFixed((Actor*)rec);
}
