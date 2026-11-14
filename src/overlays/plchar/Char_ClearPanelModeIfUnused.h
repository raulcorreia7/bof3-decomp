/* Clears the panel mode byte when the actor slot is unused and the camera is not moving. */
MATCH void Char_ClearPanelModeIfUnused(void) {
    if ((g_SpawnedActors[g_Task->param.actor_slot].header.flags == 0 || g_SpawnedActors[g_Task->param.actor_slot].header.mode == 1) && g_AreaCameraMoving == 0) {
        g_Game.current->u.field.mode_12B.s8_value = 0;
    }
    Actor_StepAnimLoop();
}
