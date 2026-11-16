#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9338(void) {
    u8 slot;

    switch (g_SceneState.step_05) {
        case 0:
            func_801BE1B0(0);
            g_ScriptVars[0]      = 1;
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0x28) {
                slot          = Actor_FindFreeSpawned();
                D_1F800000[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags  = ACTOR_FLAG_IN_USE;
                    /* Retail re-reads the staged slot byte for the type store. */
                    g_SpawnedActors[D_1F800000[0]].type = 0x14;
                    SND_PlayCue(0x203);
                }
                g_SceneState.step_05 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0x29) {
                slot          = Actor_FindFreeSpawned();
                D_1F800000[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags  = ACTOR_FLAG_IN_USE;
                    g_SpawnedActors[D_1F800000[0]].type = 0x14;
                    SND_PlayCue(0x203);
                }
                g_SceneState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x2A) {
                slot          = Actor_FindFreeSpawned();
                D_1F800000[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags  = ACTOR_FLAG_IN_USE;
                    g_SpawnedActors[D_1F800000[0]].type = 0x14;
                    SND_PlayCue(0x203);
                }
                g_SceneState.step_05 = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x32) {
                Char_AddAbility(0x97, g_CharSlot[0], 0, 0);
                SYS_SetFlag(&D_80145548, 0);
                SYS_SetFlag(g_SceneFlags, 1);
                Game_RequestAreaChange(0x2D, 0x280000, 0x350000, 0x86);
                g_GamePrevSelection  = 0x2F;
                g_GameRequestKind    = 0xFF;
                g_SceneState.step_05 = 5;
            }
            break;
        case 5:
            slot          = Actor_FindFreeSpawned();
            D_1F800000[0] = slot;
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags            = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[D_1F800000[0]].type           = 0x13;
                g_SpawnedActors[D_1F800000[0]].camera_angle.x = -0x31A;
                g_SpawnedActors[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_1F800000[0]].camera_angle.z = 0x360;
                g_SpawnedActors[D_1F800000[0]].layer          = 0xF0;
            }
            g_SceneState.timer_06 = 0x20;
            g_SceneState.step_05  = 6;
            break;
        case 6:
            if (g_SceneState.timer_06 != 0) {
                g_SceneState.timer_06--;
                break;
            }
            g_SceneState.step_05 = 7;
            break;
        case 7:
            if (g_ScriptVars[0] == 2) {
                SYS_SetFlag(g_SceneFlags, 2);
                D_80146258 |= 0x80;
                Game_RequestAreaChange(0x27, 0x290000, 0x270000, 5);
                g_GameRequestKind     = 0xFF;
                g_GameEntryMode       = 0;
                g_SceneState.state_04 = 3;
                g_SceneState.step_05  = 0;
            }
            break;
    }
}
