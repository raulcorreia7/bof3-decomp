#include "game_00.h"

MATCH void func_8019F430(void) {
    s32    heightOffset;
    s32    step;
    Actor* record;
    Actor* slot;
    Actor* work;

    record = TASK(Actor);
    step   = record->vy + 0x14000;
    record->pos.y.fixed += step;
    record->vy = step;
    if (COORD_INT(record->pos.y) >= 0) {
        record->timer     = 6;
        work              = TASK(Actor);
        record->vy        = (s32)-record->vy;
        work->header.mode = (u8)(work->header.mode + 1);
    }
    slot         = TASK(Actor);
    heightOffset = slot->param.party_index * BATTLE_PARTY_STRIDE;
    Actor_DrawValueDigits(*(s16*)((u8*)((u8*)&g_Game.members[0].screen_x) + heightOffset), (s16)(*(u16*)((u8*)((u8*)&g_Game.members[0].screen_y) + heightOffset) + (u16)COORD_INT(slot->pos.y)),
                          slot->unk_06, slot->clut_select);
}
