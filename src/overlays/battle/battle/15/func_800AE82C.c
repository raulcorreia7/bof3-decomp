#include "battle_15.h"

MATCH void func_800AE82C(void) {
    PartyMember* work;
    PartyMember* member;
    PartyMember* task;
    u32          slot;
    u8           count;
    s32          value;

    work         = SELF(PartyMember);
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        member = SELF(PartyMember);
        slot   = member->param.unk_0B;
        if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
            member->pos.x.fixed = g_Game.members[slot].pos.x.fixed;
            member->pos.y.fixed = g_Game.members[member->param.unk_0B].pos.y.fixed;
            value               = g_Game.members[member->param.unk_0B].pos.z.fixed;
        } else {
            member->pos.x.fixed = ENEMY_COMBATANT(member->param.unk_0B).pos.x.fixed;
            member->pos.y.fixed = ENEMY_COMBATANT(member->param.unk_0B).pos.y.fixed;
            value               = ENEMY_COMBATANT(member->param.unk_0B).pos.z.fixed;
        }
        member->pos.z.fixed = value;
        Battle_ProjectRange();
        task         = SELF(PartyMember);
        task->unk_10 = -0xE;
        task->unk_09 = 0;
        task->screen_x.value -= 0x18;
        task->screen_y.value -= task->timer;
        SELF(PartyMember)->timer = 1;
        SELF(PartyMember)->header.mode += 1;
    }
}
