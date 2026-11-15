/* Clears the probe-slot reference at the work byte +0x2B and the panel mode byte in the game state record once the actor slot at the work byte +0x0B is unused (its use flag is clear or its byte +0x01 is set) and the area camera is not moving, then runs Actor_StepAnimLoop. Unlike Char_ClearModeIfSlotFree this member also clears the reference and accepts a slot whose byte +0x01 is set. */
/* func_801D0204 (plp016), func_801D0628 (plp026), func_801D042C (plp056), func_801CF900 (plp267), func_801CF324
   (plp467), func_801CF704 (plp567), func_801CF108 (plp678) */
MATCH void Char_ClearModeIfUnused(void) {
    Actor* work = g_Task;

    if ((g_SpawnedActors[work->param.actor_slot].header.flags == 0 || g_SpawnedActors[work->param.actor_slot].header.mode == 1) && g_AreaCameraMoving == 0) {
        work->unk_2B                              = 0;
        g_Game.current->u.field.mode_12B.s8_value = 0;
    }
    Actor_StepAnimLoop();
}
