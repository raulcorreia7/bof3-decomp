#include "plp015_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_PollScriptRequest.h"

MATCH void func_801CFAFC(void) {
    D_801CFBC8[SELF(Actor)->unk_2C]();
}

MATCH void func_801CFB40(void) {
    D_801CFBD4[SELF(Actor)->unk_2C]();
}
