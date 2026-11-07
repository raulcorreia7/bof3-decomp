#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F717C(void) {
    u8* entity;

    D_801FD178[entity[1]]();
}

MATCH void func_801F71B8(void) {
    SYS_DISPATCH_TASK(D_801FD184, 2, g_Task);
}

MATCH void func_801F71FC(void) {
    Actor* actor;

    D_801FD288.half    = (rand() & 1) << 15;
    actor              = g_Task;
    actor->header.step = actor->header.step + 1;
}

#define SCENA12_STEP_COUNTER()                                                            \
    {                                                                                     \
        s32    bits;                                                                      \
        u16    value;                                                                     \
        u32    high;                                                                      \
        u32    count;                                                                     \
        Actor* actor;                                                                     \
                                                                                          \
        if (*g_ScriptVars == 1) {                                                         \
            Actor_Clear();                                                                \
            return;                                                                       \
        }                                                                                 \
        high = (u16)D_801FD288.half >> 0xF;                                               \
        if ((u32)(D_801FD288.half & 0xFF) >= 0xC8U) {                                     \
            actor = g_Task;                                                               \
            actor->header.step += 1;                                                      \
            return;                                                                       \
        }                                                                                 \
        count = ((u32)(D_801FD288.half & 0x7F00) >> 8) + 1;                               \
        value = D_801FD288.half;                                                          \
        if (((high & 0xFF) == 0 && count >= 30) || ((high & 0xFF) != 0 && count >= 40)) { \
            count = 0;                                                                    \
            value += 1;                                                                   \
            if (SYS_TestFlag(g_SceneFlags, 0x14) != 0) {                                  \
                SND_PlayCue(EMI_CUE_ID(2, 10));                                           \
            }                                                                             \
        }                                                                                 \
        bits = high << 15;                                                                \
        bits |= count << 8;                                                               \
        D_801FD288.half = (value & 0xFF) | bits;                                          \
    }

MATCH void func_801F7240(void) {
    SCENA12_STEP_COUNTER();
}

/* The statements of func_801F7348 and func_801F7518, byte-identical twins: unless a message is pending, the entry state
 * is 4 or scene flag 0x2E is set, queue script step 5 with D_80146875 = 0x19, raise the script-active flag and clear
 * the work. Every change here must verify both members. */
#define SCENA12_START_SCRIPT()                                                                                        \
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_GameEntryState != 4 && SYS_TestFlag(g_SceneFlags, 0x2E) == 0) { \
        D_80146875 = 0x19;                                                                                            \
        D_80146874 = 5;                                                                                               \
        g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;                                                                       \
        Actor_Clear();                                                                                                \
    }

MATCH void func_801F7348(void) {
    SCENA12_START_SCRIPT();
}

MATCH void func_801F73CC(void) {
    SYS_DISPATCH_TASK(D_801FD190, 2, g_Task);
}

MATCH void func_801F7410(void) {
    SCENA12_STEP_COUNTER();
}

MATCH void func_801F7518(void) {
    SCENA12_START_SCRIPT();
}

MATCH void func_801F759C(void) {
    func_801F75EC();
    if ((g_GameStateIndex != GAME_REQUEST_MESSAGE) && (g_GameEntryState != 4)) {
        Actor_Clear();
    }
}

MATCH void func_801F75EC(void) {
    char* buffer;
    char* fmt;
    u8    value;

    buffer = (char*)g_UiFormatBuffer;
    Menu_DrawHeaderBar(0x8A, 0x1E, 0x2D, 0x14, 1u);
    value = D_801FD288.bytes[0];
    fmt   = D_801F6C04;
    TEXT_Format(buffer, fmt, value);
    UI_DrawAsciiString(0x95, 0x22, 0, buffer);
}

INCLUDE_ASM(Menu_DrawHeaderBar);

MATCH void func_801F7BA8(void) {
    SYS_DISPATCH_TASK(D_801FD198, 1, g_Task);
}

MATCH void func_801F7BEC(void) {
    Actor* actor;

    actor              = g_Task;
    actor->screen_x    = 0;
    actor->header.mode = actor->header.mode + 1;
    SND_PlayCue(EMI_CUE_ID(2, 21));
}

