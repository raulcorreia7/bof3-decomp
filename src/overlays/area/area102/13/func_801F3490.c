#include "area102_13.h"

/* Points the game at the party member each of the two cells behind the actor
 * holds, applies that member's status change, then advances the step timer. */
MATCH void func_801F3490(void) {
    Actor*       work;
    PartyMember* member;
    Actor*       saved;
    s8           index;
    u8           result;
    s32          i;
    s32          x;
    s32          y;

    for (i = 0; i < 2; i++) {
        work  = g_Task;
        x     = work->pos.x.fixed + (i + 1) * (work->vx << 16);
        y     = work->pos.y.fixed + (i + 1) * (work->vy << 16);
        index = Game_GetPartySize(x, y, 0);
        if (index < 0) {
            continue;
        }
        member      = &g_Game.members[index];
        saved       = g_Task;
        g_GameState = member;
        TASK_SET(member);
        result = func_801C38F4(g_GameState->character_index, 3, 8);
        if (result == 0) {
            if ((g_Characters[g_GameState->character_index].status & 0x20) == 0) {
                func_801C308C(2);
            }
            Char_SetCharacterId(5);
        }
        TASK_SET(saved);
    }
    func_801F36B4(7);
    g_Task->timer++;
    if (g_Task->timer >= 0x1F) {
        g_Task->timer = 0x1F;
        g_Task->header.step++;
    }
}
