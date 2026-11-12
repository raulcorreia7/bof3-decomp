#include "area139_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F308C(u8 mode) {
    s32 facing;
    u8* line;
    u8  code;
    u8  i;

    if (mode == 0) {
        i    = 0;
        line = D_801F4440;
        do {
            g_Task->pos.x.fixed = TO_COORD(92);
            g_Task->pos.y.fixed = line[i] << 16;
            code                = func_801BE0C0(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0);
            if (code != GAME_NONE && !(g_Game.walk_flags & (AREA_WALK_LEADER_SWITCH_ACTIVE | AREA_WALK_TRANSITION)) && g_GameStateIndex == GAME_REQUEST_IDLE) {
                facing                      = (g_Task->pos.x.fixed - g_Game.members[code].pos.x.fixed) > 0 ? FACING_RIGHT : FACING_LEFT;
                g_Game.members[code].facing = facing;
                func_8015C214(code, 2);
            }
            i++;
        } while (i < 4);
    } else if (mode == 1) {
        i    = 0;
        line = D_801F4444;
        do {
            g_Task->pos.y.fixed = TO_COORD(68);
            g_Task->pos.x.fixed = line[i] << 16;
            code                = func_801BE0C0(line[i] << 16, TO_COORD(68), 0);
            if (code != GAME_NONE && !(g_Game.walk_flags & (AREA_WALK_LEADER_SWITCH_ACTIVE | AREA_WALK_TRANSITION)) && g_GameStateIndex == GAME_REQUEST_IDLE) {
                facing                      = (g_Task->pos.y.fixed - g_Game.members[code].pos.y.fixed) > 0 ? FACING_DOWN : FACING_UP;
                g_Game.members[code].facing = facing;
                func_8015C214(code, 2);
            }
            i++;
        } while (i < 4);
    }
}
#else
INCLUDE_ASM(func_801F308C);
#endif