INCLUDE_ASM(func_801F7C24);

MATCH void func_801F7E14(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F7E34);

MATCH void func_801F7F28(void) {
    SYS_DISPATCH_BYTE(D_801FD1B8, D_80146872);
}

MATCH void func_801F7F64(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7F78);

MATCH void func_801F886C(void) {
    SYS_DISPATCH_BYTE(D_801FD1C4, g_SceneState.state_04);
}

MATCH void func_801F88A8(void) {
}

INCLUDE_ASM(func_801F88B0);

INCLUDE_ASM(func_801F894C);

MATCH void func_801F89FC(void) {
}

INCLUDE_ASM(func_801F8A04);

INCLUDE_ASM(func_801F9680);

INCLUDE_ASM(func_801F9F0C);

INCLUDE_ASM(func_801FA7DC);

INCLUDE_ASM(func_801FAE04);

INCLUDE_ASM(func_801FB864);

MATCH void func_801FC574(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FD1EC[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FC5B4(void) {
}

MATCH void func_801FC5BC(void) {
}

MATCH void func_801FC5C4(void) {
}

MATCH void func_801FC5CC(void) {
}

MATCH void func_801FC5D4(void) {
}

MATCH void func_801FC5DC(void) {
}

MATCH void func_801FC5E4(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 1;
}

MATCH void func_801FC630(void) {
}

MATCH void func_801FC638(void) {
}

MATCH void func_801FC640(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x14;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 4;
}

MATCH void func_801FC690(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x14;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 5;
}

MATCH void func_801FC6E0(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 2;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 5;
}

MATCH void func_801FC738(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 8;
}

MATCH void func_801FC784(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x1e;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 8;
}

MATCH void func_801FC7D4(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0xA;
    g_SceneState.state_04 = 1;
}

MATCH s32 func_801FC80C(s32 arg0) {
    if ((g_GameAreaId == AREA_ID_STEEL_BEACH_MAP) && (SYS_TestFlag(g_SceneFlags, 0) != 0)) {
        if (arg0 <= TO_COORD(22)) {
            Game_SetScriptActive();
            D_80146875 = 0x3C;
            D_80146874 = 2;
            return 1;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}

INCLUDE_ASM(func_801FC890);

INCLUDE_ASM(func_801FCC54);

MATCH s32 func_801FCCBC(void) {
    Game_SetScriptActive();
    g_ScriptVars[0] = 0;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    if (g_BattlePartyBattlers[0].chr.character_id != 5) {
        D_80146875 = 0;
        D_80146874 = 5;
        return 1;
    }
    D_80146875 = 5;
    D_80146874 = 5;
    return 1;
}

MATCH s32 func_801FCD38(void) {
    SND_PlayCue(EMI_CUE_ID(2, 9));
    return -1;
}

INCLUDE_ASM(func_801FCD58);

#include "overlays/scenario/Scene_JoinAdultNinaAndMomo.h"

#include "overlays/scenario/Scene_JoinAdultNina.h"

#include "overlays/scenario/Scene_JoinMomo.h"

MATCH void Scene_JoinAdultNinaAndMomo_801FCEB4(void) {
    SCENE_JOIN_ADULT_NINA_AND_MOMO();
}

MATCH void func_801FCF00(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_StagePalettes();
}

MATCH void Scene_JoinMomo_801FCF44(void) {
    SCENE_JOIN_MOMO();
}

#include "overlays/scenario/Scene_JoinMomoAndPeco.h"

#include "overlays/scenario/Scene_JoinPeco.h"

#include "overlays/scenario/Scene_JoinReiAndGarr.h"

MATCH void func_801FD064(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_GARR, 0);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_GARR);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_StagePalettes();
}

#include "overlays/scenario/Scene_RemoveRei.h"

#include "overlays/scenario/Scene_RemoveGarr.h"

#include "overlays/scenario/Scene_RemovePeco.h"

#include "overlays/scenario/Scene_RemoveMomo.h"

#include "overlays/scenario/Scene_RemoveAdultNina.h"
