#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchActor.h"

MATCH void func_801FCE10(void) {
}

MATCH void func_801FCE18(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 1;
}

MATCH void func_801FCE6C(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 2;
}

MATCH void func_801FCEC0(void) {
    if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 0xA;
        *g_ScriptVars            = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.state_04 = 2;
    }
}

MATCH void func_801FCF30(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 15;
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 2;
    SYS_SetFlag(g_SceneFlags, 4);
}

MATCH void func_801FCF98(void) {
    SYS_SetFlag(g_SceneFlags, 12U);
}

MATCH void func_801FCFC0(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 4;
}

MATCH void func_801FD014(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 20;
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 4;
}

MATCH void func_801FD06C(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]          = 1;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 6;
}

MATCH void func_801FD0C4(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 20;
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 6;
}

MATCH void func_801FD11C(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 10;
}

MATCH void func_801FD170(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 10;
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 14;
}

MATCH void func_801FD1C8(void) {
    Game_SetScriptActive();
    *g_ScriptVars   = 0;
    g_ScriptVars[1] = 0;
    if (SYS_TestFlag(g_SceneFlags, 34) == 0) {
        g_ScenarioState.step = 0;
    } else {
        g_ScenarioState.step = 0x14;
    }
    g_ScenarioState.state_04 = 0x10;
}

MATCH void func_801FD234(void) {
    Game_SetScriptActive();
    *g_ScriptVars   = 0;
    g_ScriptVars[1] = 0;
    if (SYS_TestFlag(g_SceneFlags, 35) != 0) {
        g_ScenarioState.step = 0x14;
    } else {
        g_ScenarioState.step = 0xA;
    }
    g_ScenarioState.state_04 = 0x10;
}

MATCH s32 func_801FD294(void) {
    return 0;
}

MATCH void func_801FD29C(void) {
    g_Characters[7].hp                 = D_801FE464[0];
    g_Characters[7].equip.weapon       = D_801FE464[6];
    g_Characters[7].equip.armor        = D_801FE464[7];
    g_Characters[7].stats.max_hp       = D_801FE464[1];
    g_Characters[7].base.max_hp        = D_801FE464[1];
    g_Characters[7].stats.power        = D_801FE464[2];
    g_Characters[7].base.power         = D_801FE464[2];
    g_Characters[7].stats.defense      = D_801FE464[3];
    g_Characters[7].base.defense       = D_801FE464[3];
    g_Characters[7].stats.agility      = D_801FE464[4];
    g_Characters[7].base.agility       = D_801FE464[4];
    g_Characters[7].stats.intelligence = D_801FE464[5];
    g_Characters[7].base.intelligence  = D_801FE464[5];
}

MATCH s8 func_801FD34C(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags) {
    return D_801FE46C[SELF(Actor)->unk_04](entry, dir_x, dir_y, vz_start, vz_delta, landing_script, flags);
}

MATCH s8 func_801FD3BC(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags) {
    u8  size;
    s32 absX;
    s32 absY;
    u8  span;

    size = g_RouteSpeedScale[((Actor*)entry)->unk_04];
    if (size == 0) {
        return 0;
    }
    absY               = abs(dir_y);
    SELF(Actor)->timer = 0;
    span               = absY;
    absX               = abs(dir_x);
    if (absX >= absY) {
        span = absX;
    }
    if (span != 0) {
        SELF(Actor)->param.unk_0B = span - 1;
    } else {
        SELF(Actor)->param.unk_0B = 0;
    }
    SELF(Actor)->unk_0A = 16 / size;
    SELF(Actor)->vz     = vz_start << 8;
    if (span != 0) {
        SELF(Actor)->vx = (dir_x << 15) / (SELF(Actor)->unk_0A * span);
        SELF(Actor)->vy = (dir_y << 15) / (SELF(Actor)->unk_0A * span);
    } else {
        SELF(Actor)->vy = 0;
        SELF(Actor)->vx = 0;
    }
    SELF(Actor)->unk_04 = 1;
    return 1;
}

