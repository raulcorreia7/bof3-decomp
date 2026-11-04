#include "game_00.h"

MATCH void Scene_RequestChapterAdvance(void) {
    g_SceneState.flags_01 |= 0x80;
}
