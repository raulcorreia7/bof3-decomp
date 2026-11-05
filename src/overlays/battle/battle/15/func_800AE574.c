#include "battle_15.h"

MATCH void func_800AE574(void) {
    /* FAKE: retail keeps the projected-frame pointer in v0. */
    MATCH_FAKE_PIN(u8*, third, "v0");
    PartyBattler* first;
    PartyBattler* second;
    PartyBattler* flag;
    PartyBattler* last;
    PartyBattler* source;
    u8            next;
    u16           height;
    u16           base;

    first = (PartyBattler*)g_Task;
    first->unk_09--;
    if (first->unk_09 != 0) {
        return;
    }

    source              = D_801EB4E0;
    second              = (PartyBattler*)g_Task;
    second->pos.x.fixed = source->pos.x.fixed;
    second->pos.y.fixed = source->pos.y.fixed;
    second->pos.z.fixed = source->pos.z.fixed;
    func_800AF764();

    third                   = TASK_BYTES;
    FIELD(u32, third, 0x10) = -0xE;
    /* FAKE: holds the work store ahead of the field reloads. */
    MATCH_FAKE_BARRIER();
    height = FIELD(u16, third, 0x2E);
    next   = FIELD(u8, third, 0xA);
    /* FAKE: holds the drop-byte load ahead of the base-halfword load. */
    MATCH_FAKE_BARRIER();
    base     = FIELD(u16, third, 0x30);
    third[9] = 0;
    height -= 0x18;
    FIELD(u16, third, 0x2E) = height;
    flag                    = (PartyBattler*)g_Task;
    base -= next;
    FIELD(u16, third, 0x30) = base;
    flag->timer             = 1;

    last       = (PartyBattler*)g_Task;
    last->mode = (u8)(last->mode + 1);
}
