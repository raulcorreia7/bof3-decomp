/* Updates the area spin effect. */
/* func_801F2CDC (area130), func_801F2CD8 (area175) */
MATCH void Area_UpdateSpin(void) {
    u8          scratch[0x20];
    SpinEffect* spin;
    u8          index;
    u8          timer;

    GFX_ADD_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    Camera_SetMatrix(scratch);

    spin  = (SpinEffect*)AREA_WORK;
    index = 0;
    do {
        Area_DrawSpinTriangle(spin);
        spin->spin_angle += 0x10;
        if (SELF(Actor)->timer < 4) {
            spin->fade += 0x20;
        } else {
            spin->fade -= 2;
        }
        spin++;
        index += 1;
    } while (index < 0x20);

    timer              = SELF(Actor)->timer + 1;
    SELF(Actor)->timer = timer;
    if (timer >= 0x45) {
        SELF(Actor)->header.mode += 1;
    }
}
