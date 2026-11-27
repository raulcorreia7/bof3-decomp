#include "game_00.h"

MATCH void func_8019F384(void) {
    s32 offset;

    SELF(Actor)->timer -= 1;
    offset = SELF(Actor)->param.party_index * BATTLE_PARTY_STRIDE;
    Actor_DrawValueDigits(*(s16*)(((u8*)&g_Game.members[0].screen_x) + offset), (s16)(*(u16*)(((u8*)&g_Game.members[0].screen_y) + offset) + (u16)COORD_INT(SELF(Actor)->pos.y)), SELF(Actor)->unk_06,
                          SELF(Actor)->clut_select);
    if (SELF(Actor)->timer == 0) {
        SELF(Actor)->header.mode += 1;
    }
}
