#include "battle_03.h"

/* func_801E6724 */
MATCH void Battle_UpdatePoseActor(void) {
    Callback handlers[2] = {Battle_StartPoseActor, Battle_PlayPoseActor};

    g_Scripts = BATTLE_SCRIPT_TABLE;
    handlers[SELF(PartyMember)->header.mode]();
    g_Scripts = AREA_SCRIPT_TABLE;
}
