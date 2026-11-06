#include "engine/slus/slus.h"

/* reports bit **cursor of the g_SceneEventFlags flag byte.
 */
MATCH s32 Game_TestEventFlag(u8** cursor) {
    return SYS_TestFlag(g_SceneEventFlags, **cursor) & BYTE_MASK;
}
