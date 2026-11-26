#include "area148_13.h"

/* FAKE: the scene event reads stay on the symbol cells; as record members they moved the schedule. */
MATCH void func_801F3C24(void) {
    s8*  event_mode;
    u8*  selection;
    u16* timer_ptr;
    u16  timer;
    u8   slot;

    switch (g_SceneEventStep) {
        case 0:
            Scene_SetupParty(0);
            g_SceneEventStep = 1;
            break;
        case 1:
            if (g_ScriptVars[3] == 24) {
                event_mode       = &g_SceneEventMode;
                *event_mode      = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
                SYS_SetFlag(event_mode + 0x63D, 70);
                func_8019FA28(149, TO_COORD(28), TO_COORD(12), 128);
            }
            break;
        case 10:
            slot       = func_8019601C();
            selection  = &g_SceneEventSelection;
            *selection = slot;
            if (slot != GAME_NONE) {
                g_SpawnedActors[*selection].header.flags   = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[*selection].type           = 19;
                g_SpawnedActors[*selection].camera_angle.x = -922;
                FAKE_BARRIER();
                g_SpawnedActors[*selection].camera_angle.y = g_AreaCameraAngle.vy;
                FAKE_BARRIER();
                g_SpawnedActors[*selection].camera_angle.z = 400;
                FAKE_BARRIER();
                g_SpawnedActors[*selection].layer = 48;
                g_SceneEventStep                  = 11;
            }
            break;
        case 11:
            if ((g_SpawnedActors[g_SceneEventSelection].header.flags & ACTOR_FLAG_IN_USE) == 0) {
                func_801C601C(2);
                g_SceneEventStep = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[3] == 32) {
                SYS_SetFlag(g_SceneEventFlags, 90);
                D_801448EE       = 32;
                g_SceneEventStep = 13;
            }
            break;
        case 13:
            timer_ptr = &D_801448EE;
            timer     = *timer_ptr;
            timer--;
            *timer_ptr = timer;
            if (timer == 0) {
                slot                  = func_8019601C();
                g_SceneEventSelection = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                    = ACTOR_FLAG_IN_USE;
                    g_SpawnedActors[g_SceneEventSelection].type           = 19;
                    g_SpawnedActors[g_SceneEventSelection].camera_angle.x = -682;
                    FAKE_BARRIER();
                    g_SpawnedActors[g_SceneEventSelection].camera_angle.y = g_AreaCameraAngle.vy;
                    FAKE_BARRIER();
                    g_SpawnedActors[g_SceneEventSelection].camera_angle.z = 512;
                    FAKE_BARRIER();
                    g_SpawnedActors[g_SceneEventSelection].layer = 32;
                    g_SceneEventStep                             = 14;
                }
            }
            break;
        case 14:
            if (g_ScriptVars[3] == 0) {
                goto cleanup;
            }
            break;
        case 20:
            SYS_ToggleFlag(g_SceneEventFlags, 106);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
            if (SYS_TestFlag(g_SceneEventFlags, 106)) {
                Area_PaletteApplyTint(0, 0x380, -6, -4, -4);
            } else {
                Area_PaletteApplyTint(0, 0x180, 0, 0, 0);
            }
            D_801448EE       = 15;
            g_AreaDrawFlags  = 0;
            g_SceneEventStep = 21;
            break;
        case 21:
            timer_ptr = &D_801448EE;
            timer     = *timer_ptr;
            timer--;
            *timer_ptr = timer;
            if (timer == 0) {
                g_AreaDrawFlags = 31;
                goto cleanup;
            }
            break;
    }
    return;

cleanup:
    Game_ClearScriptActive();
    g_SceneEventMode = SCENE_EVENT_NONE;
    g_SceneEventStep = 0;
}
