#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH s32 func_801FC1D0(s32 member_index) {
    s32    actor_index;
    s16    height;
    u8     option_flags;
    Actor* actor;
    Actor* task;
    Actor* task2;
    Actor* task3;
    Actor* task4;

    actor_index = Actor_FindFreeField() & BYTE_MASK;
    if (actor_index == GAME_NONE) {
        return 0;
    }

    actor          = &g_Actors[actor_index];
    SPAD(0u)->self = actor;
    g_CurrentActor = actor;
    Actor_ResetMotion();
    Area_SceneSelectRecord(0x67);
    SELF(Actor)->header.flags = 1;

    task                              = SELF(Actor);
    task->pos.x.fixed                 = COORD_HALF + g_Game.members[(u8)member_index].pos.x.fixed;
    g_Actors[actor_index].walk_dest_x = task->pos.x.fixed;
    task->pos.y.fixed                 = g_Game.members[(u8)member_index].pos.y.fixed;
    g_Actors[actor_index].walk_dest_y = task->pos.y.fixed;
    g_Actors[actor_index].unk_88      = 0;

    height                        = Area_HeightSample(task->pos.x.fixed, task->pos.y.fixed);
    task2                         = SELF(Actor);
    task2->header.mode            = 4;
    task2->pos.z.part.integer     = height;
    SELF(Actor)->header.step      = 0;
    SELF(Actor)->direction        = 0;
    SELF(Actor)->unk_06           = 0;
    actor->ext.bounds.half_height = 0;
    g_Actors[actor_index].unk_77  = 2;
    g_Actors[actor_index].unk_78  = 2;

    g_Actors[actor_index].ext.bounds.half_width = 0;
    g_Actors[actor_index].unk_7C                = 0;
    option_flags                                = 0x88;
    Actor_SetOptionFlags(&option_flags);
    SELF(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    task3                   = SELF(Actor);
    task3->tint.bytes.rgb.b = 0;
    task3->tint.bytes.rgb.g = 0;
    task3->tint.bytes.rgb.r = 0;
    task4                   = SELF(Actor);
    task4->tint.bytes.flags = 1;
    Actor_StartFacingScript();
    return 1;
}

MATCH void func_801FC3B4(void) {
    SCENA03_NUDGE_SCROLL(D_801FD004, 3);
}

MATCH void func_801FC410(void) {
    SCENA03_NUDGE_SCROLL(D_801FD008, 1);
}

#include "overlays/scenario/shared/Scene_DispatchActor.h"

MATCH void func_801FC4AC(void* entity, void* bits) {
    Game_SetScriptActive();
    SYS_SetFlag(bits, 20U);
    g_ScenarioState.state_04 = 4;
    g_ScenarioState.step     = 0;
}

MATCH void func_801FC4F4(void* entity, void* flags) {
    Scene_SetFlagThenContinue(flags, 0x10);
}

MATCH void func_801FC520(void* entity, void* flags) {
    Scene_SetFlagThenContinue(flags, 0x11);
}

MATCH void func_801FC54C(void* entity, void* flags) {
    Scene_SetFlagThenContinue(flags, 0x12);
}

MATCH void func_801FC578(void* entity, void* flags) {
    Scene_SetFlagThenContinue(flags, 0x13);
}

MATCH s32 func_801FC5A4(void) {
    if ((D_80144EA2 & 0xF) == 0xF) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 6;
        g_ScenarioState.timer_06 = 30;
        return 1;
    }
    return 0;
}

MATCH void func_801FC5FC(void) {
    Item_VitalAdd(VITAL_ITEM_FLIER);
    MESSAGE_START_WAIT(MSG_SCENA03_047);
    SND_BGMPause(g_SndBGMId);
    SND_XAStartStream(2, 1);
    while (!(SND_XAIsIdle() & BYTE_MASK)) {
        Area_RunLoadingFrame();
        SYS_ThreadWait(1U);
    }
    SND_BGMResume(g_SndBGMId);
}

