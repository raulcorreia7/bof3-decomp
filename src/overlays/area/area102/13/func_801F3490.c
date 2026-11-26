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
        work  = TASK(Actor);
        x     = work->pos.x.fixed + (i + 1) * (work->vx << 16);
        y     = work->pos.y.fixed + (i + 1) * (work->vy << 16);
        index = Game_GetPartySize(x, y, 0);
        if (index < 0) {
            continue;
        }
        member      = &g_Game.members[index];
        saved       = TASK(Actor);
        g_GameState = member;
        TASK_SET(member);
        result = Char_CountEquipped(g_GameState->character_index, EQUIP_GROUP_ACCESSORY, 8);
        if (result == 0) {
            if ((g_Characters[g_GameState->character_index].status & 0x20) == 0) {
                Party_FlashDamage(PARTY_DAMAGE_COLOR_YELLOW);
            }
            Char_SetCharacterId(5);
        }
        TASK_SET(saved);
    }
    func_801F36B4(7);
    TASK(Actor)->timer++;
    if (TASK(Actor)->timer >= 0x1F) {
        TASK(Actor)->timer = 0x1F;
        TASK(Actor)->header.step++;
    }
}
