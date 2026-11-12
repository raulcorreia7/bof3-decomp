#include "engine/slus/slus.h"

/* returns bit 0 of g_SceneState.flags_01, inverted unless the record byte is 1.
 */
MATCH s32 func_8015B6F8(u8** cursor) {
    if (**cursor != 1) {
        return (g_SceneState.flags_01 & 0x1) ^ 0x1;
    }
    return g_SceneState.flags_01 & 0x1;
}
