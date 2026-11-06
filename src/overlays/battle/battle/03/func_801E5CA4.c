#include "battle_03.h"

MATCH void func_801E5CA4(void) {
    BattleHandlerTable5 handlers;
    BattleEffect*       slot;
    BattleEffect*       work;

    handlers = D_801D0EF4;
    handlers.handlers[D_801EC2E0->mode]();
    if (ACTOR_IN_USE(*g_Task)) {
        switch (D_801EC2E0->unk_07) {
            case 0:
                slot = D_801EC2E0;
                if (slot->mode < 3U) {
                    Battle_DrawRollingDigits(slot->unk_27);
                } else {
                    Battle_DrawNumber((COORD_INT(slot->pos.x) - 0xC), COORD_INT(slot->pos.y), slot->unk_27,
                                      slot->word_60.capture_count);
                }
                break;
            case 1:
                work = D_801EC2E0;
                func_801D9804(COORD_INT(work->pos.x), COORD_INT(work->pos.y), work->unk_27, 2);
                break;
            case 2:
                work = D_801EC2E0;
                func_801D9804(COORD_INT(work->pos.x), COORD_INT(work->pos.y), work->unk_27, 1);
                break;
            case 3:
                work = D_801EC2E0;
                func_801D9804(COORD_INT(work->pos.x), COORD_INT(work->pos.y), work->unk_27, 0);
                break;
            case 4:
                break;
        }
    }
}
