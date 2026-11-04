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

const ScriptFunc D_8018217C[21] = {
    (ScriptFunc)Game_IsScenarioEqual,
    (ScriptFunc)Game_IsAreaEqual,
    (ScriptFunc)Game_TestSceneFlag,
    (ScriptFunc)Game_IsScriptVar0Equal,
    (ScriptFunc)Game_IsScriptVar1Equal,
    (ScriptFunc)Game_IsScriptVar2Equal,
    (ScriptFunc)Game_IsScriptVar3Equal,
    (ScriptFunc)func_8015B6A8,
    (ScriptFunc)func_8015B6D0,
    (ScriptFunc)func_8015B6F8,
    0,
    (ScriptFunc)func_8015B73C,
    (ScriptFunc)Game_TestEventFlag,
    (ScriptFunc)Game_HasVitalItem,
    (ScriptFunc)Game_IsScenarioAtLeast,
    (ScriptFunc)func_8015B7F0,
    (ScriptFunc)func_8015B83C,
    (ScriptFunc)Game_SetScriptVar,
    (ScriptFunc)Game_IsScriptVarEqual,
    (ScriptFunc)Game_IncScriptVar,
    (ScriptFunc)func_8015BABC,
};
