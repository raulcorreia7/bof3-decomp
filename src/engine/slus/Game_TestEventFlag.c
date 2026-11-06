#include "engine/slus/slus.h"

/* reports bit **cursor of the g_SaveData.scene_event_flags flag byte.
 */
MATCH s32 Game_TestEventFlag(u8** cursor) {
    return SYS_TestFlag(g_SaveData.scene_event_flags, **cursor) & BYTE_MASK;
}
