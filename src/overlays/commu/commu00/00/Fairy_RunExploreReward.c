#include "commu00_00.h"

/* func_801F1B8C */
MATCH void Fairy_RunExploreReward(void) {
    SYS_DISPATCH_BYTE(g_FairyExploreRewardStates, g_SceneEventStep);
}
