#include "plp025_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_PollScriptRequest.h"

MATCH void func_801CFF20(void) {
    D_801CFFEC[SELF(Actor)->unk_2C]();
}

MATCH void func_801CFF64(void) {
    D_801CFFF8[SELF(Actor)->unk_2C]();
}
