#include "area189_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5600(void) {
    s32 i;

    Actor_ClearVelocity_801F5F20();
    g_EncounterSteps++;
    ((u16*)D_80144EF8)[0x2E]++;
    if (((u16*)D_80144EF8)[0x2E] == 0x1E0) {
        if (D_80144EF8[0x5F] != 0) {
            D_80144EF8[0x5F] += 8;
        }
        D_8014933C = 0;
        g_ScenarioState.flags_01 &= 0xFE;
        MESSAGE_START_WAIT(5);
    }
    if (((u16*)D_80144EF8)[0x2E] == 0x3C0) {
        if (D_80144EF8[0x5F] != 0) {
            D_80144EF8[0x5F] += 8;
        }
        ((u16*)D_80144EF8)[0x2E] = 0;
        D_8014933C               = 1;
        g_ScenarioState.flags_01 |= 1;
        D_80144EF8[0x5E]++;
        MESSAGE_START_WAIT(6);
    }
    if (D_80144EF8[0x5F] != 0) {
        for (i = 0; i < (D_8014933C == 0 ? 3 : 1); i++) {
            if (D_80144EF8[0x5F] != 0) {
                D_80144EF8[0x5F]--;
            }
        }
        D_80146880 = 0;
        D_80146881 = 0;
        if (D_80144EF8[0x5F] == 0) {
            MESSAGE_START_WAIT(1);
        }
    } else {
        if (LOBU(D_80146880) >= (rand() & 7) + D_8014933C * 20 + 7) {
            D_80146880 = 0;
            if (LOBU(D_80146881) >= 4) {
                Char_AddFatigue();
                g_AreaSceneMode = 2;
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0xB));
                D_80146881 = 0;
            } else {
                func_801F6088();
                g_AreaSceneMode = 1;
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 8));
                D_80146881 = D_80146881 + 1;
            }
        } else {
            D_80146880 = D_80146880 + 1;
        }
    }
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        if (SYS_TestFlag(D_80144EF8, 4) == 0 && (u32)((TASK(Actor)->pos.x.part.integer >> 8) - 0x16) < 2 && (TASK(Actor)->pos.y.part.integer >> 8) < 0x11) {
            func_801F8850();
        } else if (func_801A79A4(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) == 0) {
            if ((TASK(Actor)->pos.x.part.integer >> 8) < 10) {
                TASK(Actor)->pos.x.part.integer += 0x100;
            }
            if ((TASK(Actor)->pos.y.part.integer >> 8) < 14) {
                TASK(Actor)->pos.y.part.integer += 0x100;
            }
            if ((TASK(Actor)->pos.x.part.integer >> 8) >= 31) {
                TASK(Actor)->pos.x.part.integer -= 0x100;
            }
            if ((TASK(Actor)->pos.y.part.integer >> 8) >= 25) {
                TASK(Actor)->pos.y.part.integer -= 0x100;
            }
            g_AreaScrollTargetCoordX.fixed = TASK(Actor)->pos.x.fixed;
            g_AreaCameraRefreshCount       = 2;
            g_AreaScrollTargetCoordY.fixed = TASK(Actor)->pos.y.fixed;
            if ((g_Game.flags & 0x20) == 0 && (u16)g_EncounterSteps >= D_80145FB8) {
                g_EncounterSteps = 0;
                if ((TASK(Actor)->pos.x.part.integer >> 8) == 0x0B && (TASK(Actor)->pos.y.part.integer >> 8) == 0x0F) {
                    SYS_SetFlag(g_SceneEventFlags, 0x75);
                }
                if ((TASK(Actor)->pos.x.part.integer >> 8) == 0x15 && (TASK(Actor)->pos.y.part.integer >> 8) == 0x11) {
                    SYS_SetFlag(g_SceneEventFlags, 0x76);
                }
                if ((TASK(Actor)->pos.x.part.integer >> 8) == 0x0C && (TASK(Actor)->pos.y.part.integer >> 8) == 0x14) {
                    SYS_SetFlag(g_SceneEventFlags, 0x8B);
                }
                if ((TASK(Actor)->pos.x.part.integer >> 8) == 0x10 && (TASK(Actor)->pos.y.part.integer >> 8) == 0x11) {
                    SYS_SetFlag(g_SceneEventFlags, 0x8C);
                }
                if ((TASK(Actor)->pos.x.part.integer >> 8) == 0x1D && (TASK(Actor)->pos.y.part.integer >> 8) == 0x17) {
                    SYS_SetFlag(g_SceneEventFlags, 0x8D);
                }
                if ((TASK(Actor)->pos.x.part.integer >> 8) == 0x14 && (TASK(Actor)->pos.y.part.integer >> 8) == 0x14) {
                    SYS_SetFlag(g_SceneEventFlags, 0x8E);
                }
                g_GameEntryAreaId = AREA_ID_DESERT_BATTLEFIELD;
                g_GameEntryPosX   = TO_COORD(25);
                g_GameEntryPosY   = TO_COORD(25);
                g_GameEntryFacing = 4;
                D_8014504B        = (TASK(Actor)->direction + D_801F62F0[rand() & 3]) & 0xF;
                Game_RequestAreaChange(g_GameEntryAreaId, g_GameEntryPosX, g_GameEntryPosY, g_GameEntryFacing);
            } else if (!GAME_SCRIPT_ACTIVE()) {
                if (!(g_Game.walk_flags & AREA_WALK_ENTRY_PENDING) && (g_Game.input & (g_InputMasks[FIELD_INPUT_INTERACT] | 0xB000)) != 0) {
                    func_801F518C();
                    return;
                }
            }
        }
    }
    func_801F5D20();
}
#else
INCLUDE_ASM(func_801F5600);
#endif
