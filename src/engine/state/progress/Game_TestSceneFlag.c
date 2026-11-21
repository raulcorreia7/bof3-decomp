#include "engine/slus/slus.h"

/* reports bit **cursor of the g_SceneFlagWords flag row selected by D_8014820C.
 */
MATCH s32 Game_TestSceneFlag(u8** cursor) {
    return SYS_TestFlag(&g_SceneFlagWords[D_8014820C * 8], **cursor) & BYTE_MASK;
}
