#include "engine/slus/slus.h"

/* reports bit **cursor of the g_SceneFlagRows flag row selected by D_8014820C.
 */
MATCH s32 Game_TestSceneFlag(u8** cursor) {
    return SYS_TestFlag(g_SceneFlagRows[D_8014820C], **cursor) & BYTE_MASK;
}
