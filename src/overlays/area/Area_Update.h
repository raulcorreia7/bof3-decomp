/* Each image header names the step it runs in AREA_UPDATE_STEP. One definition shared by the area overlays; every change here must verify every member. */
/* func_801F347C (area152), func_801F34EC (area033), func_801F3528 (area151), func_801F35B8 (area016), func_801F35B8 (area045), func_801F35BC (area115), func_801F35D0 (area121), func_801F35EC (area087), func_801F35F0 (area065), func_801F367C (area104), func_801F411C (area088) */
MATCH void Area_Update(void) {
    Actor* scratch;

    if (D_801454F2 == 2) {
        g_Task->step = 3;
    }

    scratch = g_Task;
    AREA_UPDATE_STEP(0x10, scratch->unk_2E);
}
