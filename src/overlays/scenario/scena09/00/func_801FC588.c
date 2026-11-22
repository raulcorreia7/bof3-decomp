#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC588(void) {
}

MATCH void func_801FC590(void) {
    u8 cam                   = D_801FE430[g_ScenarioState.timer_06 & 3];
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = g_AreaCameraOffsetY + ((cam << 24) >> 22);
}

MATCH void func_801FC5DC(void) {
}

#include "overlays/scenario/shared/Scene_DispatchActor.h"

MATCH void func_801FC624(void) {
}

MATCH void func_801FC62C(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 5;
}

MATCH void func_801FC668(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]          = 0;
    g_ScenarioState.step     = 5;
    g_ScenarioState.state_04 = 5;
}

MATCH void func_801FC6A4(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 5;
    g_ScenarioState.state_04 = 4;
}

MATCH void func_801FC6DC(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xA;
    g_ScenarioState.step     = 0;
}

MATCH void func_801FC710(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xA;
    g_ScenarioState.step     = 1;
}

MATCH void func_801FC748(void) {
    *SP_REF(s8*, 0x44) = 0;
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xD;
    g_ScenarioState.step     = 5;
}

MATCH void func_801FC788(void) {
    SYS_SetFlag(g_SceneFlags, 0xEU);
}

MATCH void func_801FC7B0(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 6;
    g_ScenarioState.step     = 0x64;
}

MATCH void func_801FC7E8(void) {
    SYS_SetFlag(g_SceneFlags, 0x10U);
}

MATCH void func_801FC810(void) {
    SYS_SetFlag(g_SceneFlags, 0x14U);
}

MATCH void func_801FC838(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 8;
    g_ScenarioState.step     = 0xF;
}

MATCH void func_801FC870(void) {
}

MATCH void func_801FC878(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xF;
    g_ScenarioState.step     = 0;
}

MATCH void func_801FC8AC(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xF;
    g_ScenarioState.step     = 0x14;
}

MATCH void func_801FC8E4(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xF;
    g_ScenarioState.step     = 0x28;
}

