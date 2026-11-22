#include "game_00.h"

MATCH u16 func_801ACE9C(s32 index) {
    return LOHU(g_SceneActorDefs[(u16)index * 8]);
}
