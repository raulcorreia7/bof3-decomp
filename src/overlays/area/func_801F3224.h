/* Centres the actor on screen, counts work byte 0x09 down while adding 0x2000
 * to the field at +0x40, and when the byte reaches 0 clears the field at +0x48
 * and sets work byte 0x01 to 3, then adds the actor. One definition shared by
 * the area overlays; every change here must verify every member. */
/* func_801F3224 (area016), func_801F3224 (area045) */
MATCH void func_801F3224(void) {
    Actor* scratch;
    Actor* scratch2;
    u8     timer;

    Actor_CenterOnScreen();

    scratch                    = g_SpadWork;
    timer                      = *(u8*)(((u8*)scratch + 9));
    *(u8*)(((u8*)scratch + 9)) = timer - 1;
    scratch2                   = g_SpadWork;
    scratch->unk_40 += 0x2000;

    if (((u8*)scratch2)[9] == 0) {
        scratch2->unk_48   = 0;
        g_SpadWork->unk_01 = 3;
    }

    Area_AddActor();
}