/* Starts the scene script for the trigger cell at (x, y) in the current area; returns 1 when one starts. */
MATCH s32 func_801FC91C(s32 x, s32 y) {
    if (LOHU(g_GameAreaId) == AREA_ID_WYNDIA_LOWER) {
        if (SYS_TestFlag(g_SceneFlags, 0x2E) && !SYS_TestFlag(g_SceneFlags, 0x38) && (u32)(x - TO_COORD(32)) <= TO_COORD_HALF(3) && (u32)(y - TO_COORD(65)) <= COORD_HALF) {
            Game_SetScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 0xF;
            g_ScenarioState.state_04 = 0xF;
            return 1;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_WYNDIA_CASTLE) {
        if ((x == TO_COORD(49) || x == TO_COORD_HALF(49)) && (u32)(y - TO_COORD(39)) <= TO_COORD_HALF(2)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0x1E;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 0xF;
            return 1;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_WYNDIA_CASTLE_BASEMENT) {
        if (SYS_TestFlag(g_SceneFlags, 0x38) && !SYS_TestFlag(g_SceneFlags, 0x23)) {
            if ((x == TO_COORD(64) || x <= TO_COORD_HALF(64)) && (u32)(y - TO_COORD(39)) <= TO_COORD_HALF(1)) {
                Game_SetScriptActive();
                g_ScenarioState.step     = 0x64;
                g_ScriptVars[0]          = 0;
                g_ScenarioState.state_04 = 0xF;
                return 1;
            }
            if ((u32)(x - TO_COORD(72)) <= TO_COORD_HALF(3) && (y == TO_COORD(37) || y == TO_COORD_HALF(37))) {
                Game_SetScriptActive();
                g_ScenarioState.step     = 0x64;
                g_ScriptVars[0]          = 0;
                g_ScenarioState.state_04 = 0xF;
                return 1;
            }
            if ((x == TO_COORD(4) || x == TO_COORD_HALF(3)) && (u32)(y - TO_COORD(2)) <= TO_COORD_HALF(1)) {
                Game_SetScriptActive();
                g_ScenarioState.step     = 0x64;
                g_ScriptVars[0]          = 0;
                g_ScenarioState.state_04 = 0xF;
                return 1;
            }
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_RHAPALA_CHECKPOINT) {
        if (SYS_TestFlag(g_SceneFlags, 0x23) && !SYS_TestFlag(g_SceneFlags, 0x24) && (u32)(x - TO_COORD(15)) <= TO_COORD_HALF(1) && (y == TO_COORD(34) || y == TO_COORD_HALF(34))) {
            Game_SetScriptActive();
            g_ScriptVars[0]          = 1;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0x10;
            return 1;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_PLANT) {
        if (!SYS_TestFlag(g_SceneFlags, 2)) {
            if ((u32)(x - TO_COORD_HALF(38)) <= TO_COORD(5) && (u32)(y - TO_COORD(43)) <= TO_COORD_HALF(4)) {
                SYS_SetFlag(g_SceneFlags, 0x25);
                Game_SetScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 2;
                return 1;
            }
        } else if (!SYS_TestFlag(g_SceneFlags, 4) && (u32)(x - TO_COORD(41)) <= TO_COORD_HALF(2) && (u32)(y - TO_COORD(92)) <= COORD_HALF) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0xA;
            g_ScriptVars[0]          = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.state_04 = 2;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0x1E) && !SYS_TestFlag(g_SceneFlags, 0x2E) && (u32)(x - TO_COORD(78)) <= COORD_HALF && (u32)(y - TO_COORD(34)) <= TO_COORD_HALF(3)) {
            D_80146258 |= 0xE;
            Game_SetScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0xE;
            return 1;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_DURANDAL) {
        if (SYS_TestFlag(g_SceneFlags, 0x3A)) {
            if (!SYS_TestFlag(g_SceneFlags, 0x22)) {
                if ((u32)(x - TO_COORD(71)) <= TO_COORD_HALF(2) && (u32)(y - TO_COORD(9)) <= TO_COORD_HALF(1)) {
                    Game_SetScriptActive();
                    g_ScenarioState.step     = 0x82;
                    g_ScriptVars[0]          = 0;
                    g_ScriptVars[1]          = 0;
                    g_ScriptVars[2]          = 0;
                    g_ScriptVars[3]          = 0;
                    g_ScenarioState.state_04 = 0xF;
                    return 1;
                }
            } else if (!SYS_TestFlag(g_SceneFlags, 0x23) && (u32)(x - TO_COORD(41)) <= COORD_HALF && (u32)(y - TO_COORD(17)) <= TO_COORD_HALF(7)) {
                Game_SetScriptActive();
                g_ScenarioState.step     = 0x8C;
                g_ScriptVars[0]          = 0;
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.state_04 = 0xF;
                return 1;
            }
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_HIDDEN_FACTORY_HUGE_SLUG) {
        if (SYS_TestFlag(g_SceneFlags, 0x3D) && !SYS_TestFlag(g_SceneFlags, 0x15) && (u32)(x - TO_COORD(66)) <= TO_COORD_HALF(2) && (u32)(y - TO_COORD(60)) <= TO_COORD_HALF(2)) {
            SYS_SetFlag(g_SceneFlags, 0x15);
            Game_SetScriptActive();
            g_ScenarioState.step     = 0x14;
            g_ScriptVars[0]          = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.state_04 = 8;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0x3D) && !SYS_TestFlag(g_SceneFlags, 0x16) && (u32)(x - TO_COORD(66)) <= TO_COORD_HALF(2) && (u32)(y - TO_COORD(65)) <= TO_COORD_HALF(2)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0x19;
            g_ScriptVars[0]          = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.state_04 = 8;
            return 1;
        }
        if (!SYS_TestFlag(g_SceneFlags, 0x1E)) {
            if ((u32)(x - TO_COORD(10)) <= COORD_HALF && (u32)(y - TO_COORD(2)) <= TO_COORD(1)) {
                Game_SetScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 9;
                return 1;
            }
        } else if (!SYS_TestFlag(g_SceneFlags, 0x2C) && (u32)(x - TO_COORD(6)) <= COORD_HALF && (u32)(y - TO_COORD(2)) <= TO_COORD(1)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0x1E;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 9;
            return 1;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_ANGEL_TOWER_OUTSIDE && g_GameCellType == 0) {
        if (SYS_TestFlag(g_SceneFlags, 0x20) && !SYS_TestFlag(g_SceneFlags, 0x21) && (u32)((y >> 16) - 0x40) < 5 && (u32)((x >> 16) - 0x22) < 4) {
            SYS_SetFlag(g_SceneFlags, 0x21);
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 0xB;
            g_ScenarioState.step     = 0x1E;
            return 1;
        }
        if ((u32)((y >> 16) - 0x3C) < 5 && (u32)((x >> 16) - 0x22) < 4) {
            g_ScratchPad.cells.bytes[0] = D_80145E98;
            if (g_ScratchPad.cells.bytes[0] != 5 && g_ScratchPad.cells.bytes[0] != 6 && g_ScratchPad.cells.bytes[0] != 4) {
                if (D_80145F09 != CHAR_ID_GARR) {
                    if (!SYS_TestFlag(g_SceneFlags, 0x20) || SYS_TestFlag(g_SceneFlags, 0x21)) {
                        g_ScriptVars[0] = 0x10;
                        Game_SetScriptActive();
                        return 1;
                    }
                } else if (!SYS_TestFlag(g_SceneFlags, 0x20)) {
                    Game_SetScriptActive();
                    g_ScenarioState.state_04 = 0xB;
                    g_ScenarioState.step     = 0;
                    return 1;
                }
            }
        }
    }
    return 0;
}

MATCH s32 func_801FD278(void) {
    return 0;
}

MATCH s8 func_801FD280(s32 x, s32 y) {
    SCENE_PROBE_POSITION(D_801FE474, 14, D_801FE4BC);
}

MATCH s32 func_801FD2E8(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xC) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0x14;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else {
            Game_SetScriptActive();
            g_ScenarioState.step     = 5;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
    }
    Game_SetScriptActive();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 6;
    return 1;
}

MATCH s32 func_801FD388(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xC) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 2;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0xE) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 3;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0xD) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0x1E;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else {
            Game_SetScriptActive();
            g_ScenarioState.step     = 5;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
    } else {
        Game_SetScriptActive();
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 6;
        return 1;
    }
}

