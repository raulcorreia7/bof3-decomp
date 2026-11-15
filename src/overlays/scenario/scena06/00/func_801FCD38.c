#include "scena06_00.h"

MATCH void func_801FCD38(void) {
    switch (g_EmiLoadedCharacterIndex & 0x7F) {
        case 0:
            func_801C1E3C(3);
            Scene_RunScenario(1);
            break;
        case 2:
            func_801C1E3C(4);
            Scene_RunScenario(1);
            break;
        case 3:
            func_801C1E3C(3);
            Scene_RunScenario(2);
            break;
        case 4:
            func_801C1E3C(5);
            Scene_RunScenario(3);
            break;
        case 6:
            func_801C1E3C(4);
            Scene_RunScenario(2);
            break;
    }
}
