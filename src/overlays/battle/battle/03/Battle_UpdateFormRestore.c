#include "battle_03.h"

/* func_801E862C */
MATCH void Battle_UpdateFormRestore(void) {
    ACTOR_RUN_MODE_HANDLER(Battle_StartFormRestore, Battle_EndFormRestore);
}