MATCH s32 func_801FD498(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xE) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 2;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0x10) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 3;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0xF) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0x28;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else {
            Game_SetScriptActive();
            g_ScenarioState.step     = 5;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
    } else {
        Game_SetScriptActive();
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 6;
        return 1;
    }
}

MATCH s32 func_801FD5A8(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0x10) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 2;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0x12) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 3;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0x1D) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 50;
            *g_ScriptVars            = 0;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0x11) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 7;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else {
            Game_SetScriptActive();
            g_ScenarioState.step     = 5;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
    } else {
        Game_SetScriptActive();
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 6;
        return 1;
    }
}

MATCH s32 func_801FD6F8(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xC) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 2;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0xE) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 3;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0xD) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 6;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        g_AreaSceneMode = 2;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 6;
    return 1;
}

MATCH s32 func_801FD7F4(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xD) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 2;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0x10) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 3;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0xF) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 6;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        g_AreaSceneMode = 3;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 6;
    return 1;
}

MATCH s32 func_801FD8F0(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 5;
        g_ScenarioState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x18);
    return 1;
}

MATCH s32 func_801FD978(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 5;
        g_ScenarioState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step     = 1;
    g_ScenarioState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x19);
    return 1;
}

MATCH s32 func_801FDA04(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 5;
        g_ScenarioState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step     = 2;
    g_ScenarioState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x1A);
    return 1;
}

MATCH s32 func_801FDA90(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 5;
        g_ScenarioState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step     = 3;
    g_ScenarioState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x1B);
    return 1;
}

MATCH s32 func_801FDB1C(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 5;
        g_ScenarioState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step     = 4;
    g_ScenarioState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x1C);
    return 1;
}

MATCH s32 func_801FDBA8(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        SYS_SetFlag(g_SceneFlags, 0x3D);
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x03));
        return 1;
    }

    Game_SetScriptActive();
    g_ScenarioState.step     = 6;
    g_ScenarioState.state_04 = 8;
    return 1;
}

MATCH s32 func_801FDC1C(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x2C) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 0x14;
        g_ScenarioState.state_04 = 9;
        return 1;
    }
    return -1;
}

MATCH s32 func_801FDC70(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x33) != 0) {
        return -1;
    }
    if (g_Game.members[0].chr.character_id != CHAR_ID_REI) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 0x34;
        g_ScenarioState.state_04 = 0x0F;
        return 1;
    }
    *g_ScriptVars = 0;
    Game_SetScriptActive();
    g_ScenarioState.step     = 0x32;
    g_ScenarioState.state_04 = 0x0F;
    return 1;
}

/* func_801FDCF4 */
MATCH void Scene_JoinAdultNinaWithGarr(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_GARR, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FDD38 */
MATCH void Scene_JoinGarrWithAdultNina(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_GARR, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_GARR);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_JoinAdultNinaMomo.h"

#include "overlays/scenario/shared/Scene_JoinMomo.h"

#include "overlays/scenario/shared/Scene_JoinAdultNina.h"

MATCH void func_801FDE50(void) {
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_PECO);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_JoinMomoPeco.h"

#include "overlays/scenario/shared/Scene_JoinPeco.h"

/* func_801FDF10 */
MATCH void Scene_JoinMomoWithPeco(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_PECO, CHAR_ID_MOMO, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_RebuildRyuGarrParty.h"

/* func_801FE014 */
MATCH void Scene_JoinAdultNinaWithRei(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FE058 */
MATCH void Scene_JoinReiAdultNina(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_REI);
    Party_MemberJoin(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FE0A4 */
MATCH void Scene_JoinReiWithAdultNina(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_REI);
    Party_LoadPalettes();
}

/* func_801FE0E8 */
MATCH void Scene_JoinRyuAdult(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_RemoveRei.h"

/* func_801FE154 */
MATCH void Scene_RemoveReiGarr(void) {
    Party_MemberRemove(CHAR_ID_REI);
    Party_MemberRemove(CHAR_ID_GARR);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_RemoveGarr.h"

/* func_801FE1AC */
MATCH void Scene_RemoveGarrAdultNina(void) {
    Party_MemberRemove(CHAR_ID_GARR);
    Party_MemberRemove(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FE1DC */
MATCH void Scene_RemoveReiAdultNina(void) {
    Party_MemberRemove(CHAR_ID_REI);
    Party_MemberRemove(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_RemoveAdultNina.h"

#include "overlays/scenario/shared/Scene_StashPartyExceptRyuAdult.h"

#include "overlays/scenario/shared/Scene_RemoveMomo.h"

#include "overlays/scenario/shared/Scene_RemovePeco.h"

/* func_801FE35C */
MATCH void Scene_RemoveRyuAdult(void) {
    Party_MemberRemove(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}