MATCH s8 func_801FD568(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags) {
    Actor* work;
    s32    speed;
    s16    height;
    u8     count;
    s32    sum;

    work              = SELF(Actor);
    speed             = work->vz;
    sum               = work->pos.x.fixed;
    count             = work->unk_0A - 1;
    work->pos.x.fixed = sum + work->vx;
    work->pos.y.fixed += work->vy;
    COORD_INT(work->pos.z) += work->vz >> 8;
    work->unk_0A = count;
    work->vz     = speed + vz_delta;
    height       = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    if (SELF(Actor)->vz < 0 && height > COORD_INT(SELF(Actor)->pos.z) + 576) {
        COORD_INT(SELF(Actor)->pos.z) = height + 576;
    }
    if (SELF(Actor)->vz <= 0 && speed >= 0 && landing_script != GAME_NONE) {
        SELF(Actor)->mirror = flags != 0;
        Script_Request(landing_script);
    }
    if (SELF(Actor)->unk_0A == 0) {
        if (SELF(Actor)->param.unk_0B != 0) {
            SELF(Actor)->unk_0A = 0x10 / g_RouteSpeedScale[((Actor*)entry)->unk_04];
            SELF(Actor)->param.unk_0B -= 1;
        } else {
            Actor_ApplyVelocity();
            SELF(Actor)->unk_04 = 2;
        }
    }
    return 1;
}

MATCH s8 func_801FD748(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags) {
    s16 distance;
    s16 z;

    distance = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    z        = COORD_INT(SELF(Actor)->pos.z);
    if (distance < z - 0x240) {
        COORD_INT(SELF(Actor)->pos.z) = z + (SELF(Actor)->vz >> 8);
        SELF(Actor)->vz += vz_delta;
        return 1;
    }
    COORD_INT(SELF(Actor)->pos.z) = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) + 0x240;
    SELF(Actor)->unk_04           = 0;
    return 0;
}

MATCH s32 func_801FD800(s32 x, s32 y) {
    if (g_GameAreaId == AREA_ID_WYNDIA_CASTLE) {
        if ((x == TO_COORD(49) || x == TO_COORD_HALF(49)) && (u32)(y - TO_COORD(39)) <= TO_COORD_HALF(2)) {
            Game_SetScriptActive();
            g_ScriptVars[0]      = 10;
            g_ScenarioState.step = 5;
            SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
            g_ScenarioState.state_04 = 2;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 7) && SYS_TestFlag(g_SceneFlags, 8) == 0 && (y == TO_COORD(55) || y == TO_COORD_HALF(55)) && (u32)(x - TO_COORD(67)) <= TO_COORD_HALF(1)) {
            SYS_SetFlag(g_SceneFlags, 8);
            Game_SetScriptActive();
            SCRIPT_VARS_CLEAR_ALL();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 3;
        }
    }
    if (g_GameAreaId == AREA_ID_RHAPALA_ENTRANCE && SYS_TestFlag(g_SceneFlags, 16) && SYS_TestFlag(g_SceneFlags, 17) == 0 && (y == TO_COORD(82) || y == TO_COORD_HALF(82)) &&
        (u32)(x - TO_COORD(39)) <= TO_COORD_HALF(11)) {
        Game_SetScriptActive();
        SCRIPT_VARS_CLEAR_ALL();
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 5;
        return 1;
    }
    if (g_GameAreaId == AREA_ID_MAEKYSS_GORGE && SYS_TestFlag(g_SceneFlags, 0) == 0 && (y == TO_COORD(31) || y == TO_COORD_HALF(31)) && (u32)(x - TO_COORD(28)) <= TO_COORD_HALF(3)) {
        Game_SetScriptActive();
        SCRIPT_VARS_CLEAR_ALL();
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 12;
        return 1;
    }
    if (g_GameAreaId == AREA_ID_LIGHTHOUSE_INSIDE) {
        if (SYS_TestFlag(g_SceneFlags, 40) == 0 && SYS_TestFlag(g_SceneFlags, 39) && (x == TO_COORD(48) || x == TO_COORD_HALF(49)) && (u32)(y - TO_COORD(4)) <= TO_COORD_HALF(5)) {
            Game_SetScriptActive();
            SCRIPT_VARS_CLEAR_ALL();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 14;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 42) == 0 && SYS_TestFlag(g_SceneFlags, 39) && (x == TO_COORD_HALF(27) || x == TO_COORD(28)) && (u32)(y - TO_COORD(4)) <= TO_COORD_HALF(5)) {
            Game_SetScriptActive();
            g_ScriptVars[0]      = 20;
            g_ScenarioState.step = 20;
            SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
            g_ScenarioState.state_04 = 14;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_RHAPALA_DOCK) {
        if (SYS_TestFlag(g_SceneFlags, 13) && SYS_TestFlag(g_SceneFlags, 14) == 0 && (x == TO_COORD(67) || x == TO_COORD_HALF(67)) && (u32)(y - TO_COORD(50)) <= TO_COORD_HALF(2)) {
            Game_SetScriptActive();
            g_ScenarioState.step = 10;
            g_ScriptVars[0]      = 0;
            SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
            g_ScenarioState.state_04 = 4;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 30) == 0) {
            if ((x == TO_COORD_HALF(27) || x == TO_COORD(28)) && (u32)(y - TO_COORD(61)) <= TO_COORD_HALF(2)) {
                Game_SetScriptActive();
                g_ScenarioState.step = 30;
                g_ScriptVars[0]      = 0;
                SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
                g_ScenarioState.state_04 = 4;
                return 1;
            }
        } else if (SYS_TestFlag(g_SceneFlags, 36) == 0 && (x == TO_COORD_HALF(27) || x == TO_COORD(28)) && (u32)(y - TO_COORD(61)) <= TO_COORD_HALF(2)) {
            Game_SetScriptActive();
            g_ScriptVars[0]      = 20;
            g_ScenarioState.step = 5;
            SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
            g_ScenarioState.state_04 = 10;
            return 1;
        }
    }
    return 0;
}

