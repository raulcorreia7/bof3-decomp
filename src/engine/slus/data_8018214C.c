#include "slus.h"

/*
 * colour matrix, 16-byte copy block and the script handler table of
 * the resident executable; the emi/etc/game/00 script interpreter indexes the
 * handlers and its tail (D_801821C0).
 */

const MATRIX D_8018214C = {
    {{3096, 0, 0}, {3096, 0, 0}, {3096, 0, 0}},
    {0, 0, 0},
};

const u8 s_ScriptCopyBlock[16] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x50, 0x50, 0x50, 0x50, 0x64, 0x64, 0xA0, 0x64,
};

const ScriptOpCallback g_AreaScriptTests[21] = {
    (ScriptOpCallback)Game_IsScenarioEqual,
    (ScriptOpCallback)Game_IsAreaEqual,
    (ScriptOpCallback)Game_TestSceneFlag,
    (ScriptOpCallback)Game_IsScriptVar0Equal,
    (ScriptOpCallback)Game_IsScriptVar1Equal,
    (ScriptOpCallback)Game_IsScriptVar2Equal,
    (ScriptOpCallback)Game_IsScriptVar3Equal,
    (ScriptOpCallback)Game_IsScenarioStateEqual,
    (ScriptOpCallback)Game_IsCellTypeEqual,
    (ScriptOpCallback)Game_TestScenarioFlag,
    0,
    (ScriptOpCallback)Game_IsLeaderEqual,
    (ScriptOpCallback)Game_TestEventFlag,
    (ScriptOpCallback)Game_HasVitalItem,
    (ScriptOpCallback)Game_IsScenarioAtMost,
    (ScriptOpCallback)Game_HasPartyFlag,
    (ScriptOpCallback)func_8015B83C,
    (ScriptOpCallback)Game_ScriptVarSet,
    (ScriptOpCallback)Game_ScriptVarIsEqual,
    (ScriptOpCallback)Game_ScriptVarInc,
    (ScriptOpCallback)Game_TestNever,
};
