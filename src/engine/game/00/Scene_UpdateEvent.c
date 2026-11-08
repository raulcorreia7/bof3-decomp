#include "game_00.h"

MATCH void Scene_UpdateEvent(void) {
    SYS_DISPATCH_BYTE(g_SceneEvents, g_SceneEventMode);
}
