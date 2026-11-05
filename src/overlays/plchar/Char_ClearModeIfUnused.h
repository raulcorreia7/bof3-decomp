/* Clears the probe-slot reference at the work byte +0x2B and the panel mode
 * byte in the game state record once the actor slot at the work byte +0x0B is
 * unused (its use flag is clear or its byte +0x01 is set) and the area camera
 * is not moving, then runs func_8014D978. Unlike Char_ClearModeIfSlotFree this
 * member also clears the reference and accepts a slot whose byte +0x01 is set.
 * One definition shared by the plchar character programs; each program includes
 * it where the function sits, and a change must keep every member matching.
 */
/* func_801D0204 (plp016), func_801D0628 (plp026), func_801D042C (plp056), func_801CF900 (plp267), func_801CF324 (plp467), func_801CF704 (plp567), func_801CF108 (plp678) */
MATCH void Char_ClearModeIfUnused(void) {
    Actor* work = g_SpadWork;

    if ((g_ActorSlots[work->unk_0B].flags_00 == 0 || g_ActorSlots[work->unk_0B].unk_01 == 1) &&
        g_AreaCameraMoving == 0) {
        work->unk_2B                   = 0;
        g_GameState->mode_12B.s8_value = 0;
    }
    func_8014D978();
}
