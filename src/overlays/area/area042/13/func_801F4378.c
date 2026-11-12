#include "area042_13.h"
#include "menu/save_data.h"

MATCH void func_801F4378(void) {
    u32 timer;
    u16 thirtieths;
    u16 seconds;
    u16 hundredths;

    switch (g_SceneEventStep) {
        case 0: {
            u8* selection = &g_SceneEventSelection;

            if (*selection != 0) {
                timer      = g_SaveData.scene_event_timer;
                seconds    = timer / GAME_CLOCK_THIRTIETHS_PER_SECOND;
                thirtieths = timer % GAME_CLOCK_THIRTIETHS_PER_SECOND;
                hundredths = thirtieths * 10 / 3;
                func_801F4B0C(124, 46, 72, 17, 0);
                TEXT_Format(g_UiFormatBuffer, D_801F2C04, seconds, hundredths);
                g_UiFormatBuffer[2] = 0x8F;
                UI_DrawText(140, 48, (seconds < 10) * 2, 5, g_UiFormatBuffer);
                (*selection)--;
                break;
            }
        }
        /* fallthrough */
        case 1:
            g_AreaScrollTargetX = TO_COORD(21);
            g_AreaScrollTargetY = TO_COORD(25);
            g_AreaCameraStep    = 0x40;
            g_SceneEventStep    = 2;
            break;

        case 2:
            if (g_AreaCameraMoving == 0) {
                g_AreaCameraStep                 = 0;
                g_SaveData.scene_event.selection = Actor_FindFreeSlot();
                if (g_SaveData.scene_event.selection != 0xFF) {
                    g_ActorSlots[g_SaveData.scene_event.selection].header.flags   = ACTOR_FLAG_IN_USE;
                    g_ActorSlots[g_SaveData.scene_event.selection].type           = 0x13;
                    g_ActorSlots[g_SaveData.scene_event.selection].camera_angle.x = -0x302;
                    g_ActorSlots[g_SaveData.scene_event.selection].camera_angle.y = g_AreaCameraAngle.vy;
                    g_ActorSlots[g_SaveData.scene_event.selection].camera_angle.z = g_AreaCameraAngle.vz;
                    g_ActorSlots[g_SaveData.scene_event.selection].layer          = 0x10;
                }
                g_SceneEventStep = 3;
            }
            break;

        case 3:
            if ((g_ActorSlots[g_SaveData.scene_event.selection].header.flags & ACTOR_FLAG_IN_USE) == 0) {
                SYS_SetFlag(g_SaveData.scene_event_flags, 0x11);
                g_SceneEventStep = 9;
            }
            break;

        case 4:
            g_SaveData.scene_event.selection = Actor_FindFreeSlot();
            if (g_SaveData.scene_event.selection != 0xFF) {
                g_ActorSlots[g_SaveData.scene_event.selection].header.flags   = ACTOR_FLAG_IN_USE;
                g_ActorSlots[g_SaveData.scene_event.selection].type           = 0x13;
                g_ActorSlots[g_SaveData.scene_event.selection].camera_angle.x = -0x2AA;
                g_ActorSlots[g_SaveData.scene_event.selection].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[g_SaveData.scene_event.selection].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[g_SaveData.scene_event.selection].layer          = 0x10;
            }
            g_SceneEventStep = 5;
            break;

        case 5:
            if ((g_ActorSlots[g_SaveData.scene_event.selection].header.flags & ACTOR_FLAG_IN_USE) == 0) {
                g_AreaCameraStep    = 0x40;
                g_SceneEventStep    = 6;
                g_AreaScrollTargetX = g_Game.members[0].pos.x.fixed;
                g_AreaScrollTargetY = g_Game.members[0].pos.y.fixed;
            }
            break;

        case 6:
            if (g_AreaCameraMoving == 0) {
                SYS_ClearFlag(g_SaveData.scene_event_flags, 0x0B);
                Game_ClearScriptActive();
                g_AreaCameraStep             = 0;
                g_SceneEventMode             = SCENE_EVENT_NONE;
                g_SceneEventStep             = 0;
                g_SaveData.scene_event_timer = 0;
                g_GameFlags &= 0xFFDF;
            }
            break;

        case 10:
            timer      = g_SaveData.scene_event_timer;
            seconds    = timer / GAME_CLOCK_THIRTIETHS_PER_SECOND;
            thirtieths = timer % GAME_CLOCK_THIRTIETHS_PER_SECOND;
            hundredths = thirtieths * 10 / 3;
            func_801F4B0C(124, 46, 72, 17, 0);
            TEXT_Format(g_UiFormatBuffer, D_801F2C04, seconds, hundredths + (rand() & 3));
            g_UiFormatBuffer[2] = 0x8F;
            UI_DrawText(140, 48, (seconds < 10) ? ((g_SaveData.scene_event_timer >> 1) & 2) : 0, 5, g_UiFormatBuffer);
            if (g_SaveData.scene_event_timer != 0) {
                g_SaveData.scene_event_timer--;
                break;
            }
            SYS_ClearFlag(g_SaveData.scene_event_flags, 0x0B);
            SYS_ClearFlag(g_SaveData.scene_event_flags, 0x12);
            SYS_ClearFlag(g_SaveData.scene_event_flags, 0x13);
            SYS_ClearFlag(g_SaveData.scene_event_flags, 0x14);
            SYS_ClearFlag(g_SaveData.scene_event_flags, 0x15);
            g_SceneEventMode             = SCENE_EVENT_NONE;
            g_SceneEventStep             = 0;
            g_SaveData.scene_event_timer = 0;
            g_GameFlags &= 0xFFDF;
            break;
    }
}
