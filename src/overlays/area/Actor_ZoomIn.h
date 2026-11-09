/* Grows the actor scale at offset 0x40 by 0x2000 each frame; when the timer at byte 0x09 expires, clears offset 0x48 and sets the handler index at byte 0x01 to 3, then keeps the actor drawn. */
/* func_801F325C (area065), func_801F3258 (area087), func_801F3D88 (area088), func_801F32E8 (area104) */
MATCH void Actor_ZoomIn(void) {
    Actor* scratch;
    Actor* scratch2;
    u8     timer;

    Actor_CenterOnScreen();

    scratch        = g_Task;
    timer          = scratch->timer;
    scratch->timer = timer - 1;
    scratch2       = g_Task;
    scratch->scale.x += 0x2000;

    if (scratch2->timer == 0) {
        scratch2->unk_48    = 0;
        g_Task->header.mode = 3;
    }

    Area_AddActor();
}
