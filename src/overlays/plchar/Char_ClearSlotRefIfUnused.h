/* When the actor slot at the work byte +0x06 is unused (its use flag is clear
 * or its byte +0x01 is set) and the area camera is not moving, clears the slot
 * reference and lowers the work byte +0x03 by 2. One definition shared by the
 * plchar character programs; each program includes it where the function sits,
 * and a change must keep every member matching.
 */
/* func_801CFC90 (plp016), func_801D00B4 (plp026), func_801CF8AC (plp034), func_801CFEB8 (plp056), func_801CF38C (plp267), func_801CEB84 (plp349), func_801CEDB0 (plp467), func_801CF190 (plp567), func_801CEB94 (plp678) */
MATCH void Char_ClearSlotRefIfUnused(void) {
    Actor* work = g_SpadWork;

    if ((g_ActorSlots[work->unk_06].flags_00 == 0 || g_ActorSlots[work->unk_06].unk_01 == 1) &&
        g_AreaCameraMoving == 0) {
        work->unk_06 = 0;
        g_SpadWork->unk_03 -= 2;
    }
}
