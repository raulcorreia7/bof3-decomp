#include "area108_14.h"
#include "menu/save_data.h"

MATCH void func_801F50F0(void) {
    SceneSampleTrack* track;
    u8                i;
    u8                index;

    switch (g_SceneEventStep) {
        case 0:
            if (--g_SaveData.scene_event_timer == 0) {
                g_AreaScrollTargetX = g_PartyActors[1].pos.x.fixed;
                g_AreaScrollTargetY = g_PartyActors[1].pos.y.fixed;
                g_AreaCameraSpeed   = g_RouteSpeedScale[3] * 8;
                g_SceneEventStep++;
            }
            break;
        case 1:
            if (!g_AreaCameraMoving) {
                /* Retail passes the masked byte, the owner declares the argument s8. */
                ((void (*)(u8))Area_ScrollStartRoute)((u8)(g_PartyActors[1].unk_77 - 1));
                D_80143FC0      = 4;
                g_ScriptVars[3] = 1;
                g_SceneEventState.step++;
            }
            break;
        case 2:
            if (g_ScriptVars[3] == 2) {
                g_ScriptVars[3] = 0;
                if (g_PartyActors[1].unk_77 == 9) {
                    g_SceneEventStep = 4;
                } else {
                    g_AreaScrollTargetX = g_Game.members[0].pos.x.fixed;
                    g_AreaScrollTargetY = g_Game.members[0].pos.y.fixed;
                    g_AreaCameraSpeed   = g_RouteSpeedScale[4] * 8;
                    g_SceneEventState.step++;
                }
            }
            break;
        case 3:
            if (!g_AreaCameraMoving) {
                Area_ScrollAdvance(Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY));
                g_SceneEventStep       = 0;
                g_SceneEventState.mode = SCENE_EVENT_NONE;
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
                    slot->pos.z.fixed  = Area_HeightSample(slot->pos.x.fixed, slot->pos.y.fixed);
                }
                g_SaveData.scene_event_timer = 0x1E;
                g_SceneEventStep             = 5;
                D_801F6298.flags             = (D_801F6298.flags & 0xF0) | 0x41;
            }
            break;
        case 5: {
            u16* timer;

            timer = &g_SaveData.scene_event_timer;
            if (--*timer != 0) {
                i     = 0;
                track = D_801F6298.tracks;
                if (D_801F6298.count > 0) {
                    do {
                        track->sample[0] += track->weight[0] >> 8;
                        track->sample[1] += track->weight[1] >> 8;
                        track->sample[2] += track->weight[2] >> 8;
                        track->sample[3] += track->weight[0] >> 8;
                        track->sample[4] += track->weight[1] >> 8;
                        track->sample[5] += track->weight[2] >> 8;
                        track->sample[6] += track->weight[0] >> 8;
                        track->sample[7] += track->weight[1] >> 8;
                        track->sample[8] += track->weight[2] >> 8;
                        track->sample[9] += track->weight[0] >> 8;
                        track->sample[10] += track->weight[1] >> 8;
                        track->sample[11] += track->weight[2] >> 8;
                        i++;
                        track++;
                    } while (i < D_801F6298.count);
                }
                g_PartyActors[0].tint.bytes.rgb.r -= 4;
                g_PartyActors[0].tint.bytes.rgb.b -= 4;
                g_PartyActors[0].tint.bytes.rgb.g -= 4;
            } else {
                SYS_SetFlag(g_SaveData.scene_event_flags, 0x1D);
                Area_CellSetPalette(0x20, 0x2F);
                g_PartyActors[0].header.flags = 0;
                *timer                        = 0x1E;
                g_SceneEventStep              = 9;
            }
        } break;
        case 9:
            if (--g_SaveData.scene_event_timer == 0) {
                g_SceneEventStep         = 0;
                g_SceneEventState.mode   = SCENE_EVENT_NONE;
                g_ScenarioState.state_04 = 3;
                g_ScenarioState.step     = 0;
            }
            break;
    }
}
