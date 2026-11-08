#include "battle_15.h"

/* Sets the panel task's unk_08 byte to 2 and its y half to -5. */
MATCH void func_8009FEAC(void) {
    g_Battle.target_record->target_flags = 2;
    g_Battle.target_record->ap_change    = -5;
}
