#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8188(void) {
    u8  id;
    u8* char_slots;

    switch (g_SceneState.step_05) {
        case 0:
            g_SceneState.step_05 = 1;
            func_8019FA28(0x2F, 0x718000, 0x90000, 0x80);
            g_GamePrevSelection = 0xFF;
            break;
        case 1:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScriptVars[0] = 1;
            func_801C601C(0);
            g_SceneState.step_05 = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            id                     = func_8019601C();
            D_1F800000.view.raw[0] = id;
            if ((id & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[id].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x31;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = g_AreaCameraAngle.vx;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = 0x124;
                g_ActorSlots[D_1F800000.view.raw[0]].scene_step     = 0x700;
                g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x5A;
                g_SceneState.step_05                                = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            SND_PlayBGM(0x27, 0x64, 8);
            g_SceneState.step_05 = 5;
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            break;
        case 5:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            id                     = func_8019601C();
            D_1F800000.view.raw[0] = id;
            if ((id & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[id].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = -0x3B5;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x1E;
                g_SceneState.step_05                                = 7;
            }
            break;
        case 7:
            SND_StopSequence(0, 2);
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
            g_SceneState.step_05 = 8;
            break;
        case 8:
            if (g_ScriptVars[0] != 0xC) {
                break;
            }
            SND_PlayBGM(0x24, 0x64, 8);
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
            g_SceneState.step_05 = 9;
            g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            break;
        case 9:
            if (g_ScriptVars[0] != 0xD) {
                break;
            }
            id                     = func_8019601C();
            D_1F800000.view.raw[0] = id;
            if ((id & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[id].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = -0x2AA;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x1E;
                g_SceneState.step_05                                = 0xA;
            }
            break;
        case 10:
            if (g_ScriptVars[0] != 0xE) {
                break;
            }
            g_SceneState.step_05 = 0xB;
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            SYS_SetFlag(g_SceneFlags, 0xA);
            func_8019FA28(0x35, 0x230000, 0x290000, 0x80);
            break;
        case 11:
            func_801C601C(0);
            id                     = func_8019601C();
            D_1F800000.view.raw[0] = id;
            if ((id & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[id].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = 0;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[D_1F800000.view.raw[0]].layer          = 2;
                g_SceneState.step_05                                = 0xC;
            }
            break;
        case 12:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            id                     = func_8019601C();
            D_1F800000.view.raw[0] = id;
            if ((id & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[id].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = -0x2AA;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x78;
                g_SceneState.step_05                                = 0xD;
            }
            break;
        case 13:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            g_SceneState.step_05 = 0xE;
            SYS_SetFlag(g_SceneFlags, 0xB);
            SYS_SetFlag(g_SceneFlags, 9);
            Item_VitalAdd(VITAL_ITEM_PASSPORT);
            break;
        case 14:
            if (g_ScriptVars[0] != 0x32) {
                break;
            }
            g_SceneState.step_05 = 0xF;
            g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            /* FAKE: retail reads g_CharSlot as u8[]. */
            char_slots = (u8*)g_CharSlot;
            g_Characters[char_slots[6]].unk_07 |= 1;
            g_Characters[char_slots[2]].unk_07 |= 1;
            func_8019FA28(0x2D, 0x220000, 0x2A0000, 3);
            break;
        case 15:
            func_801C16B8();
            Game_ClearScriptActive();
            g_ScriptVars[0]       = 0;
            D_80146865            = 0;
            D_80146866            = 0;
            D_80146867            = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}
