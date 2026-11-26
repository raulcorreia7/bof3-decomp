#include "engine/slus/slus.h"

/* resolves a palette-tint request word (bits 8-15 the class, bit 0 the polarity): classes FA/FF compare the
 * low byte with a reference byte, FC00 folds in the entry-0 UI state, FB00 tests g_AreaCameraAngle.vz against a
 * 0x801-frame window at 0x200, and the low classes test a bit of the g_SceneFlagRows row the class byte names.
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
        return ((request & BYTE_MASK) ^ g_GameCellType) != 0;
    }
    if ((tag & 0xFF00) == 0xFC00) {
        return (tag & 0x1) ^ ((g_SysThreads[0].tail.game_entry.request == GAME_REQUEST_CAMERA_LOOK) | (g_SysThreads[0].tail.game_entry.state == GAME_MODE_SHOP));
    }
    if ((tag & 0xFF00) == 0xFB00) {
        s32 bit = request & 0x1;

        if (((g_AreaCamera.angle.vz - 0x200) & ANGLE_MASK) < 0x801) {
            return bit ^ 0x1;
        }
        return bit;
    }
    if ((tag & 0xFF00) == 0xFA00) {
        return ((request & BYTE_MASK) ^ g_SceneRecord.sbyte) == 0;
    }
    if ((tag & 0xFF00) < 0x2000) {
        return SYS_TestFlag(g_SceneFlagRows[shifted >> 24], request & BYTE_MASK);
    }
    if ((tag & 0xFF00) < 0x4000) {
        return SYS_TestFlag(g_SceneFlagRows[(shifted >> 24) & 0x1F], request & BYTE_MASK) == 0;
    }
    return tag & 0x1;
}
