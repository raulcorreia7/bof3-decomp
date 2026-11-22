#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8CAC(void) {
    switch (g_ScenarioState.step) {
        case 0:
            g_ScenarioState.step = 1;
            SYS_SetFlag(g_SceneFlags, 0xB);
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            UI_ModeSet(UI_MODE_LONG_FADE_OUT);
            break;
        case 1:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0;
                func_801C16B8();
                g_ScenarioState.step = 2;
                SND_SeqFadeOut(0, 0, 4, 0x1E);
            }
            break;
        case 2:
            SND_XAStartStream(0, 1);
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (SND_XAIsIdle()) {
                g_ScenarioState.step = 4;
            }
            break;
        case 4:
            g_ScenarioState.step = 5;
            Game_RequestAreaChange(AREA_ID_PLANT, TO_COORD(0x44), TO_COORD(0x21), 0x80);
            SND_BGMPlay(0x10, 0x64, 8);
            break;
        case 5:
            g_ScenarioState.step = 6;
            g_AreaDrawFlags      = 0x1F;
            break;
        case 6:
            if (g_ScriptVars[0] == 0x28) {
                g_ScenarioState.step = 7;
                SYS_SetFlag(g_SceneFlags, 0xC);
                SYS_SetFlag(g_SceneFlags, 0xE);
                SYS_SetFlag(g_SceneFlags, 0xF);
                SYS_ClearFlag(g_SceneFlags, 0x3F);
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
                Game_RequestAreaChange(0x45, TO_COORD(0x1E), TO_COORD(0x19), 0x80);
                g_GamePrevSelection = 0xFF;
            }
            break;
        case 7:
            break;
    }
}
