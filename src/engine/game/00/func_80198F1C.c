#include "game_00.h"

MATCH void func_80198F1C(void) {
    if ((g_PadStates[0].held & g_InputMasks[FIELD_INPUT_VIEW]) == 0) {
        if (g_AreaCameraAngle.vz >= ANGLE_45 + 1) {
            D_80143BB1 = 0;
        } else if (g_AreaCameraAngle.vz < ANGLE_45) {
            D_80143BB1 = 1;
        }
        {
            u16* counter = &g_SysThreads[0].tail.game_entry.substate;
            *counter += 1;
        }
        return;
    }
    if ((g_PadStates[0].held & PADLdown) && (g_AreaCameraAngle.vx >= -0x2A9)) {
        g_AreaCameraAngle.vx -= AREA_CAMERA_STEP;
        *MEM_PTR(u16, (void*)&D_801481D8) -= AREA_CAMERA_STEP;
    }
    if ((g_PadStates[0].held & PADLup) && (g_AreaCameraAngle.vx < -0x1C7)) {
        g_AreaCameraAngle.vx += AREA_CAMERA_STEP;
        *MEM_PTR(u16, (void*)&D_801481D8) += AREA_CAMERA_STEP;
    }
    if ((g_PadStates[0].held & PADLright) && (g_AreaCameraAngle.vz < 853)) {
        g_AreaCameraAngle.vz += AREA_CAMERA_STEP;
        *MEM_PTR(u16, (void*)&D_801481DC) += AREA_CAMERA_STEP;
    }
    if ((g_PadStates[0].held & PADLleft) && (g_AreaCameraAngle.vz >= 171)) {
        g_AreaCameraAngle.vz -= AREA_CAMERA_STEP;
        *MEM_PTR(u16, (void*)&D_801481DC) -= AREA_CAMERA_STEP;
    }
}
