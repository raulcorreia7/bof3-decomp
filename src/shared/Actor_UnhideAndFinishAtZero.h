/* Keeps the actor slot referenced at the work byte 0x0B hidden while the timer
 * at byte 0x09 counts down; at zero the slot is shown again, the two actor
 * slots referenced at the work bytes 0x03 and 0x04 are cleared and the handler
 * index at byte 0x01 is set to 2. One definition shared by the area and
 * scenario overlays; every change here must verify every member.
 */
/* func_801F3480 (area032), func_801F78E0 (scena03) */
MATCH void Actor_UnhideAndFinishAtZero(void) {
    u8* work;

    work = (u8*)g_SpadWork;
    if (work[9] != 0) {
        g_Actors[work[11]].flags_00 |= ACTOR_FLAG_HIDDEN;
        g_SpadWork->unk_09 -= 1;
    } else {
        g_Actors[work[11]].flags_00 &= ~ACTOR_FLAG_HIDDEN;
        g_Actors[g_SpadWork->unk_03].flags_00 = 0;
        g_Actors[g_SpadWork->unk_04].flags_00 = 0;
        g_SpadWork->unk_01                    = 2;
    }
}
