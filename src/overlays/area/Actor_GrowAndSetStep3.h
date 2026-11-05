/* Grows the actor scale at offset 0x40 by 0x2000 each frame; when the timer
 * at byte 0x09 expires, clears offset 0x48 and sets the handler index at byte
 * 0x01 to 3, then keeps the actor drawn. One definition shared by the world
 * area overlays; every change here must verify every member.
 */
/* func_801F325C (area065), func_801F3258 (area087), func_801F3D88 (area088), func_801F32E8 (area104) */
MATCH void Actor_GrowAndSetStep3(void) {
    Actor* scratch;
    Actor* scratch2;
    u8     timer;

    Actor_CenterOnScreen();

    scratch         = g_SpadWork;
    timer           = scratch->unk_09;
    scratch->unk_09 = timer - 1;
    scratch2        = g_SpadWork;
    scratch->unk_40 += 0x2000;

    if (scratch2->unk_09 == 0) {
        scratch2->unk_48   = 0;
        g_SpadWork->unk_01 = 3;
    }

    Area_AddActor();
}
