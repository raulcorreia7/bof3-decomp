#include "battle_15.h"

MATCH void func_800AE82C(void) {
    PartyMember* work;
    PartyMember* row_work;
    PartyMember* tail_work;
    u32          slot;
    u8           count;
    s32          value;

    work         = TASK(PartyMember);
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        row_work = TASK(PartyMember);
        slot     = row_work->param.unk_0B;
        if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
            row_work->pos.x.fixed = g_Game.members[slot].pos.x.fixed;
            row_work->pos.y.fixed = g_Game.members[row_work->param.unk_0B].pos.y.fixed;
            value                 = g_Game.members[row_work->param.unk_0B].pos.z.fixed;
        } else {
            row_work->pos.x.fixed = ENEMY_COMBATANT(row_work->param.unk_0B).pos.x.fixed;
            row_work->pos.y.fixed = ENEMY_COMBATANT(row_work->param.unk_0B).pos.y.fixed;
            value                 = ENEMY_COMBATANT(row_work->param.unk_0B).pos.z.fixed;
        }
        row_work->pos.z.fixed = value;
        Battle_ProjectRange();
        tail_work         = TASK(PartyMember);
        tail_work->unk_10 = -0xE;
        tail_work->unk_09 = 0;
        tail_work->screen_x.value -= 0x18;
        tail_work->screen_y.value -= tail_work->timer;
        TASK(PartyMember)->timer = 1;
        TASK(PartyMember)->header.mode += 1;
    }
}