MATCH void func_801FC688(void) {
}

MATCH s32 func_801FC690(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 6;
    g_ScenarioState.step     = 0;
    return 0;
}

MATCH s32 func_801FC6C4(void) {
    Game_SetScriptActive();
    g_ScenarioState.timer_06 = 30;
    g_ScenarioState.state_04 = 7;
    g_ScenarioState.step     = 0;
    return 0;
}

MATCH s8 func_801FC704(s32 entry_x, s32 entry_y) {
    /* kept: the LOHU halfword compare matches retail; the plain u16 lvalue adds four bytes. */
    switch (LOHU(g_GameAreaId)) {
        case AREA_ID_WYNDIA_LOWER:
            return func_801FC944(entry_x, entry_y);
        case AREA_ID_WYNDIA_CASTLE_BASEMENT:
            return func_801FC8AC(entry_x, entry_y);
        case AREA_ID_GENMEL:
            return func_801FCAB8(entry_x, entry_y);
        case AREA_ID_MOUNT_MYRNEG:
            return func_801FC7EC(entry_x, entry_y);
        case AREA_ID_EYGNOCK_ROAD:
            return func_801FC9DC(entry_x, entry_y);
        case AREA_ID_MOUNT_BOUMORE_FIRST:
            return func_801FCB4C(entry_x, entry_y);
    }
    return 0;
}

MATCH s32 func_801FC7EC(s32 entry_x, s32 entry_y) {
    u8 state;

    if (SYS_TestFlag(g_SceneFlags, 1) == 0) {
        if (SYS_TestFlag(g_SceneFlags, 0) == 0) {
            if (((entry_x >> 0x10) - 2) < 3U) {
                if (entry_y == TO_COORD(6)) {
                    state = 2;
                    goto block_9;
                }
            }
        } else if ((SYS_TestFlag(g_SceneFlags, 0) != 0) && (((entry_x >> 0x10) - 3) < 2U)) {
            if (entry_y == TO_COORD(4)) {
                state = 1;
            block_9:
                g_ScenarioState.state_04 = state;
            }
        }
    }
    return 0;
}

