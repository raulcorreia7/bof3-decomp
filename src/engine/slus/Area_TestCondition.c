#include "engine/slus/slus.h"

/* resolves a palette-tint request word (bits 8-15 the class, bit 0 the polarity): classes FA/FF compare the
 * low byte with a reference byte, FC00 folds in the entry-0 UI state, FB00 tests g_AreaCameraAngle.vz against a
 * 0x801-frame window at 0x200, and the low classes read a bit from the 8-byte-stride table g_SceneFlagWords.
 */
MATCH s8 Area_TestCondition(s32 request) {
    s16 tag     = request;
    s32 shifted = request << 16;

    if ((tag & 0xFF00) == 0x4000) {
        return tag & 0x1;
    }
    if ((tag & 0xFF00) == 0xFF00) {
        return D_8014933C ^ (tag & 0x1);
    }
    if ((tag & 0xFF00) == 0xFE00) {
        return ((request & BYTE_MASK) ^ g_AreaSceneMode) == 0;
    }
    if ((tag & 0xFF00) == 0xFD00) {
        return ((request & BYTE_MASK) ^ D_80143F03) != 0;
    }
    if ((tag & 0xFF00) == 0xFC00) {
        return (tag & 0x1) ^ ((g_GameStateIndex == GAME_REQUEST_CAMERA_LOOK) | (g_GameEntryState == GAME_STATE_SHOP));
    }
    if ((tag & 0xFF00) == 0xFB00) {
        s32 bit = request & 0x1;

        if (((g_AreaCameraAngle.vz - 0x200) & ANGLE_MASK) < 0x801) {
            return bit ^ 0x1;
        }
        return bit;
    }
    if ((tag & 0xFF00) == 0xFA00) {
        return ((request & BYTE_MASK) ^ g_SceneRecord.sbyte) == 0;
    }
    if ((tag & 0xFF00) < 0x2000) {
        return SYS_TestFlag(&g_SceneFlagWords[(shifted >> 24) * 8], request & BYTE_MASK);
    }
    if ((tag & 0xFF00) < 0x4000) {
        return SYS_TestFlag(&g_SceneFlagWords[(shifted >> 21) & 0xF8], request & BYTE_MASK) == 0;
    }
    return tag & 0x1;
}
