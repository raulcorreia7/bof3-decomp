#include "game_00.h"

MATCH void func_8019A904(void) {
    Actor* work;
    s32    pos_x;
    s32    pos_y;
    s32    pos_z;

    work                     = g_SpadWork;
    pos_x                    = g_AreaCameraAngle.vx;
    pos_y                    = g_AreaCameraAngle.vy;
    pos_z                    = g_AreaCameraAngle.vz;
    D_801481E8.x             = pos_x << 0x10;
    D_801481E8.y             = pos_y << 0x10;
    D_801481E8.z             = pos_z << 0x10;
    D_801481F8.x             = ((work->unk_64 - pos_x) << 0x10) / work->unk_09;
    D_801481F8.y             = ((work->unk_68 - pos_y) << 0x10) / work->unk_09;
    D_801481F8.z             = ((work->unk_6C - pos_z) << 0x10) / work->unk_09;
    g_AreaCameraRefreshCount = work->unk_09;
    g_SceneState.flags_01 |= 0x20;
    work->unk_01 = 1;
}
