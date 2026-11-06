#include "engine/slus/slus.h"

/* reports bit **cursor of the g_SaveData.scene_flag_words flag row selected by D_8014820C.
 */
MATCH s32 Game_TestSceneFlag(u8** cursor) {
    return SYS_TestFlag(&g_SaveData.scene_flag_words[D_8014820C * 8], **cursor) & BYTE_MASK;
}
