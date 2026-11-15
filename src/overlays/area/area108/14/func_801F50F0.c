#include "area108_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F50F0(void) {
    /* Kept volatile: the track loop's stores leave retail order without it. */
    volatile SceneSampleTrack* track;
    u8                         i;
    u8                         index;

    switch (g_SceneEventStep) {
        case 0:
            if (--LOHU(D_801448EE) == 0) {
                g_AreaScrollTargetX = D_80147A58[1].pos.x.fixed;
                g_AreaScrollTargetY = D_80147A58[1].pos.y.fixed;
                g_AreaCameraStep    = g_RouteSpeedScale[3] * 8;
                g_SceneEventStep++;
            }
            break;
        case 1:
            if (!g_AreaCameraMoving) {
                s8* step;

                step = &g_SceneEventStep;
                /* Retail passes the masked byte, the owner declares the argument s8. */
                ((void (*)(u8))Area_StartScrollRoute)((u8)(D_80147B67 - 1));
                D_80143FC0      = 4;
                g_ScriptVars[3] = 1;
                *step           = (u8)*step + 1;
            }
            break;
        case 2:
            if (g_ScriptVars[3] == 2) {
                s8* step;

                g_ScriptVars[3] = 0;
                if (D_80147B67 == 9) {
                    g_SceneEventStep = 4;
                } else {
                    step                = &g_SceneEventStep;
                    g_AreaScrollTargetX = g_Game.members[0].pos.x.fixed;
                    g_AreaScrollTargetY = g_Game.members[0].pos.y.fixed;
                    g_AreaCameraStep    = g_RouteSpeedScale[4] * 8;
                    *step               = (u8)*step + 1;
                }
            }
            break;
        case 3:
            if (!g_AreaCameraMoving) {
                Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
                g_SceneEventStep = 0;
                g_SceneEventMode = SCENE_EVENT_NONE;
                Game_ClearScriptActive();
            }
            break;
        case 4:
            if (g_ScriptVars[3] == 4) {
                SpawnedActor* slot;

                index = Actor_FindFreeSpawned() & BYTE_MASK;
                if (index != GAME_NONE) {
                    slot               = &g_SpawnedActors[index];
                    slot->pos.x.fixed  = 0x218000;
                    slot->header.flags = ACTOR_FLAG_IN_USE;
                    slot->type         = 0x35;
                    slot->pos.y.fixed  = 0x2F8000;
                    slot->pos.z.fixed  = Area_SampleHeight(slot->pos.x.fixed, slot->pos.y.fixed);
                }
                D_801448EE       = 0x1E;
                g_SceneEventStep = 5;
                {
                    u8* flag = &D_801F629B;
                    *flag    = (*flag & 0xF0) | 0x41;
                }
            }
            break;
        case 5: {
            u16* timer;

            timer = &LOHU(D_801448EE);
            if (--*timer != 0) {
                i     = 0;
                track = D_801F629C;
                if (D_801F6298 > 0) {
                    do {
                        track->sample[0] += (s8)(track->weight[0] >> 8);
                        track->sample[1] += (s8)(track->weight[1] >> 8);
                        track->sample[2] += (s8)(track->weight[2] >> 8);
                        track->sample[3] += (s8)(track->weight[0] >> 8);
                        track->sample[4] += (s8)(track->weight[1] >> 8);
                        track->sample[5] += (s8)(track->weight[2] >> 8);
                        track->sample[6] += (s8)(track->weight[0] >> 8);
                        track->sample[7] += (s8)(track->weight[1] >> 8);
                        track->sample[8] += (s8)(track->weight[2] >> 8);
                        track->sample[9] += (s8)(track->weight[0] >> 8);
                        track->sample[10] += (s8)(track->weight[1] >> 8);
                        track->sample[11] += (s8)(track->weight[2] >> 8);
                        i++;
                        track++;
                    } while (i < D_801F6298);
                }
                D_80147A58[0].tint.bytes.rgb.red -= 4;
                D_80147A58[0].tint.bytes.rgb.green -= 4;
                D_80147A58[0].tint.bytes.rgb.blue -= 4;
            } else {
                SYS_SetFlag(g_SceneEventFlags, 0x1D);
                Area_SetCellPalette(0x20, 0x2F);
                D_80147A58[0].header.flags = 0;
                *timer                     = 0x1E;
                g_SceneEventStep           = 9;
            }
        } break;
        case 9:
            if (--LOHU(D_801448EE) == 0) {
                g_SceneEventStep      = 0;
                g_SceneEventMode      = SCENE_EVENT_NONE;
                g_SceneState.state_04 = 3;
                g_SceneState.step_05  = 0;
            }
            break;
    }
}
#else
INCLUDE_ASM(func_801F50F0);
#endif
