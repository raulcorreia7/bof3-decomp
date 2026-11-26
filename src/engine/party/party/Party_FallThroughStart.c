#include "engine/game/00/game_00.h"

/* func_801B90A0 */
/* Plays the fall sound and requests the area link of the cell. */
MATCH void Party_FallThroughStart(void) {
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
    Area_RequestLinkAtCell(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y));
    SELF(Actor)->vz = 0;
    Script_Request(SELF(Actor)->direction);
    SELF(Actor)->unk_03 = 1;
}
