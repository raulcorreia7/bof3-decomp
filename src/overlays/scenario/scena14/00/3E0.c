#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6FE0(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    SYS_DISPATCH_INDEX(D_801FC418, index);
}

MATCH void func_801F7014(void) {
    D_80146872 = 1;
}

/* Sets up each area of the chapter on entry from the scene flags: party placement, camera, actors and pending steps. */
MATCH void func_801F7028(void) {
    SpawnedActor* actor;
    s32           slot;

    if (LOHU(g_GameAreaId) == AREA_ID_CEDAR_WOODS_HOUSE_BALIO_SUNDER && SYS_TestFlag(g_SceneFlags, 0x13) && !SYS_TestFlag(g_SceneFlags, 0x14)) {
        g_AreaDrawFlags = 0;
        func_801C1DF0(3);
        func_801BE1B0(5);
        g_AreaCameraAngle.vx = -0x462;
        g_AreaCameraAngle.vz = 0x3B8;
        func_801F7960();
    }
    if (LOHU(g_GameAreaId) == AREA_ID_MIKBA_CHECKPOINT) {
        if (SYS_TestFlag(g_SceneFlags, 0x13) && !SYS_TestFlag(g_SceneFlags, 0x14)) {
            func_801C1DF0(4);
            func_801BE1B0(5);
            func_801BFE34(0x150000, 0x190000, 0x22);
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_MOUNT_ZUBLO_GISSHAN && SYS_TestFlag(g_SceneFlags, 0x13) && !SYS_TestFlag(g_SceneFlags, 0x14)) {
        func_801C1DF0(5);
        func_801BE1B0(1);
        func_801BFE34(0x4A0000, 0x220000, 0x1E);
    }
    if (LOHU(g_GameAreaId) == AREA_ID_CLIFF_GAIST) {
        if (SYS_TestFlag(g_SceneFlags, 0x13) && !SYS_TestFlag(g_SceneFlags, 0x14)) {
            func_801C1DF0(6);
            func_801BE1B0(8);
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_RYU_DREAM_FIRST) {
        if (!SYS_TestFlag(g_SceneFlags, 0x14)) {
            g_AreaCameraOffsetZ = 0x7F00;
            func_801C1DF0(9);
            func_801BE1B0(0);
            Scene_SpawnActor(0x31, g_AreaCameraAngle.vx, g_AreaCameraAngle.vy, g_AreaCameraAngle.vz, 0xF0, 0);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
        }
        if (g_GameCellType == 1 && !SYS_TestFlag(g_SceneFlags, 0x18)) {
            SYS_SetFlag(g_SceneFlags, 0x18);
            func_801BE1B0(4);
            func_801F4584();
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_RYU_DREAM_LAST) {
        if (!SYS_TestFlag(g_SceneFlags, 0x1B)) {
            SYS_SetFlag(g_SceneFlags, 0x1B);
            func_801C1DF0(0xA);
        }
        if (g_GameCellType == 2 && !SYS_TestFlag(g_SceneFlags, 0x1D)) {
            SYS_SetFlag(g_SceneFlags, 0x1D);
            func_801BE1B0(1);
        }
        if (g_GameCellType == 3 && !SYS_TestFlag(g_SceneFlags, 0x1E)) {
            SYS_SetFlag(g_SceneFlags, 0x1E);
            func_801BE1B0(2);
            g_ScenarioState.state_04 = 7;
            g_ScenarioState.step     = 6;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_DRAGNIER_ELDER_FIGHT && SYS_TestFlag(g_SceneFlags, 0x13) && !SYS_TestFlag(g_SceneFlags, 0x14)) {
        func_801C1DF0(7);
        func_801BE1B0(9);
        func_801BFE34(0x288000, 0x1D8000, 0x25);
    }
    if (LOHU(g_GameAreaId) == AREA_ID_CAER_XHAN_HONEY_ROOM) {
        if (!SYS_TestFlag(g_SceneFlags, 0x35)) {
            SYS_SetFlag(g_SceneFlags, 0x35);
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_OASIS) {
        if (!SYS_TestFlag(g_SceneFlags, 0xA)) {
            if (g_GameCellType == 0) {
                func_801C1DF0(1);
                func_801BE1B0(0);
            }
            g_GameCellType  = 3;
            g_AreaSceneMode = 1;
        } else if (!SYS_TestFlag(g_SceneFlags, 0xB) && g_GameCellType == 0) {
            func_801C1DF0(2);
            func_801BE1B0(2);
            g_AreaDrawFlags          = 0;
            g_ScenarioState.timer_06 = 0x3C;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_EDEN_TEEPO_FIGHT && g_GameCellType == 0) {
        if (!SYS_TestFlag(g_SceneFlags, 0x12)) {
            g_AreaCameraAngle.vx = -0x2AA;
            g_AreaCameraAngle.vz = 6;
            g_AreaCameraOffsetZ  = 0x900;
            Scene_SpawnActor(0x13, -0x2AA, g_AreaCameraAngle.vy, 0x3A2, 0xE7, 0);
        } else if (SYS_TestFlag(g_SceneFlags, 0x13)) {
            if (!SYS_TestFlag(g_SceneFlags, 0x14)) {
                g_AreaDrawFlags = 0x1F;
                func_801C1DF0(8);
                func_801BE1B0(8);
            } else if (!SYS_TestFlag(g_SceneFlags, 0x1F)) {
                g_AreaCameraOffsetZ = 0x200;
            } else if (!SYS_TestFlag(g_SceneFlags, 0x30)) {
                func_801C1DF0(0xC);
                func_801BE1B0(0xB);
                SYS_SetFlag(g_SceneFlags, 0x30);
                slot = func_8019601C() & 0xFF;
                if (slot != 0xFF) {
                    actor               = &g_SpawnedActors[slot];
                    actor->pos.x.fixed  = 0x1C8000;
                    actor->header.flags = 1;
                    actor->type         = 0x98;
                    actor->pos.y.fixed  = 0x268000;
                    actor->pos.z.fixed  = (Area_HeightSample(actor->pos.x.fixed, 0x268000) << 16) + 0x800000;
                }
            }
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_DESERT_OF_DEATH_MAP && SYS_TestFlag(g_SceneFlags, 1)) {
        g_SpawnedActors[0].header.flags |= 0x40;
    }
    if (LOHU(g_GameAreaId) == AREA_ID_DESERT_CAMP_FIRST) {
        if (g_GameCellType == 0 && SYS_TestFlag(g_SceneFlags, 5)) {
            if (!SYS_TestFlag(g_SceneFlags, 6)) {
                g_AreaCameraOffsetZ = 0x600;
                Scene_SpawnActor(0x31, g_AreaCameraAngle.vx, g_AreaCameraAngle.vy, g_AreaCameraAngle.vz, 0xE8, 0);
                func_801C1E3C(0);
                func_801BE1B0(0);
            } else if (!SYS_TestFlag(g_SceneFlags, 7)) {
                SYS_SetFlag(g_SceneFlags, 7);
                func_801BE1B0(2);
            }
        }
        if (g_GameCellType == 1 && SYS_TestFlag(g_SceneFlags, 5) && SYS_TestFlag(g_SceneFlags, 8)) {
            SYS_SetFlag(g_SceneFlags, 9);
            SYS_ClearFlag(g_SceneFlags, 5);
            func_801BE1B0(5);
            g_AreaScrollTargetX = 0x468000;
            g_AreaScrollTargetY = 0xD8000;
            Area_InitMapRenderer();
            g_ScenarioState.state_04 = 2;
            g_ScenarioState.step     = 0x1E;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_DESERT_ENTRANCE_CAMP && !SYS_TestFlag(g_SceneFlags, 0)) {
        SYS_SetFlag(g_SceneFlags, 0);
        func_801C1DF0(0);
        func_801BE1B0(0);
    }
    if (LOHU(g_GameAreaId) == AREA_ID_MYRIA_STATION_CHIMERA) {
        if (!SYS_TestFlag(g_SceneFlags, 0xD)) {
            SYS_SetFlag(g_SceneFlags, 0xD);
            func_801BE1B0(1);
            g_ScenarioState.state_04 = 5;
            g_ScenarioState.step     = 0;
        }
        if (LOBU(g_GameLastCellType) == 5 && !SYS_TestFlag(g_SceneFlags, 0xF)) {
            func_801BE1B0(2);
            g_ScenarioState.state_04 = 5;
            g_ScenarioState.step     = 0xA;
        }
    }
    D_80146872 = 2;
}

/* Averages each working palette colour's red, green and blue channels into a
 * grey level and keeps the mask bit, then marks the palette for upload. */
MATCH void func_801F7960(void) {
    u16* cell;
    u32  row;
    u32  col;
    u32  row_base;
    u32  color;
    u32  red;
    u32  rgb;
    u32  average;
    u32  packed;

    row = 0;
    do {
        col      = 0;
        row_base = AREA_PALETTE_WORK + (row & 0xFF) * AREA_PALETTE_ROW;
        do {
            cell    = MEM_PTR(u16, (col & 0xFFFF) * 2 + row_base);
            color   = *cell;
            red     = color & 0x1F;
            rgb     = color & 0xFFFF;
            average = (red + ((rgb >> 5) & 0x1F) + ((rgb >> 10) & 0x1F)) / 3;
            packed  = color & 0x8000;
            packed |= average << 10;
            packed |= average << 5;
            *cell = average | packed;
            col++;
        } while ((col & 0xFFFF) < AREA_PALETTE_COLORS);
        row++;
    } while ((row & 0xFF) < AREA_PALETTE_ROWS);
    g_GfxPalettePending = 1;
}

#include "overlays/scenario/shared/Scene_SpawnActor.h"

MATCH bool Scene_SpawnActor(u8 type, s16 angle_x, s16 angle_y, s16 angle_z, u8 layer, s32 vx){SCENE_SPAWN_ACTOR(D_801FC4C0)}

MATCH void func_801F7B5C(void) {
    SYS_DISPATCH_BYTE(D_801FC424, g_ScenarioState.state_04);
}

MATCH void func_801F7B98(void) {
}
