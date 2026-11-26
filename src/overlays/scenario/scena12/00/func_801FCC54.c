#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH s8 func_801FCC54(s32 x, s32 y) {
    SCENE_PROBE_POSITION(D_801FD228, 4, D_801FD23C);
}

MATCH s32 func_801FCCBC(void) {
    Game_SetScriptActive();
    g_ScriptVars[0] = 0;
    g_ScriptVars[1] = 0;
    g_ScriptVars[2] = 0;
    g_ScriptVars[3] = 0;
    if (g_Game.members[0].chr.character_id != CHAR_ID_MOMO) {
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 5;
        return 1;
    }
    g_ScenarioState.step     = 5;
    g_ScenarioState.state_04 = 5;
    return 1;
}

MATCH s32 func_801FCD38(void) {
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 9));
    return -1;
}

MATCH s32 func_801FCD58(void) {
    if (SYS_TestFlag(g_SceneFlags, 42) == 0) {
        Game_SetScriptActive();
        g_ScriptVars[0]          = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 7;
        Area_CellSetPalette(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        return 1;
    }
    return -1;
}
