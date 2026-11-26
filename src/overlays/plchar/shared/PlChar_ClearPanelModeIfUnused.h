/* Clears the panel mode byte when the actor slot is unused and the camera is not moving. */
MATCH void PlChar_ClearPanelModeIfUnused(void) {
    if ((g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags == 0 || g_SpawnedActors[SELF(Actor)->param.actor_slot].header.mode == 1) && g_AreaCameraMoving == 0) {
        g_Game.current->u.field.mode.value = 0;
    }
    Script_AnimStepLoop();
}
