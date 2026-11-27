#include "area139_13.h"

MATCH void func_801F308C(s32 mode) {
    s32 i;
    u8  index;
    u8* table;

    mode &= BYTE_MASK;
    if (mode == 0) {
        i     = 0;
        table = &D_801F442C[0x14];
        do {
            SELF(Actor)->pos.x.fixed = 0x5C0000;
            SELF(Actor)->pos.y.fixed = (s32)table[(u8)i] << 16;
            index                    = Game_GetPartySize(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 0);
            if (index != GAME_NONE && (g_Game.walk_flags & (AREA_WALK_TRANSITION | AREA_WALK_LEADER_SWITCH_ACTIVE)) == 0 && g_GameStateIndex == GAME_REQUEST_IDLE) {
                if (SELF(Actor)->pos.x.fixed - g_Game.members[index].pos.x.fixed > 0) {
                    g_Game.members[index].facing = 3;
                } else {
                    g_Game.members[index].facing = 7;
                }
                func_8015C214(index, 2);
            }
            i++;
        } while ((u8)i < 4);
    } else if (mode == 1) {
        i     = 0;
        table = &D_801F442C[0x18];
        do {
            SELF(Actor)->pos.x.fixed = (s32)table[(u8)i] << 16;
            SELF(Actor)->pos.y.fixed = 0x440000;
            index                    = Game_GetPartySize(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 0);
            if (index != GAME_NONE && (g_Game.walk_flags & (AREA_WALK_TRANSITION | AREA_WALK_LEADER_SWITCH_ACTIVE)) == 0 && g_GameStateIndex == GAME_REQUEST_IDLE) {
                if (SELF(Actor)->pos.y.fixed - g_Game.members[index].pos.y.fixed > 0) {
                    g_Game.members[index].facing = 5;
                } else {
                    g_Game.members[index].facing = 1;
                }
                func_8015C214(index, 2);
            }
            i++;
        } while ((u8)i < 4);
    }
}
