#include "game_00.h"

MATCH void func_8019F384(void) {
    s32 offset;

    TASK(Actor)->timer -= 1;
    offset = TASK(Actor)->param.party_index * BATTLE_PARTY_STRIDE;
    Actor_DrawValueDigits(*(s16*)(((u8*)&g_Game.members[0].screen_x) + offset), (s16)(*(u16*)(((u8*)&g_Game.members[0].screen_y) + offset) + (u16)COORD_INT(TASK(Actor)->pos.y)), TASK(Actor)->unk_06,
                          TASK(Actor)->clut_select);
    if (TASK(Actor)->timer == 0) {
        TASK(Actor)->header.mode += 1;
    }
}
