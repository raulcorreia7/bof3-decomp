#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F73A0(void) {
    Scene_ClearWorkRows();
    func_801F76D0();
    TASK(Actor)->timer = 0xFF;
    TASK(Actor)->header.mode++;
}

MATCH void func_801F73F0(void) {
    if (!(func_801F75BC() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F7424(Actor* actor) {
    POLY_F3* poly;
    FAKE_STACK_PADS(u8, 48); /* FAKE: retail frame reserves 48 bytes no statement uses. */

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK, 0);
    Area_CellAddPrim(actor->unk_18, actor->unk_1C, 0, sizeof(DR_MODE));
    poly = (POLY_F3*)g_GfxPrimCursor;
    SetPolyF3(poly);
    SetSemiTrans(poly, 1);
    Camera_ProjectPoint(&actor->unk_18, POLY_XY(poly, 0));
    poly->x1 = poly->x0 + D_801FE38C[actor->unk_04].dx1;
    poly->y1 = poly->y0 + D_801FE38C[actor->unk_04].dy1;
    poly->x2 = poly->x0 + D_801FE38C[actor->unk_04].dx2;
    poly->y2 = poly->y0 + D_801FE38C[actor->unk_04].dy2;
    setRGB0(poly, 0, actor->unk_03, actor->unk_03);
    Area_CellAddPrim(actor->unk_18, actor->unk_1C, -2, sizeof(POLY_F3));
}

/* func_801F7574 */
MATCH void Scene_ClearWorkRows(void) {
    SparkParticle* particle;
    u8             i;

    particle = (SparkParticle*)(MEM_PTR(u8, AREA_WORK + 0x800) + TASK(Actor)->unk_06 * 0x500);
    for (i = 0; i < SCENE_SPARK_COUNT; i++, particle++) {
        particle->header.active = 0;
    }
}

MATCH s32 func_801F75BC(void) {
    MATRIX         camera;
    SparkParticle* particle;
    u8             i;
    u8             life;
    s32            alive;

    Camera_SetMatrix(&camera);
    alive    = 0;
    particle = (SparkParticle*)(MEM_PTR(u8, AREA_WORK + 0x800) + TASK(Actor)->unk_06 * 0x500);
    for (i = 0; i < SCENE_SPARK_COUNT; particle++, i++) {
        if (particle->header.active == 0) {
            continue;
        }
        particle->pos.vx += particle->velocity.vx;
        particle->pos.vy += particle->velocity.vy;
        particle->pos.vz += particle->velocity.vz;
        particle->velocity.vz -= 0x40000;
        particle->header.shade -= 4;
        particle->frame       = rand() & 7;
        life                  = particle->header.life - 1;
        particle->header.life = life;
        if (life == 0) {
            particle->header.active = 0;
        }
        func_801F7424(particle);
        alive = 1;
    }
    return alive;
}

MATCH void func_801F76D0(void) {
    SparkParticle* spark;
    u8             mode;
    u8             i;

    FAKE_STACK_PADS(u8, 0x20); /* FAKE: retail reserves 32 unused stack bytes. */
    mode  = TASK(Actor)->unk_06;
    spark = MEM_PTR(SparkParticle, AREA_WORK + 0x800 + mode * 0x500);
    i     = 0;
    do {
        if (TASK(Actor)->unk_06 == 0) {
            setVector(&spark->pos, ((rand() & 0x1FF) << 8) + 0x120000, ((rand() & 0x1FF) << 8) + 0x2E8000, TO_COORD(2112) - ((spark->pos.vx - 0x120000) << 7));
            setVector(&spark->velocity, (spark->pos.vx - 0x130000) >> 4, (spark->pos.vy - 0x2F8000) >> 4, (-(rand() & 0xFF)) << 5);
            spark->velocity.vx -= 0x800;
        } else {
            setVector(&spark->pos, ((rand() & 0x1FF) << 8) + 0x78000, ((rand() & 0x1FF) << 8) + 0x318000, TO_COORD(2112) - ((spark->pos.vy - 0x318000) << 7));
            setVector(&spark->velocity, (spark->pos.vx - 0x88000) >> 4, (spark->pos.vy - 0x328000) >> 4, (-(rand() & 0xFF)) << 5);
            spark->velocity.vy = -0x800;
        }
        spark->header.active = 1;
        spark->header.life   = 0x18;
        spark->header.type   = 0;
        spark->header.shade  = 0x60;
        spark->frame         = rand() & 7;
        spark++;
        i++;
    } while (i < 32);
}

MATCH void func_801F78D0(void) {
    SYS_DISPATCH_BYTE(D_801FE3E0, D_80146872);
}

MATCH void func_801F790C(void) {
    D_80146872 = 1;
}

/* starts the scene events of the area and cell the party enters */
MATCH void func_801F7920(void) {
    if (g_GameAreaId == AREA_ID_WYNDIA_LOWER) {
        if (SYS_TestFlag(g_SceneFlags, 0x2E) && !SYS_TestFlag(g_SceneFlags, 0x2F)) {
            Game_SetScriptActive();
            SYS_SetFlag(g_Scenario2Flags + 0x20, 0x3E);
            g_GameFlags |= 8;
            SYS_SetFlag(g_SceneFlags, 0x2F);
            g_ScenarioState.state_04 = 0xF;
            g_AreaDrawFlags          = 0;
            g_ScenarioState.step     = 0xA;
            g_ScriptVars[0]          = 0;
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 7:
                    func_801C1E3C(2);
                    Scene_RunScenario(0xA);
                    break;
                case 8:
                    func_801C1E3C(2);
                    func_801C1E3C(7);
                    Scene_RunScenario(0xB);
                    break;
                case 9:
                    func_801C1E3C(2);
                    func_801C1E3C(8);
                    Scene_RunScenario(0xB);
                    break;
                case 10:
                    func_801C1E3C(2);
                    Scene_RunScenario(0xC);
                    break;
                case 11:
                case 12:
                    break;
                case 13:
                    func_801C1E3C(7);
                    Scene_RunScenario(0xA);
                    break;
                case 14:
                    func_801C1E3C(8);
                    Scene_RunScenario(0xA);
                    break;
                case 15:
                    break;
                case 16:
                    func_801C1E3C(7);
                    func_801C1E3C(8);
                    Scene_RunScenario(0xB);
                    break;
                case 17:
                    func_801C1E3C(7);
                    Scene_RunScenario(0xC);
                    break;
                case 18:
                    func_801C1E3C(8);
                    Scene_RunScenario(0xC);
                    break;
            }
        }
    }
    if (g_GameAreaId == AREA_ID_WYNDIA_CASTLE) {
        if (!SYS_TestFlag(g_SceneFlags, 0x30)) {
            Area_ScrollStartRoute(2);
        }
        if (SYS_TestFlag(g_SceneFlags, 0x36) && SYS_TestFlag(g_SceneFlags, 0x31) && g_GameCellType == 0 && !SYS_TestFlag(g_SceneFlags, 0x34)) {
            Game_SetScriptActive();
            g_ScenarioState.step = 0x46;
            g_GameFlags |= 8;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 0xF;
        }
    }
    if (g_GameAreaId == AREA_ID_WYNDIA_CASTLE_BASEMENT) {
        if (!SYS_TestFlag(g_SceneFlags, 0x32)) {
            SYS_SetFlag(g_SceneFlags, 0x32);
            g_AreaDrawFlags = 0;
            Game_SetScriptActive();
            g_ScenarioState.step     = 0x3C;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 0xF;
        }
        if (g_ScriptVars[2] == 1 && SYS_TestFlag(g_SceneFlags, 0x38) && g_GameCellType == 0) {
            g_GameFlags |= 8;
            g_AreaDrawFlags = 0;
            Game_SetScriptActive();
            g_ScenarioState.step     = 0x6E;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 0xF;
        }
    }
    if (g_GameAreaId == AREA_ID_CAMP_BEFORE_ANGEL_TOWER) {
        if (!SYS_TestFlag(g_SceneFlags, 0x2E)) {
            Area_ScrollStartRoute(2);
        }
    }
    if (g_GameAreaId == AREA_ID_YGGDRASIL_MASTER) {
        if (SYS_TestFlag(g_SceneFlags, 4) && !SYS_TestFlag(g_SceneFlags, 5)) {
            Game_SetScriptActive();
            g_AreaCameraRefreshCount = 2;
            g_ScenarioState.state_04 = 3;
            g_AreaDrawFlags          = 0;
            g_ScenarioState.step     = 0;
            g_ScriptVars[0]          = 0;
            g_AreaCameraOffsetZ += 0xA80;
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 7:
                    func_801C1E3C(1);
                    Scene_RunScenario(2);
                    break;
                case 8:
                    func_801C1E3C(2);
                    Scene_RunScenario(4);
                    break;
                case 9:
                case 11:
                case 12:
                    break;
                case 10:
                    func_801C1E3C(2);
                    Scene_RunScenario(3);
                    break;
                case 13:
                    func_801C1E3C(0);
                    Scene_RunScenario(2);
                    break;
                case 14:
                case 16:
                    break;
                case 15:
                    func_801C1E3C(0);
                    Scene_RunScenario(3);
                    break;
                case 17:
                    break;
            }
        }
    }
    if (g_GameAreaId == AREA_ID_EYGNOCK_ROAD) {
        if (!SYS_TestFlag(g_SceneFlags, 0)) {
            g_AreaDrawFlags          = 0;
            g_ScenarioState.state_04 = 1;
            g_ScenarioState.step     = 0;
            g_ScriptVars[0]          = 0;
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 7:
                    func_801C1E3C(0);
                    Scene_RunScenario(0);
                    break;
                case 10:
                    break;
                case 15:
                    func_801C1E3C(0);
                    Scene_RunScenario(1);
                    break;
            }
        }
    }
    if (g_GameAreaId == AREA_ID_PLANT) {
        if (SYS_TestFlag(g_SceneFlags, 2) && !SYS_TestFlag(g_SceneFlags, 3)) {
            Area_ScrollStartRoute(2);
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 7:
                    func_801C1E3C(1);
                    Scene_RunScenario(2);
                    break;
                case 10:
                    func_801C1E3C(2);
                    Scene_RunScenario(3);
                    break;
                case 15:
                    func_801C1E3C(0);
                    Scene_RunScenario(3);
                    break;
            }
        }
        if (SYS_TestFlag(g_SceneFlags, 6) && !SYS_TestFlag(g_SceneFlags, 7)) {
            g_AreaDrawFlags          = 0;
            g_ScenarioState.state_04 = 4;
            g_ScenarioState.step     = 0;
            g_ScriptVars[0]          = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
        }
        if (g_ScriptVars[2] == 1) {
            g_AreaDrawFlags          = 0;
            g_AreaCameraRefreshCount = 2;
            g_AreaCameraOffsetZ += 0xB80;
        }
        if (g_GameCellType == 1 && !SYS_TestFlag(g_SceneFlags, 0x1E)) {
            SYS_ClearFlag(g_SceneFlags, 0x11);
        }
    }
    if (g_GameAreaId == AREA_ID_WYNDIA_BASEMENT_TELEPORTER) {
        s32 phase = g_ScriptVars[2];

        switch (phase) {
            case 0:
            case 1:
                break;
            case 2:
                if (SYS_TestFlag(g_SceneFlags, 0x38) && g_GameCellType == 2) {
                    g_AreaDrawFlags = 0;
                    Game_SetScriptActive();
                    g_ScenarioState.step     = 0x78;
                    g_ScriptVars[0]          = 0;
                    g_ScenarioState.state_04 = 0xF;
                }
                break;
        }
    }
    if (g_GameAreaId == AREA_ID_HIDDEN_FACTORY_ROOMS && g_GameCellType == 4) {
        if (!SYS_TestFlag(g_SceneFlags, 0x13)) {
            Game_SetScriptActive();
            g_ScenarioState.state_04    = 7;
            g_ScenarioState.step        = 0;
            g_ScriptVars[0]             = 0;
            g_ScriptVars[1]             = 0;
            g_ScriptVars[2]             = 0;
            g_ScriptVars[3]             = 0;
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x96;
            }
            if (g_Game.members[0].pos.z.fixed <= TO_COORD(0x200)) {
                g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x95;
                }
            }
        } else if (g_Game.members[0].pos.z.fixed <= TO_COORD(0x200)) {
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x96;
            }
            if (g_Game.members[0].pos.z.fixed <= TO_COORD(0x200)) {
                g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x95;
                }
            }
        }
    }
    if (g_GameAreaId == AREA_ID_HIDDEN_FACTORY_HUGE_SLUG && g_GameCellType == 2 && SYS_TestFlag(g_SceneFlags, 0x3D) && !SYS_TestFlag(g_SceneFlags, 0x16)) {
        g_GameFlags |= 8;
        g_AreaDrawFlags = 0;
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 8;
        g_ScenarioState.step     = 0x1E;
        g_ScriptVars[0]          = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        SYS_SetFlag(g_SceneFlags, 0x16);
    }
    if (g_GameAreaId == AREA_ID_WYNDIA_WORLD_MAP || g_GameAreaId == AREA_ID_MOMO_TOWER_WORLD_MAP || g_GameAreaId == AREA_ID_RHAPALA_WORLD_MAP || g_GameAreaId == AREA_ID_YRAAL_WORLD_MAP ||
        g_GameAreaId == AREA_ID_DAUNA_WORLD_MAP) {
        g_ScriptVars[0] = 0;
        g_ScriptVars[1] = 0;
        g_ScriptVars[2] = 0;
        g_ScriptVars[3] = 0;
    }
    g_ScenarioState.mode_02 = 2;
}

MATCH void func_801F83D8(void) {
    SYS_DISPATCH_BYTE(D_801FE3EC, g_ScenarioState.state_04);
}

MATCH void func_801F8414(void) {
}

MATCH void func_801F841C(void) {
    u8* step = &g_ScenarioState.step;

    switch (*step) {
        case 0:
            *step = 1;
            SYS_SetFlag(g_SceneFlags, 0);
            Game_RequestAreaChange(AREA_ID_EYGNOCK_ROAD, TO_COORD_HALF(31), TO_COORD(76), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
            break;
        case 1:
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            *step           = 2;
            break;
        case 2:
            if (*g_ScriptVars == 0x11) {
                SYS_SetFlag(g_SceneFlags, 1);
                Game_ClearScriptActive();
                *step                    = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}
