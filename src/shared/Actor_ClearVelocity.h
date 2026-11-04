/* Zeroes the spad actor's velocity members unk_0C, unk_10 and vz. One definition shared by the resident
 * image and the area189 overlay; each includes this file where the function sits. Every change here must
 * verify every member. */
/* func_801C5798 (game), func_801F5F20 (area189) */
MATCH void Actor_ClearVelocity(void) {
    g_SpadWork->unk_0C = 0;
    g_SpadWork->unk_10 = 0;
    g_SpadWork->vz     = 0;
}
