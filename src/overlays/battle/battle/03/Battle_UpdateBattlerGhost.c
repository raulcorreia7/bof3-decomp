#include "battle_03.h"

/* func_801E72A8 */
MATCH void Battle_UpdateBattlerGhost(void) {
    Callback handlers[2];

    handlers[0] = Battle_CopyBattlerGhost;
    handlers[SELF(PartyMember)->header.mode]();
}
