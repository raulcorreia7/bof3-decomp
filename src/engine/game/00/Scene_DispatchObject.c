#include "game_00.h"

MATCH void Scene_DispatchObject(void* record) {
    g_SceneObjects[((Actor*)record)->callback_index](record, &g_SceneEventFlags);
}
