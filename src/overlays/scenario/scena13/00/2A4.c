#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F6EE8(void) {
    u8* first;
    u8* second;
    u8* third;

    first       = (u8*)g_Task;
    first[0x5F] = 0;
    first[0x5E] = 0;
    first[0x5D] = 0;

    second    = (u8*)g_Task;
    second[9] = 0x0F;

    third    = (u8*)g_Task;
    third[1] = 1;
}

MATCH void func_801F6F24(void) {
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        g_Task->tint.bytes.rgb.r += 7;
        g_Task->tint.bytes.rgb.g += 7;
        g_Task->tint.bytes.rgb.b += 7;
    } else {
        g_Task->header.mode = 2;
    }
    Area_DrawScreenTint();
    func_801F70DC();
}

MATCH void func_801F6FD0(void) {
    Area_DrawScreenTint();
    func_801F70DC();
}

#include "shared/Area_DrawScreenTint.h"

MATCH void Area_DrawScreenTint(void) {
    Screen_DrawTintLayer(5, (GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK));
}

MATCH void func_801F70DC(void) {
    Actor* actor;
    Actor* actor2;
    s32    i;

    actor = g_Task;
    i     = 0;
    do {
        actor2 = &g_Actors[i & BYTE_MASK];
        g_Task = actor2;
        if ((actor2->header.flags & 0x1) && (actor2->unk_06 == 6)) {
            actor2->draw_layer = 5;
            Area_AddGridActor();
        }
        i += 1;
    } while ((i & BYTE_MASK) < 0x1EU);
    g_Task = actor;
}

MATCH void func_801F7198(void) {
    SYS_DISPATCH_TASK(D_801FBEFC, 1, g_Task);
}

MATCH void func_801F71DC(void) {
    Actor* work;

    work                   = g_Task;
    work->tint.bytes.rgb.b = 0;
    work->tint.bytes.rgb.g = 0;
    work->tint.bytes.rgb.r = 0;
    g_Task->param.unk_0B   = 0x33;
    MESSAGE_START_WAIT(g_Task->param.unk_0B);
    g_Task->header.mode = 1;
}

MATCH void func_801F7248(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        g_Task->timer       = 30;
        g_Task->header.mode = 2;
    }
    Scene_DrawScreenTint();
    func_801F7568();
}

MATCH void func_801F72A0(void) {
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        g_Task->tint.bytes.rgb.r += 2;
        g_Task->tint.bytes.rgb.g += 2;
        g_Task->tint.bytes.rgb.b += 2;
    } else {
        g_Task->timer       = 30;
        g_Task->header.mode = 3;
    }
    Scene_DrawScreenTint();
    func_801F7568();
}

MATCH void func_801F735C(void) {
    Actor* work;
    s16    message_id;

    g_Task->timer -= 1;
    if (g_Task->timer == 0) {
        g_Task->param.unk_0B += 1;
        work       = g_Task;
        message_id = work->param.unk_0B;
        if ((u8)message_id == 0x37) {
            work->tint.steps.delta.b = -1;
            work->tint.steps.delta.g = -1;
            work->tint.steps.delta.r = -1;
            g_Task->header.mode      = 4;
            g_ScriptVars[0] += 1;
        } else {
            MESSAGE_START_WAIT(message_id);
            g_Task->header.mode = 1;
        }
    }
    Scene_DrawScreenTint();
    func_801F7568();
}

MATCH void func_801F7444(void) {
    if (g_ScriptVars[0] == 0x35) {
        Actor_Clear();
    }
    Scene_DrawScreenTint();
    func_801F7568();
}

/* func_801F7484 */
MATCH void Scene_DrawScreenTint(void) {
    Screen_DrawTintLayer(5, (GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK));
}

MATCH void func_801F7568(void) {
    Actor* work;
    Actor* actor;

    work              = g_Task;
    actor             = &g_Actors[work->unk_06];
    g_Task            = actor;
    actor->draw_layer = 2;
    Area_AddGridActor();
    TASK_SET(g_Game.members);
    g_Game.members[0].unk_29 = 2;
    Area_AddGridActor();
    g_Task = work;
}

MATCH void func_801F75F8(void) {
    SYS_DISPATCH_TASK(D_801FBF10, 1, g_Task);
}

