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

    first = (PartyBattler*)g_SpadWork;
    first->word_08.byte.unk_09--;
    if (first->word_08.byte.unk_09 != 0) {
        return;
    }

    source                 = D_801EB4E0;
    second                 = (PartyBattler*)g_SpadWork;
    second->coord_x_34.raw = source->coord_x_34.raw;
    second->coord_y_38.raw = source->coord_y_38.raw;
    second->word_3C.word   = source->word_3C.word;
    func_800AF764();

    third                   = g_SpadWork;
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
    flag                    = (PartyBattler*)g_SpadWork;
    base -= next;
    FIELD(u16, third, 0x30)   = base;
    flag->word_08.byte.unk_0A = 1;

    last          = (PartyBattler*)g_SpadWork;
    last->step_01 = (u8)(last->step_01 + 1);
}
