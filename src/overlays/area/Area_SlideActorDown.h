/* Slides the actor down its screen coordinate by 0x2000 fixed-point units
 * per frame while counting byte 0x09 down; at zero it clears byte 0x48 and
 * moves the handler to state 3.
 */
/* func_801F3228 (area115), func_801F323C (area121) */
MATCH void Area_SlideActorDown(void) {
u8* work;
    u8* reload;
    u8  timer;

    Actor_CenterOnScreen();

    work    = (u8*)g_SpadWork;
    timer   = work[9];
    work[9] = timer - 1;
    reload  = (u8*)g_SpadWork;
    FIELD(s32, work, 0x40) += 0x2000;

    if (reload[9] == 0) {
        reload[0x48]       = 0;
        g_SpadWork->unk_01 = 3;
    }

    Area_AddActor();
}