MATCH s8 func_801FDD14(s32 x, s32 y) {
    SCENE_PROBE_POSITION(D_801FE478, 4, D_801FE48C);
}

MATCH s32 func_801FDD7C(void) {
    if (Item_Count(ITEM_CATEGORY_WEAPON, WEAPON_FLAME_CHRYSM, 0) == 0) {
        Game_SetScriptActive();
        g_ScriptVars[0]          = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 0xB;
        return 1;
    }

    Game_SetScriptActive();
    g_ScenarioState.step     = 5;
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 0xB;
    return 1;
}

MATCH void func_801FDE2C(void) {
}

MATCH s32 func_801FDE34(void) {
    if (!SYS_TestFlag(g_SceneFlags, 39)) {
        Game_SetScriptActive();
        g_ScriptVars[0]          = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 0xD;
        return 1;
    }
    return 1;
}

MATCH s32 func_801FDEA4(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x27) == 0) {
        Game_SetScriptActive();
        g_ScriptVars[0]          = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 15;
        return 1;
    } else if (SYS_TestFlag(g_SceneEventFlags, 5) == 0 || SYS_TestFlag(g_SceneEventFlags, 6) == 0) {
        Game_SetScriptActive();
        g_ScriptVars[0]          = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 15;
        return 1;
    } else if (SYS_TestFlag(g_SceneFlags, 0x2C) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 5;
        g_ScriptVars[0]          = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.state_04 = 15;
        return 1;
    } else {
        Game_SetScriptActive();
        g_ScenarioState.step     = 30;
        g_ScenarioState.state_04 = 15;
        return 1;
    }
}

MATCH void func_801FDFFC(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_RYU_YOUNG);
    Party_MemberJoin(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

MATCH void func_801FE048(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

MATCH void func_801FE08C(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_NINA_YOUNG);
    Party_LoadPalettes();
}

MATCH void func_801FE0D0(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_NINA_YOUNG);
    Party_MemberJoin(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

/* func_801FE11C */
MATCH void Party_JoinMomo(void) {
    Party_MemberJoin(CHAR_ID_MOMO);
}

/* func_801FE13C */
MATCH void Party_JoinPeco(void) {
    Party_MemberJoin(CHAR_ID_PECO);
}

#include "overlays/scenario/shared/Scene_JoinNina.h"

MATCH void func_801FE198(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_GARR, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_GARR);
}

MATCH void Scene_JoinNina3(void) {
    SCENE_JOIN_NINA();
}

MATCH void func_801FE210(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_GARR, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_NINA_YOUNG);
    Party_MemberJoin(CHAR_ID_GARR);
}

/* func_801FE254 */
MATCH void Scene_RemoveRyuGarr(void) {
    Party_MemberRemove(CHAR_ID_RYU_YOUNG);
    Party_MemberRemove(CHAR_ID_GARR);
    Party_LoadPalettes();
}

/* func_801FE284 */
MATCH void Scene_RemoveRyuMomo(void) {
    Party_MemberRemove(CHAR_ID_RYU_YOUNG);
    Party_MemberRemove(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

/* func_801FE2B4 */
MATCH void Scene_RemoveRyuPeco(void) {
    Party_MemberRemove(CHAR_ID_RYU_YOUNG);
    Party_MemberRemove(CHAR_ID_PECO);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_RemoveGarr.h"

#include "overlays/scenario/shared/Scene_RemovePeco.h"

/* func_801FE334 */
MATCH void Scene_RemovePecoGarr(void) {
    Party_MemberRemove(CHAR_ID_PECO);
    Party_MemberRemove(CHAR_ID_GARR);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_RemoveMomo.h"

/* func_801FE38C */
MATCH void Scene_RemoveMomoPeco(void) {
    Party_MemberRemove(CHAR_ID_MOMO);
    Party_MemberRemove(CHAR_ID_PECO);
    Party_LoadPalettes();
}