MATCH void func_801F763C(void) {
    u8*  work;
    u8*  data;
    u8*  cell;
    u8   cell4;
    u32  cell3;
    s16* scratch;

    g_Task->unk_03 = Actor_FindFreeField();
    if (g_Task->unk_03 == GAME_NONE) {
        return;
    }

    g_Actors[g_Task->unk_03].header.flags = 1;
    g_Task->unk_04                        = Actor_FindFreeField();
    if (g_Task->unk_04 == GAME_NONE) {
        g_Actors[g_Task->unk_03].header.flags = 0;
        return;
    }

    scratch                               = (s16*)g_ScratchPad.cells.bytes;
    data                                  = (u8*)D_801FBF20;
    g_Actors[g_Task->unk_04].header.flags = 1;
    work                                  = (u8*)g_Task;
    *scratch                              = work[3];
    Actor_SpawnFromRecord(data);
    *scratch = work[4];
    Actor_SpawnFromRecord(data);
    SP_REF(u8*, 0x44) = work;

    g_Actors[work[3]].pos.y.fixed -= TO_COORD(1);
    g_Actors[work[4]].pos.y.fixed += TO_COORD(1);
    g_Actors[work[3]].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Actors[g_Task->unk_04].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    cell                                      = (u8*)g_Task;
    cell4                                     = cell[4];
    cell3                                     = cell[3];
    FIELD(u8, D_801468E4, cell4 * ACTOR_SIZE) = 1;
    FIELD(u8, D_801468E4, cell3 * ACTOR_SIZE) = 1;
    GFX_AllocPaletteFade(&g_Actors[work[3]], 15, 0, 0, 1);
    GFX_AllocPaletteFade(&g_Actors[work[4]], 0, 0, 15, 1);
    g_Task->timer       = 32;
    g_Task->header.mode = 1;
}

MATCH void func_801F7958(void) {
    if (g_Task->timer != 0) {
        g_Actors[g_Task->unk_03].pos.y.fixed += 0x800;
        g_Actors[g_Task->unk_04].pos.y.fixed -= 0x800;
        g_Task->timer -= 1;
    } else {
        g_Task->timer       = 15;
        g_Task->header.mode = 2;
    }
}

MATCH void func_801F7A1C(void) {
    if (g_Task->timer != 0) {
        g_Actors[g_Task->unk_03].tint.bytes.rgb.r += 8;
        g_Actors[g_Task->unk_03].tint.bytes.rgb.g += 8;
        g_Actors[g_Task->unk_03].tint.bytes.rgb.b += 8;
        g_Actors[g_Task->unk_04].tint.bytes.rgb.r += 8;
        g_Actors[g_Task->unk_04].tint.bytes.rgb.g += 8;
        g_Actors[g_Task->unk_04].tint.bytes.rgb.b += 8;
        g_Task->timer--;
    } else {
        g_ScriptVars[0]++;
        g_Task->header.mode = 3;
    }
}

/* func_801F7C24 */
MATCH void Scene_ReleaseActors(void) {
    g_Actors[g_Task->unk_03].header.flags = 0;
    g_Actors[g_Task->unk_04].header.flags = 0;
    GFX_FreePaletteFadeTarget(&g_Actors[g_Task->unk_03]);
    GFX_FreePaletteFadeTarget(&g_Actors[g_Task->unk_04]);
    Actor_Clear();
}

MATCH void func_801F7D14(void) {
    SYS_DISPATCH_BYTE(D_801FBF48, D_80146872);
}

MATCH void func_801F7D50(void) {
    Game_SetScriptActive();
    g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
    Char_RebuildPartyStats();
    Scene_RunScenario(0);
    SYS_SetFlag(g_SceneEventFlags, 67);
    SYS_ClearFlag(g_SceneEventFlags, 66);
    D_80146872 = 1;
}

