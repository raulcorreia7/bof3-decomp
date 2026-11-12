#include "battle_15.h"

MATCH void func_800AE574(void) {
    /* FAKE: retail keeps the projected-frame pointer in v0. */
    FAKE_REG(u8*, third, "v0");
    PartyMember* first;
    PartyMember* second;
    PartyMember* flag;
    PartyMember* last;
    PartyMember* source;
    u8           next;
    u16          height;
    u16          base;

    first = (PartyMember*)g_Task;
    first->unk_09--;
    if (first->unk_09 != 0) {
        return;
    }

    source = g_BattleEffectBattler;
    second = (PartyMember*)g_Task;
    WorldPos_Copy(&second->pos, &source->pos);
    Battle_ProjectRange();

    third                   = TASK_BYTES;
    FIELD(u32, third, 0x10) = -0xE;
    /* FAKE: holds the work store ahead of the field reloads. */
    FAKE_BARRIER();
    height = FIELD(u16, third, 0x2E);
    next   = FIELD(u8, third, 0xA);
    /* FAKE: holds the drop-byte load ahead of the base-halfword load. */
    FAKE_BARRIER();
    base     = FIELD(u16, third, 0x30);
    third[9] = 0;
    height -= 0x18;
    FIELD(u16, third, 0x2E) = height;
    flag                    = (PartyMember*)g_Task;
    base -= next;
    FIELD(u16, third, 0x30) = base;
    flag->timer             = 1;

    last              = (PartyMember*)g_Task;
    last->header.mode = (last->header.mode + 1);
}
