#include "area008_13.h"

MATCH void func_801F43C8(void) {
    TEXT_Format(g_TextVariables[0], D_801F2C14, g_ScriptVars[3] & 0x7F);
    MESSAGE_START_WAIT(MSG_AREA008_MASTER_TEST_PASSED);
    SND_BGMPlay(0xA, 0x64, 8);
}
