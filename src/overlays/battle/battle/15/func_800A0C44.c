#include "battle_15.h"

/* Sets the panel task's unk_08 byte to 2 and its y half to -10. */
MATCH void func_800A0C44(void) {
    g_BattleTargetRecord->target_flags = 2;
    g_BattleTargetRecord->ap_change    = -10;
}
