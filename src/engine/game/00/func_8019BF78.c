#include "game_00.h"

MATCH void func_8019BF78(void) {
    TASK(Actor)->param.unk_0B = (u8)Area_CellGetCode(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y));
    Area_CellSetCode(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y), 0x10);
}
