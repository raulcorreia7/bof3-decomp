#include "battle_15.h"

/* Sets the panel task's unk_08 byte to 2 and its y half to -5. */
/* func_8009FEAC */
MATCH void Battle_Heal5Ap(void) {
    g_Battle.target_record->target_flags = 2;
    g_Battle.target_record->ap_change    = -5;
}