MATCH void func_801F7DBC(void) {
    if (LOHU(g_GameAreaId) == AREA_ID_STEEL_BEACH_FREIGHTER) {
        if (g_GameCellType == 1 && g_GameLastAreaId == AREA_ID_RELAY_POINT_A_PORTAL && SYS_TestFlag(g_SceneFlags, 0xC) != 0 && SYS_TestFlag(g_SceneFlags, 0xD) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 4;
            g_ScenarioState.step_05  = 0xA;
        }
        if (g_GameCellType == 0 && SYS_TestFlag(g_SceneFlags, 0xD) != 0 && SYS_TestFlag(g_SceneFlags, 0xE) == 0) {
            func_801C1DF0(4);
            func_801BE1B0(0);
        }
    }

    if (LOHU(g_GameAreaId) == AREA_ID_URKAN_TAPA_WORLD_MAP && g_GameLastAreaId == AREA_ID_COLONY_OUTSIDE && SYS_TestFlag(g_SceneFlags, 0xB) == 0) {
        g_AreaCameraAngle.vx = -0x2D6;
        g_AreaCameraAngle.vz = 0x2F2;
        g_AreaCameraOffsetZ  = 0x5DC;
    }
    if (LOHU(g_GameAreaId) == AREA_ID_RELAY_POINT_A_PORTAL && g_GameCellType == 4 && SYS_TestFlag(g_SceneFlags, 0xC) == 0) {
        func_801BE1B0(2);
        SYS_SetFlag(g_SceneFlags, 0xC);
    }
    if (LOHU(g_GameAreaId) == AREA_ID_KOMBINAT_ARRIVAL && SYS_TestFlag(g_SceneFlags, 0) == 0) {
        func_801BE1B0(0);
        g_AreaCameraAngle.vx     = -0x386;
        g_AreaCameraAngle.vz     = 0x150;
        g_ScenarioState.state_04 = 1;
        g_ScenarioState.step_05  = 0;
    }

    if (LOHU(g_GameAreaId) == AREA_ID_DRAGNIER_SURFACE) {
        if (g_GameCellType == 0) {
            if (SYS_TestFlag(g_SceneFlags, 0x11) == 0) {
                g_AreaCameraAngle.vx = -0x2C0;
                g_AreaCameraAngle.vz = 0x10E;
                D_801FBFEC           = func_8019601C();
                if (D_801FBFEC != 0xFF) {
                    g_SpawnedActors[D_801FBFEC].header.flags   = 1;
                    g_SpawnedActors[D_801FBFEC].type           = 0x13;
                    g_SpawnedActors[D_801FBFEC].camera_angle.x = -0x2AA;
                    g_SpawnedActors[D_801FBFEC].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FBFEC].camera_angle.z = 0x2C6;
                    g_SpawnedActors[D_801FBFEC].layer          = 0xFF;
                }
            } else if (SYS_TestFlag(g_SceneFlags, 0x12) == 0) {
                func_801F3E60(1);
                g_AreaDrawFlags = 0;
                SND_PlaySE(0x203);
            } else if (SYS_TestFlag(g_SceneFlags, 0x13) == 0) {
                func_801C1DF0(6);
                func_801BE1B0(6);
                SYS_SetFlag(g_SceneFlags, 0x13);
            }
        }
        if (g_GameCellType == 2) {
            if (SYS_TestFlag(g_SceneFlags, 0x11) == 0) {
                func_801C1DF0(5);
                func_801BE1B0(3);
            } else if (SYS_TestFlag(g_SceneFlags, 0x12) == 0) {
                func_801F3E60(0);
            }
        }
    }

    if (LOHU(g_GameAreaId) == AREA_ID_DRAGNIER_ELDER_FIGHT) {
        SYS_SetFlag(g_SceneFlags, 0x1F);
        if (g_GameCellType == 2 && SYS_TestFlag(g_SceneFlags, 0x17) == 0) {
            SND_StartDecrescendo(0, 0, 0x64, 0x10);
            func_801BE1B0(0);
            g_ScenarioState.state_04 = 7;
            g_ScenarioState.step_05  = 0;
        }
    }

    if (LOHU(g_GameAreaId) == AREA_ID_COLONY_OUTSIDE) {
        if (g_GameCellType == 0 && SYS_TestFlag(g_SceneFlags, 7) == 0) {
            func_801BE1B0(5);
            g_ScenarioState.state_04 = 3;
            g_ScenarioState.step_05  = 0;
        }
        if (g_GameCellType == 4 && SYS_TestFlag(g_SceneFlags, 8) == 0) {
            func_801BE1B0(6);
            SYS_SetFlag(g_SceneFlags, 8);
        }
    }

    if (LOHU(g_GameAreaId) == AREA_ID_KOMBINAT_CAMP) {
        if (SYS_TestFlag(g_SceneFlags, 2) == 0) {
            func_801C1DF0(1);
            func_801BE1B0(0);
            func_801F8C1C();
            g_AreaCameraOffsetZ = -0xE00;
            D_801FBFEC          = func_8019601C();
            if (D_801FBFEC != 0xFF) {
                g_SpawnedActors[D_801FBFEC].header.flags   = 1;
                g_SpawnedActors[D_801FBFEC].type           = 0x31;
                g_SpawnedActors[D_801FBFEC].camera_angle.x = -0x2AA;
                g_SpawnedActors[D_801FBFEC].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FBFEC].camera_angle.z = 0x200;
                g_SpawnedActors[D_801FBFEC].scene_step     = 0;
                g_SpawnedActors[D_801FBFEC].layer          = 0x1E;
            }
        } else if (SYS_TestFlag(g_SceneFlags, 3) != 0 && SYS_TestFlag(g_SceneFlags, 4) == 0) {
            func_801C1DF0(2);
            func_801BE1B0(2);
            func_801F8D0C();
        }
    }
    g_ScenarioState.mode_02 = 2;
}

MATCH void func_801F8474(void) {
    SYS_DISPATCH_BYTE(D_801FBF54, g_ScenarioState.state_04);
}

MATCH void func_801F84B0(void) {
}
