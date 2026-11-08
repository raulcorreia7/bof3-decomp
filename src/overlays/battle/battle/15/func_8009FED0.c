#include "battle_15.h"

/* Sets the panel task's unk_08 byte to 2 and its y half to -40. */
MATCH void func_8009FED0(void) {
    g_Battle.target_record->target_flags = 2;
    g_Battle.target_record->ap_change    = -0x28;
}
