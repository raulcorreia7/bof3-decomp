#include "game_00.h"

MATCH void Scene_RunEventHandler(void) {
    SYS_DISPATCH_BYTE(g_SceneEvents, g_SaveData.scene_event.mode);
}