MATCH s32 func_801FC8AC(s32 entry_x, s32 entry_y) {
    if (SYS_TestFlag(g_SceneFlags, 7) == 0) {
        if (((entry_y >> 0x10) - 7) < 2U) {
            if (entry_x == TO_COORD(92)) {
                SYS_SetFlag(g_SceneFlags, 7U);
                g_ScenarioState.state_04 = 3;
                g_ScenarioState.step     = 0xA;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

MATCH s8 func_801FC944(s32 entry_x, s32 entry_y) {
    if (SYS_TestFlag(g_SceneFlags, 21) == 0) {
        if (entry_y == TO_COORD(65) + COORD_HALF) {
            if (((entry_x >> 0x10) - 32) < 4U) {
                g_ScenarioState.state_04 = 4;
                g_ScenarioState.step     = 5;
                return Scene_ShowMessage(MSG_SCENA03_051);
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

MATCH s8 func_801FC9DC(s32 entry_x, s32 entry_y) {
    if (SYS_TestFlag(g_SceneFlags, 24) == 0) {
        if (entry_x == TO_COORD(58) + COORD_HALF) {
            if (((entry_y >> 0x10) - 60) >= 2U) {
                goto block_4;
            }
            goto block_9;
        }
    block_4:
        if (entry_y == TO_COORD(2) + COORD_HALF) {
            if (((entry_x >> 0x10) - 31) >= 2U) {
                goto block_7;
            }
            goto block_9;
        }
    block_7:
        if (entry_y == TO_COORD(76) + COORD_HALF) {
            if (((entry_x >> 0x10) - 31) < 2U) {
            block_9:
                g_ScenarioState.state_04 = 5;
                g_ScenarioState.step     = 0;
                return Scene_ShowMessage(MSG_SCENA03_018);
            }
            /* Duplicate return node #11. Try simplifying control flow for better match */
            return 0;
        }
        /* Duplicate return node #11. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}

MATCH s8 func_801FCAB8(s32 entry_x, s32 entry_y) {
    if (SYS_TestFlag(g_SceneFlags, 26) != 0) {
        if ((entry_x >> 0x10) == 21) {
            if (((entry_y >> 0x10) - 52) < 2U) {
                g_ScenarioState.state_04 = 5;
                g_ScenarioState.step     = 0x10;
                return Scene_ShowMessage(MSG_SCENA03_031);
            }
        }
    }
    return 0;
}

MATCH s8 func_801FCB4C(s32 entry_x, s32 entry_y) {
    if (SYS_TestFlag(g_SceneFlags, 0x1B) == 0) {
        if (g_GameCellType != 2) {
            return 0;
        }
        if (entry_x != TO_COORD(10) + COORD_HALF) {
            return 0;
        }
        if (((entry_y >> 16) - 36) >= 2U) {
            return 0;
        }
        g_ScriptVars[1]          = 1;
        g_ScenarioState.state_04 = 6;
        g_ScenarioState.step     = 5;
        return Scene_ShowMessage(MSG_SCENA03_012);
    }
    if (g_GameCellType == 3 && entry_y == TO_COORD(11) + COORD_HALF && ((entry_x >> 16) - 5) < 2U) {
        if (SYS_TestFlag(g_SceneFlags, 0x1C) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0xF;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else {
            g_ScenarioState.step     = 0xD;
            g_ScenarioState.state_04 = 6;
            return Scene_ShowMessage(MSG_SCENA03_017);
        }
    }
    return 0;
}

#include "overlays/scenario/shared/Scene_ShowMessage.h"

MATCH s32 func_801FCCDC(s32 x, s32 y) {
    if (MEM(u16, GAME_AREA_ID_ADDR) == AREA_ID_MOUNT_BOUMORE_SECOND) {
        return func_801FCD1C(x, y);
    }
    return 0;
}

MATCH s8 func_801FCD1C(s32 x, s32 y) {
    if (SYS_TestFlag(g_SceneFlags, 30) == 0) {
        if (y == TO_COORD(73)) {
            if (((x >> 16) - 14) < 4U) {
                Game_SetScriptActive();
                g_ScenarioState.state_04 = 8;
                g_ScenarioState.step     = 2;
                g_ScenarioState.timer_06 = 30;
                return 1;
            }
        }
    }
    return 0;
}

/* needs: D_801FD030 and D_801FD038 declarations. */
MATCH s32 func_801FCDB4(s32 entry_x, s32 entry_y) {
    s8  index;
    s32 result;

    index = func_801A7AD8(&D_801FD030, 1, entry_x, entry_y);
    if (index >= 0) {
        SYS_DISPATCH_BYTE(D_801FD038, index);
        result = 1;
    } else {
        result = -1;
    }
    return result;
}

MATCH void func_801FCE18(void) {
    MESSAGE_START_WAIT(MSG_SCENA03_025);
    Game_SetScriptActive();
    g_ScenarioState.timer_06 = 30;
    g_ScenarioState.state_04 = 7;
    g_ScenarioState.step     = 0;
}

MATCH void func_801FCE6C(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_GARR, 0);
    g_PartyFieldOrder[0]  = 255;
    D_80144F5B            = 255;
    D_80144F5C            = 255;
    g_PartyBattleOrder[0] = 255;
    D_80144F5E[0]         = 255;
    D_80144F5F            = 255;
    g_Game.party_size     = 0;
    Party_MemberJoin(CHAR_ID_RYU_YOUNG);
}

/* func_801FCEDC */
MATCH void Party_JoinNinaYoung(void) {
    Party_MemberJoin(CHAR_ID_NINA_YOUNG);
}

#include "overlays/scenario/shared/Scene_RemoveNina.h"
