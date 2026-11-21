#include "engine/game/00/game_00.h"

MATCH void Scene_UpdateEvent(void) {
    SYS_DISPATCH_BYTE(g_SceneEvents, g_SceneEventState.mode);
}
