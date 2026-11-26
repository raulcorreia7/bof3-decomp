#include "game_00.h"

MATCH void func_801B90A0(void) {
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
    Area_RequestLinkAtCell(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y));
    TASK(Actor)->vz = 0;
    Script_Request(TASK(Actor)->direction);
    TASK(Actor)->unk_03 = 1;
}
