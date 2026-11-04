#include "game_00.h"

MATCH void Scene_RunEventHandler(void) {
    SYS_DISPATCH_BYTE(g_SceneEvents, D_801448EB);
}
