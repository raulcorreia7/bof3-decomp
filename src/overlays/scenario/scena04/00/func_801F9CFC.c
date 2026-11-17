#include "scena04_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9CFC(void) {
    s32 offset = D_801FA220[(g_FrameCount >> 1) & 0x3];

    g_AreaCameraRefreshCount = 2;
    g_AreaCameraHeight += offset * 4;
}

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH s32 func_801F9D88(void* entity, void* flags) {
    SYS_SetFlag(flags, 0);
    return 0;
}

MATCH s32 func_801F9DAC(void) {
    return 0;
}

MATCH s32 func_801F9DB4(s32 x, s32 y) {
    if (g_GameAreaId == AREA_ID_MOMO_TOWER_FIRST_FLOOR) {
        return func_801F9DF4(x, y);
    }
    return 0;
}

/* Momo Tower first floor: start the scripted event for the cell the party steps on, from its facing and the scene flags. */
MATCH s8 func_801F9DF4(s32 x, s32 y) {
    if (SYS_TestFlag(g_SceneFlags, 2) == 0) {
        if (((x >> 16) - 0x57) < 4U && ((y >> 16) - 0x13) < 3U) {
            g_ScratchPad.cells.bytes[0] = g_Game.members[0].facing;
            if ((u8)(g_ScratchPad.cells.bytes[0] - 5) >= 2U && g_ScratchPad.cells.bytes[0] != 4) {
                Game_SetScriptActive();
                SYS_SetFlag(g_SceneFlags, 2);
                SND_PlaySE(EMI_CUE_ID(SND_BANK_AREA, 4));
                g_SceneState.timer_06 = 30;
                g_SceneState.state_04 = 1;
                g_SceneState.step_05  = 1;
                return 1;
            }
        }
        return 0;
    }
    if (SYS_TestFlag(g_SceneFlags, 3) == 0) {
        if (((x >> 16) - 0x57) < 4U && ((y >> 16) - 0xB) < 6U) {
            g_ScratchPad.cells.bytes[0] = g_Game.members[0].facing;
            if ((u8)(g_ScratchPad.cells.bytes[0] - 5) >= 2U && g_ScratchPad.cells.bytes[0] != 4) {
                g_SceneState.state_04 = 1;
                g_SceneState.step_05  = 0;
                return Scene_ShowMessage(MSG_002);
            }
        }
        if (((y >> 16) - 0x18) < 2U && x == TO_COORD_HALF(77)) {
            g_SceneState.state_04 = 1;
            g_SceneState.step_05  = 0;
            return Scene_ShowMessage(MSG_003);
        }
        return 0;
    }
    if (SYS_TestFlag(g_SceneFlags, 7) == 0 && ((x >> 16) - 0x1F) < 3U && y == TO_COORD_HALF(36)) {
        g_SceneState.state_04 = 1;
        g_SceneState.step_05  = 0;
        return Scene_ShowMessage(MSG_038);
    }
    return 0;
}

#include "overlays/scenario/Scene_ShowMessage.h"

#include "overlays/scenario/Scene_DispatchByPosition.h"

MATCH void func_801FA074(void) {
    Game_SetScriptActive();
    g_SceneState.timer_06 = 0xA;
    g_SceneState.state_04 = 2;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FA0B4(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0);
    g_PartyFieldOrder     = 255;
    D_80144F5B            = 255;
    D_80144F5C            = 255;
    g_PartyBattleOrder[0] = 255;
    D_80144F5E            = 255;
    D_80144F5F            = 255;
    g_Game.party_size     = 0;
    Party_JoinMember(CHAR_ID_RYU_YOUNG);
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
}

#include "overlays/scenario/Scene_SetPartyRyuYoungNinaYoungMomo.h"

MATCH void func_801FA178(void) {
}
