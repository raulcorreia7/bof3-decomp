#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8188(void) {
    u8  slot;
    u8* char_slots;

    switch (g_SceneState.step_05) {
        case 0:
            g_SceneState.step_05 = 1;
            Game_RequestAreaChange(AREA_ID_WYNDIA_HONEY_BALCONY, TO_COORD(113) + COORD_HALF, TO_COORD(9), AREA_ENTRY_MAP_LOADING);
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
            slot                     = Actor_FindFreeSlot();
            D_1F800000.view.raw[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[slot].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x31;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = g_AreaCameraAngle.vx;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = 292;
                g_ActorSlots[D_1F800000.view.raw[0]].scene_step     = 0x700;
                g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x5A;
                g_SceneState.step_05                                = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            SND_PlayBGM(0x27, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_SceneState.step_05 = 5;
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            break;
        case 5:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            slot                     = Actor_FindFreeSlot();
            D_1F800000.view.raw[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[slot].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = -949;
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
            SND_PlayBGM(0x24, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
            g_SceneState.step_05 = 9;
            g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            break;
        case 9:
            if (g_ScriptVars[0] != 0xD) {
                break;
            }
            slot                     = Actor_FindFreeSlot();
            D_1F800000.view.raw[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[slot].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = -682;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x1E;
                g_SceneState.step_05                                = 10;
            }
            break;
        case 10:
            if (g_ScriptVars[0] != 0xE) {
                break;
            }
            g_SceneState.step_05 = 11;
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            SYS_SetFlag(g_SceneFlags, 10);
            Game_RequestAreaChange(AREA_ID_CAMP_BEFORE_ANGEL_TOWER, TO_COORD(35), TO_COORD(41), AREA_ENTRY_MAP_LOADING);
            break;
        case 11:
            func_801C601C(0);
            slot                     = Actor_FindFreeSlot();
            D_1F800000.view.raw[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[slot].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = 0;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[D_1F800000.view.raw[0]].layer          = 2;
                g_SceneState.step_05                                = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            slot                     = Actor_FindFreeSlot();
            D_1F800000.view.raw[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[slot].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = -682;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x78;
                g_SceneState.step_05                                = 13;
            }
            break;
        case 13:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            g_SceneState.step_05 = 14;
            SYS_SetFlag(g_SceneFlags, 11);
            SYS_SetFlag(g_SceneFlags, 9);
            Item_VitalAdd(VITAL_ITEM_PASSPORT);
            break;
        case 14:
            if (g_ScriptVars[0] != 0x32) {
                break;
            }
            g_SceneState.step_05 = 15;
            g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            /* FAKE: retail reads g_CharSlot as u8[]. */
            char_slots = (u8*)g_CharSlot;
            g_Characters[char_slots[6]].unk_07 |= 1;
            g_Characters[char_slots[2]].unk_07 |= 1;
            Game_RequestAreaChange(AREA_ID_WYNDIA_WORLD_MAP, TO_COORD(34), TO_COORD(42), FACING_RIGHT);
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
