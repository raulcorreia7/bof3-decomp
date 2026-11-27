#include "scena02_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F71A4(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    SYS_DISPATCH_INDEX(D_801FE288, index);
}

MATCH void func_801F71D8(void) {
    *g_Scenario2Flags = 0;
    g_ScriptVarsWord  = 0;
    D_80146872        = 1;
}
